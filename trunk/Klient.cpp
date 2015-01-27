#include "Klient.h"
#include <vector>
#include <chrono>
#include "Aplikacja.h"
#include "StaleRPC.h"
#include <Ws2tcpip.h>
#include "TypyProste\Wyjatek.h"
#include "zlib.h"

#define ROZMIAR_BUFORA 1024
#define ATRYBUT_PORT_SERWERA "portSerwera"
#define ATRYBUT_ADRES_SERWERA "adresSerwera"

#define RPC_OK 0
#define RPC_ERROR_MISSING_AUTORYZACJA -1
#define RPC_ERROR_MISSING_INSTANCJA -2
#define RPC_ERROR_MISSING_METODA -3
#define RPC_ERROR_MISSING_NAZWA_METODY -4
#define RPC_ERROR_MISSING_ID_UNIKALNE -5
#define RPC_ERROR_MISSING_POWTORZENIE -6
#define RPC_ERROR_MISSING_CZAS_WYWOLANIA -7

#define RPC_ERROR_UNAUTHORIZED -8
#define RPC_ERROR_WITHOUT_AUTHORIZED -9
#define RPC_ERROR_NEED_AUTHORIZATION -10

namespace SpEx{
	Klient::Klient(const UstawieniaAplikacji& opcje)
		: Watek(true)
	{

		struct addrinfo *result = NULL;
		if (getaddrinfo(opcje[ATRYBUT_ADRES_SERWERA].c_str(), nullptr, nullptr, &result)){
			throw STyp::Wyjatek(EXCEPTION_PLACE,Aplikacja::pobierzInstancje().pobierzSladStosu());
		}
		decltype(addr_) &sock = *((decltype(addr_)*)(result->ai_addr));
		addr_.sin_family = AF_INET;
		addr_.sin_port = htons(stoi(opcje[ATRYBUT_PORT_SERWERA], nullptr, 10));
		addr_.sin_addr.s_addr = sock.sin_addr.s_addr;
		gniazdo_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		funkcja_ = std::bind(&Klient::pracujJakoKlient, this);
	}

	Klient::Klient(SOCKET gniazdo, struct sockaddr_in &addr)
		: Watek(true)
	{
		gniazdo_ = gniazdo;
		addr_ = addr;
		funkcja_ = std::bind(&Klient::pracujJakoSerwer, this);
	}

	void Klient::wykonuj(){
		funkcja_();
	}

	std::future<bool> Klient::dodajZadanie(std::shared_ptr<std::promise<bool> > zakonczenie, std::shared_ptr<const std::string> parametry, std::shared_ptr<std::string> rezultat){
		std::lock_guard<std::mutex> lock(dostepDoZadan_);
		listaZadan_.emplace_back(std::make_shared<Zadanie>(zakonczenie, parametry, rezultat));
		return listaZadan_.back()->zakonczenie_->get_future();
	}

	int Klient::sprawdzMetode(const Json::Value& root) const{

		if (!root[METODA_RPC_AUTORYZACJA].isString())
			return RPC_ERROR_MISSING_AUTORYZACJA;

		if (!root[METODA_RPC_INSTANCJA].isString())
			return RPC_ERROR_MISSING_INSTANCJA;

		const Json::Value& metoda = root[METODA_RPC_METODA];

		if (!metoda.isObject())
			return RPC_ERROR_MISSING_METODA;

		if (!metoda[METODA_RPC_NAZWA].isString())
			return RPC_ERROR_MISSING_NAZWA_METODY;


		if (!metoda[METODA_RPC_ID_UNIKALNE].isString())
			return RPC_ERROR_MISSING_ID_UNIKALNE;


		if (!metoda[METODA_RPC_POWTORZENIE].isUInt())
			return RPC_ERROR_MISSING_POWTORZENIE;


		if (!metoda[METODA_RPC_CZAS_WYWOLANIA].isString())
			return RPC_ERROR_MISSING_CZAS_WYWOLANIA;

		return RPC_OK;
	}

	int Klient::sprawdzAutoryzacje(const Json::Value& root) const{
		if (root[METODA_RPC_AUTORYZACJA].asString() == "0" && root[METODA_RPC_INSTANCJA].asString() == "0")
			return RPC_ERROR_WITHOUT_AUTHORIZED;

		if (root[METODA_RPC_AUTORYZACJA].asString() == "0" || root[METODA_RPC_INSTANCJA].asString() == "0")
			return RPC_ERROR_UNAUTHORIZED;

		return RPC_OK;
	}

	void Klient::dodajKomunikatBledu(int blad, Json::Value& root){
		switch (blad){
		case RPC_OK:
			break;
		case RPC_ERROR_NEED_AUTHORIZATION:
			root[METODA_RPC_THROW][METODA_RPC_TYPE] = "Wymagana autoryzacja.";
			root[METODA_RPC_THROW][METODA_RPC_KOMUNIKAT] = "Metoda wymaga autoryzacji.";
			break;
		default:
			root[METODA_RPC_THROW][METODA_RPC_TYPE] = "Nieznany blad";
			root[METODA_RPC_THROW][METODA_RPC_KOMUNIKAT] = "Wystapil nieznany blad.";
			break;
		}
	}

	int Klient::sprawdzMetodeUprzywilejowana(const Json::Value& root)const{
		auto nazwa = root[METODA_RPC_METODA][METODA_RPC_NAZWA].asString();
		if (nazwa == "Echo" || nazwa == "Zaloguj")
			return RPC_OK;
		return RPC_ERROR_NEED_AUTHORIZATION;
	}


	void Klient::pracujJakoKlient(){

		// £¹czenie siê z serwerem
		if (SOCKET_ERROR == connect(gniazdo_, (struct sockaddr*) &addr_, sizeof(addr_))){
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji connect: " + std::to_string(error));
			zakoncz();
			return;
		}

		// Pêtla wysy³aj¹ca ¿¹dania do serwera.
		while (!czyZakonczyc()){
			std::shared_ptr<Zadanie> zadanie_ = nullptr;

			// Pobieranie ¿¹dania
			{
				std::lock_guard<std::mutex> lock(dostepDoZadan_);
				if (listaZadan_.size()){
					zadanie_ = listaZadan_.front();
					listaZadan_.pop_front();
				}
			}

			// Dzia³ania w przypadku braku oczekuj¹cych ¿¹dañ.
			if (zadanie_ == nullptr){
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				continue;
			}

			//Proces obs³ugi ¿¹dania.
			int blad;
			std::string zadanie = *(zadanie_->zadanie_);
			Dane daneW(*this, std::move(zadanie));
			daneW.wlaczKompresje();
			blad = daneW.przygotujDoWyslania();
			if (blad){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(blad));
				zakoncz();
				zadanie_->zakonczenie_->set_value(false);
				break;
			}
			// Wysy³anie ¿¹dania do serwera.
			if (!daneW.wyslij(blad)){
				if (blad == 0){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
					zakoncz();
					zadanie_->zakonczenie_->set_value(false);
					break;
				} else{
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(blad));
					zakoncz();
					zadanie_->zakonczenie_->set_value(false);
					break;
				}
			}


			Dane daneO(*this);
			// Odbieranie wiadomoœci zwrotnej
			while (!czyZakonczyc()){
				// Próba odebrania wiadomoœci zwrotniej
				if (!daneO.odbierz(blad)){

					// Obs³uga sytuacji b³êdu odbierania wiadomoœci zwrotnej 
					if (blad == 0){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
						zakoncz();
						zadanie_->zakonczenie_->set_value(false);
						break;
					} else{
						if (WSAEWOULDBLOCK != blad){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji recv: " + std::to_string(blad));
							zakoncz();
							zadanie_->zakonczenie_->set_value(false);
							break;
						} else{
							// Obs³uga gniazd nie blokuj¹cych.
							// Oczekiwanie nadejœcie danych z mo¿liwoœci¹ zewnêtrznego zakoñczenia w¹tku.
							std::this_thread::sleep_for(std::chrono::milliseconds(100));
							continue;
						}
					}
				}
				daneO.przetworzPoOdebraniu();
				*(zadanie_->rezultat_) = daneO.pobierzDane();
				zadanie_->zakonczenie_->set_value(true);
				break;
			}
		}
		zakoncz();
	}

	void Klient::pracujJakoSerwer(){
		while (!czyZakonczyc()){
			int blad;
			Dane daneO(*this);
			if (!daneO.odbierz(blad)){
				if (blad == 0){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
					break;
				} else{
					if (WSAEWOULDBLOCK != blad){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji recv: " + std::to_string(blad));
						break;
					} else{
						std::this_thread::sleep_for(std::chrono::milliseconds(100));
						continue;
					}
				}
			}

			Json::Value root;
			Json::Reader reader;
			int ret;
			if (ret = daneO.przetworzPoOdebraniu()){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d : " + std::to_string(ret));
				zakoncz();
				break;
			}
			if (reader.parse(daneO.pobierzDane(), root)){
				if (MetodaRPC::sprawdzCRC(root)){

					//Sprawdzanie metody
					auto error = sprawdzMetode(root);
					if (!error){
						error = sprawdzAutoryzacje(root);
						if (error == RPC_ERROR_WITHOUT_AUTHORIZED){
							error = sprawdzMetodeUprzywilejowana(root);
						}
					}
					
					//Obs³uga b³êdu lub wykonanie metody.
					if (error){
						dodajKomunikatBledu(error,root);
					} else{
						auto metodaRPC = Aplikacja::pobierzInstancje().fabrykator_.TworzMetodeRPC(root, *this);
						if (metodaRPC){
							Json::Value result(Json::objectValue);
							metodaRPC->obslugaZadania(root, result);
							root[METODA_RPC_METODA][METODA_RPC_RETURN] = result;
						}
					}
					
					//Wys³anie rezultatu do klienta.
					std::string ret;
					Json::FastWriter writer;
					MetodaRPC::dodajCRC(root);
					ret = writer.write(root);
					if (ret.size()){
						int blad;
						Dane daneW(*this, std::move(ret));
						daneW.wlaczKompresje();
						if (blad = daneW.przygotujDoWyslania()){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d : " + std::to_string(blad));
							zakoncz();
							break;
						}
						if (!daneW.wyslij(blad)){
							if (blad == 0){
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
								zakoncz();
								break;
							} else{
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(blad));
								zakoncz();
								break;
							}
						}
					}
				}
			}
		}
	}
	
	void Klient::autoryzujMetode(std::string& instancja, std::string& autoryzacja){
		instancja = instancja_;
		autoryzacja = autoryzacja_;
	}

	void Klient::zamknijPolaczenie(){
		if (gniazdo_ != INVALID_SOCKET){
			shutdown(gniazdo_, SD_SEND);
			closesocket(gniazdo_);
			gniazdo_ = INVALID_SOCKET;
		}
	}

	Klient::~Klient()
	{
		zamknijPolaczenie();
	}
}
