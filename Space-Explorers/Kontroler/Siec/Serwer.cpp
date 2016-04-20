#include "Serwer.h"
#include <Ws2tcpip.h>

#define ATRYBUT_PORT_SERWERA "portSerwera"

namespace SpEx{
	Serwer::Serwer(const UstawieniaAplikacji& ustawienia)
		: Nasluchiwacz(ustawienia)
	{}

	void Serwer::wykonuj(){

		Nasluchiwacz::wykonuj();

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

	bool Serwer::polaczeniePrzychodzace(SOCKET gniazdoKlienta, sockaddr_in & addr){
		polaczenia_.emplace_back(gniazdoKlienta, addr);
		return true;
	}
}
