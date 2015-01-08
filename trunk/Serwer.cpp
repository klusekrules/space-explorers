#include "Serwer.h"

#define ATRYBUT_PORT_SERWERA "portSerwera"

namespace SpEx{
	Serwer::Serwer(const UstawieniaAplikacji& ustawienia)
		: Watek(true)
	{
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(std::stoi(ustawienia[ATRYBUT_PORT_SERWERA],nullptr,10));
		addr.sin_addr.s_addr = INADDR_ANY;
		gniazdo_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (INVALID_SOCKET == gniazdo_){
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji socket: " + std::to_string(error));
		}

		if (SOCKET_ERROR == bind(gniazdo_, (struct sockaddr*) &addr, sizeof(addr))){
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji bind: " + std::to_string(error));
		}
	}

	void Serwer::wykonuj(){

		if (SOCKET_ERROR == listen(gniazdo_, SOMAXCONN)){
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji listen: " + std::to_string(error));
			return;
		}

		struct sockaddr_in addr;
		int addrSize = sizeof(addr);
		SOCKET gniazdoKlienta = INVALID_SOCKET;
		u_long iMode = 1;
		int nError = 0;
		ioctlsocket(gniazdo_, FIONBIO, &iMode);

		while ( !czyZakonczyc() ) {
			gniazdoKlienta = accept(gniazdo_, (struct sockaddr*) &addr, &addrSize);
			nError = WSAGetLastError();
			if (nError != WSAEWOULDBLOCK && gniazdoKlienta == INVALID_SOCKET){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji listen: " + std::to_string(nError));
				break;
			}
			if (gniazdoKlienta != INVALID_SOCKET){
				polaczenia_.emplace_back(gniazdoKlienta, addr);
				polaczenia_.back().odblokuj();
			}else{
				Sleep(100);
			}
		}

		for (auto& p : polaczenia_){
			p.zakoncz();
		}

		for (auto& p : polaczenia_){
			if (!p.czekajNaZakonczenie()){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d oczekiwania na zamkniêcie polaczenia: ");			
			}
		}

		polaczenia_.clear();
	}
	
	Serwer::~Serwer()
	{
		if (gniazdo_ != INVALID_SOCKET){
			shutdown(gniazdo_, SD_SEND);
			closesocket(gniazdo_);
		}
	}
}
