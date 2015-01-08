#include "Klient.h"
#include <vector>

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
		funkcja_ = std::bind(&Klient::wysylaj, this);
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

	void Klient::wysylaj(){

		if (SOCKET_ERROR == connect(gniazdo_, (struct sockaddr*) &addr_, sizeof(addr_))){
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji connect: " + std::to_string(error));
			return;
		}

		long rozmiar = 0;
		int rezultat = 0;
		std::string dane("Jan Kowalski");
		rozmiar = dane.size();

		rezultat = send(gniazdo_, (char*)&rozmiar, sizeof(long), 0);

		if (!(rezultat > 0)){
			if (rezultat == 0){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
				return;
			}
			else{
				auto error = WSAGetLastError();
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(error));
				return;
			}
		}

		long tempRozmiar = rozmiar;
		do{
			rezultat = send(gniazdo_, &(dane.c_str()[rozmiar - tempRozmiar]), rozmiar, 0);

			if (!(rezultat > 0)){
				if (rezultat == 0){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
					return;
				}
				else{
					auto error = WSAGetLastError();
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(error));
					return;
				}
			}
			tempRozmiar -= rezultat;
		} while (tempRozmiar != 0);
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Wys³ano: " + dane);

		shutdown(gniazdo_, SD_SEND);
		closesocket(gniazdo_);
		gniazdo_ = INVALID_SOCKET;
	}

	void Klient::odbieraj(){
		while (!czyZakonczyc()){
			long rozmiar = 0;
			int rezultat = 0;

			rezultat = recv(gniazdo_, (char*) &rozmiar, sizeof(long), 0);

			if (!(rezultat > 0)){
				if (rezultat == 0){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
					break;
				}
				else{
					auto error = WSAGetLastError();
					if (WSAEWOULDBLOCK != error){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji recv: " + std::to_string(error));
						break;
					}
					else{
						Sleep(100);
						continue;
					}
				}
			}

			long tempRozmiar = 0;
			std::vector <char> bufor_;
			bufor_.reserve(rozmiar + 1);
			bufor_.resize(rozmiar + 1,0);
			do{
				rezultat = recv(gniazdo_, &bufor_.data()[tempRozmiar], rozmiar - tempRozmiar, 0);

				if (!(rezultat > 0)){
					if (rezultat == 0){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
						break;
					}
					else{
						auto error = WSAGetLastError();
						if (WSAEWOULDBLOCK != error){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji recv: " + std::to_string(error));
							break;
						}
						else{
							Sleep(100);
							continue;
						}
					}
				}
				tempRozmiar += rezultat;
			} while (tempRozmiar!=rozmiar);
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Odebrano: " + std::string(bufor_.data()));

		}
	}

	Klient::~Klient()
	{
		if (gniazdo_ != INVALID_SOCKET){
			shutdown(gniazdo_, SD_SEND);
			closesocket(gniazdo_);
		}
	}
}
