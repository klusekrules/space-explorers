#include "Klient.h"
#include <vector>
#include <chrono>

#define ROZMIAR_BUFORA 1024
#define ATRYBUT_PORT_SERWERA "portSerwera"
#define ATRYBUT_ADRES_SERWERA "adresSerwera"

namespace SpEx{
	Klient::Klient(const UstawieniaAplikacji& opcje)
		: Watek(true)
	{
		struct hostent *he;
		he = gethostbyname(opcje[ATRYBUT_ADRES_SERWERA].c_str());
		addr_.sin_family = AF_INET;
		addr_.sin_port = htons(stoi(opcje[ATRYBUT_PORT_SERWERA], nullptr, 10));
		addr_.sin_addr.s_addr = *((unsigned long*)he->h_addr);
		gniazdo_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		funkcja_ = std::bind(&Klient::pracujJakoKlient, this);
	}

	Klient::Klient(SOCKET gniazdo, struct sockaddr_in &addr)
		: Watek(true)
	{
		gniazdo_ = gniazdo;
		addr_ = addr;
		funkcja_ = std::bind(&Klient::odbieraj, this);
	}

	void Klient::wykonuj(){
		funkcja_();
	}

	std::future<bool> Klient::dodajZadanie(std::shared_ptr<const std::string> parametry, std::shared_ptr<std::string> rezultat){
		std::lock_guard<std::mutex> lock(dostepDoZadan_);
		listaZadan_.emplace_back(std::make_shared<Zadanie>(std::promise<bool>(), parametry, rezultat));
		return listaZadan_.back()->zakonczenie_.get_future();
	}

	void Klient::pracujJakoKlient(){

		if (SOCKET_ERROR == connect(gniazdo_, (struct sockaddr*) &addr_, sizeof(addr_))){
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji connect: " + std::to_string(error));
			zakoncz();
			return;
		}

		while (!czyZakonczyc()){
			std::shared_ptr<Zadanie> zadanie_ = nullptr;
			{
				std::lock_guard<std::mutex> lock(dostepDoZadan_);
				if (listaZadan_.size()){
					zadanie_ = listaZadan_.front();
					listaZadan_.pop_front();
				}
			}
			if (zadanie_ == nullptr){
				std::this_thread::sleep_for( std::chrono::milliseconds(100));
				continue;
			}

			int blad;
			if (!wyslij(*(zadanie_->zadanie_), blad)){
				if (blad == 0){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
					zakoncz();
					break;
				}else{
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(blad));
					zakoncz();
					break;
				}
			}

			while (!czyZakonczyc()){

				if (!odbierz(*(zadanie_->rezultat_), blad)){
					if (blad == 0){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
						zakoncz();
						break;
					}else{
						if (WSAEWOULDBLOCK != blad){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji recv: " + std::to_string(blad));
							zakoncz();
							break;
						}else{
							std::this_thread::sleep_for(std::chrono::milliseconds(100));
							continue;
						}
					}
				}
				break;

			}
		}
	
	}

	void Klient::wysylaj(){

		if (SOCKET_ERROR == connect(gniazdo_, (struct sockaddr*) &addr_, sizeof(addr_))){
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji connect: " + std::to_string(error));
			return;
		}

		std::string dane("Jan Kowalski");
		int blad;
		if (!wyslij(dane, blad)){
			if (blad == 0){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
			}else{
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(blad));
			}
		}
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Wys³ano: " + dane);
	}

	void Klient::odbieraj(){
		while (!czyZakonczyc()){
			std::string dane;
			int blad;

			if (!odbierz(dane, blad)){
				if (blad == 0){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
					break;
				}else{
					if (WSAEWOULDBLOCK != blad){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji recv: " + std::to_string(blad));
						break;
					}else{
						Sleep(100);
						continue;
					}
				}
			}
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Odebrano: " + dane);
		}
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
				return false;
			}
			tempRozmiar += rezultat;
		} while (tempRozmiar != rozmiar);
		dane = bufor.data();
		error = 0;
		return rozmiar;
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
