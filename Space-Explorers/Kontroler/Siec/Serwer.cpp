#include "Serwer.h"
#include <Ws2tcpip.h>
#include "Utils\FinalAction.h"
#define ATRYBUT_PORT_SERWERA "portSerwera"

namespace SpEx{
	Serwer::Serwer(const UstawieniaAplikacji& ustawienia)
		: Nasluchiwacz(ustawienia)
	{}

	void Serwer::wykonuj(){
		auto clearing = finally(std::bind(&Serwer::clear,this));
		Nasluchiwacz::wykonuj();
	}

	bool Serwer::polaczeniePrzychodzace(SOCKET gniazdoKlienta, sockaddr_in & addr){
		polaczenia_.emplace_back(gniazdoKlienta, addr);
		polaczenia_.back().odblokuj();
		return true;
	}

	void Serwer::clear(){
		for (auto& p : polaczenia_) {
			p.zakoncz();
		}

		for (auto& p : polaczenia_) {
			if (!p.czekajNaZakonczenie()) {
				if(SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error))
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d oczekiwania na zamkniêcie polaczenia: " + p.pobierzAdres());
			}
		}
		polaczenia_.clear();
	}
}
