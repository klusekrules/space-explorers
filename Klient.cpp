#include "Klient.h"
#include <vector>
#include <chrono>
#include "Aplikacja.h"
#include "StaleRPC.h"
#include <Ws2tcpip.h>
#include "TypyProste\Wyjatek.h"

#define ROZMIAR_BUFORA 1024
#define ATRYBUT_PORT_SERWERA "portSerwera"
#define ATRYBUT_ADRES_SERWERA "adresSerwera"

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

	void Klient::pracujJakoKlient(){

		// ��czenie si� z serwerem
		if (SOCKET_ERROR == connect(gniazdo_, (struct sockaddr*) &addr_, sizeof(addr_))){
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B��d funkcji connect: " + std::to_string(error));
			zakoncz();
			return;
		}

		// P�tla wysy�aj�ca ��dania do serwera.
		while (!czyZakonczyc()){
			std::shared_ptr<Zadanie> zadanie_ = nullptr;

			// Pobieranie ��dania
			{
				std::lock_guard<std::mutex> lock(dostepDoZadan_);
				if (listaZadan_.size()){
					zadanie_ = listaZadan_.front();
					listaZadan_.pop_front();
				}
			}

			// Dzia�ania w przypadku braku oczekuj�cych ��da�.
			if (zadanie_ == nullptr){
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				continue;
			}

			//Proces obs�ugi ��dania.
			int blad;

			// Wysy�anie ��dania do serwera.
			if (!wyslij(*(zadanie_->zadanie_), blad)){
				if (blad == 0){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkni�to po��czenie!");
					zakoncz();
					zadanie_->zakonczenie_->set_value(false);
					break;
				} else{
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B��d funkcji send: " + std::to_string(blad));
					zakoncz();
					zadanie_->zakonczenie_->set_value(false);
					break;
				}
			}

			// Odbieranie wiadomo�ci zwrotnej
			while (!czyZakonczyc()){

				// Pr�ba odebrania wiadomo�ci zwrotniej
				if (!odbierz(*(zadanie_->rezultat_), blad)){

					// Obs�uga sytuacji b��du odbierania wiadomo�ci zwrotnej 
					if (blad == 0){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkni�to po��czenie!");
						zakoncz();
						zadanie_->zakonczenie_->set_value(false);
						break;
					} else{
						if (WSAEWOULDBLOCK != blad){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B��d funkcji recv: " + std::to_string(blad));
							zakoncz();
							zadanie_->zakonczenie_->set_value(false);
							break;
						} else{
							// Obs�uga gniazd nie blokuj�cych.
							// Oczekiwanie nadej�cie danych z mo�liwo�ci� zewn�trznego zako�czenia w�tku.
							std::this_thread::sleep_for(std::chrono::milliseconds(100));
							continue;
						}
					}
				}
				zadanie_->zakonczenie_->set_value(true);
				break;
			}
		}
		zakoncz();
	}

	void Klient::pracujJakoSerwer(){
		while (!czyZakonczyc()){
			std::string dane;
			int blad;

			if (!odbierz(dane, blad)){
				if (blad == 0){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkni�to po��czenie!");
					break;
				} else{
					if (WSAEWOULDBLOCK != blad){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B��d funkcji recv: " + std::to_string(blad));
						break;
					} else{
						std::this_thread::sleep_for(std::chrono::milliseconds(100));
						continue;
					}
				}
			}

			Json::Value root;
			Json::Reader reader;
			if (reader.parse(dane, root)){
				if (MetodaRPC::sprawdzCRC(root)){
					Json::Value& metoda = root[METODA_RPC_METODA];
					// Sprawdzanie czy wymagane parametry s� zawarte w ��daniu.
					if (metoda.isNull()){
						metoda = Json::Value(Json::objectValue);
					}
					bool validParametr = root[METODA_RPC_AUTORYZACJA].isString() && root[METODA_RPC_INSTANCJA].isString() && metoda[METODA_RPC_NAZWA].isString();
					if (validParametr){
						//Sprawdzenie czy metoda jest uprzywilejowana do obs�ugi bez autoryzacji.
						if ((root[METODA_RPC_AUTORYZACJA].asString() == "0" || root[METODA_RPC_INSTANCJA].asString() == "0")
							&& !czyMetodaRPCUprzywilejowana(metoda[METODA_RPC_NAZWA].asString())){
							metoda[METODA_RPC_THROW][METODA_RPC_TYPE] = "Unautorized";
							metoda[METODA_RPC_THROW][METODA_RPC_KOMUNIKAT] = "Brak autoryzacji zdalnej metody.";
						} else{
							auto metodaRPC = Aplikacja::pobierzInstancje().fabrykator_.TworzMetodeRPC(root, *this);
							if (metodaRPC){
								Json::Value result(Json::objectValue);
								metodaRPC->obslugaZadania(root, result);
								metoda[METODA_RPC_RETURN] = result;
							}
						}
					} else{
						metoda[METODA_RPC_THROW][METODA_RPC_TYPE] = "Invalid params";
						metoda[METODA_RPC_THROW][METODA_RPC_KOMUNIKAT] = "Nie poprawna sk�adnia ��dania.";
					}


					std::string ret;
					Json::FastWriter writer;
					MetodaRPC::dodajCRC(root);
					ret = writer.write(root);
					if (ret.size()){
						int blad;

						if (!wyslij(ret, blad)){
							if (blad == 0){
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkni�to po��czenie!");
								zakoncz();
								break;
							} else{
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B��d funkcji send: " + std::to_string(blad));
								zakoncz();
								break;
							}
						}
					}
				}
			}
		}
	}

	bool Klient::odbierz(std::string& dane, int& error){
		long rozmiar = 0;
		int rezultat = 0;

		rezultat = recv(gniazdo_, (char*)&rozmiar, sizeof(long), 0);
		rozmiar = ntohl(rozmiar);
		if (rezultat <= 0){
			error = (rezultat == 0 ? 0 : WSAGetLastError());
			return false;
		}
		long tempRozmiar = 0;
		std::vector <char> bufor;
		bufor.reserve(rozmiar + 1);
		bufor.resize(rozmiar + 1, 0);
		do{
			rezultat = recv(gniazdo_, &bufor.data()[tempRozmiar], rozmiar - tempRozmiar, 0);
			if (rezultat <= 0){
				error = (rezultat == 0 ? 0 : WSAGetLastError());
				if (WSAEWOULDBLOCK == error){
					continue;
				} else{
					return false;
				}
			}
			tempRozmiar += rezultat;
		} while (tempRozmiar != rozmiar && !czyZakonczyc());
		dane = bufor.data();
		error = 0;
		return rozmiar > 0;
	}

	bool Klient::wyslij(const std::string& dane, int& error){
		u_long rozmiar = dane.size();
		int rezultat = 0;

		rozmiar = htonl(rozmiar);
		rezultat = send(gniazdo_, (char*)&rozmiar, sizeof(u_long), 0);
		rozmiar = ntohl(rozmiar);

		if (rezultat <= 0){
			error = (rezultat == 0 ? 0 : WSAGetLastError());
			return false;
		}
		long tempRozmiar = rozmiar;
		do{
			rezultat = send(gniazdo_, &(dane.c_str()[rozmiar - tempRozmiar]), rozmiar, 0);
			if (rezultat <= 0){
				error = (rezultat == 0 ? 0 : WSAGetLastError());
				return false;
			}
			tempRozmiar -= rezultat;
		} while (tempRozmiar != 0);
		error = 0;
		return true;
	}

	bool Klient::czyMetodaRPCUprzywilejowana(const std::string& nazwa)const{
		if (nazwa == "Echo" || nazwa == "Zaloguj")
			return true;
		return false;
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
