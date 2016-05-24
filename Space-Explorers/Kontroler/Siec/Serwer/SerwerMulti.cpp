#include "SerwerMulti.h"
#include <Ws2tcpip.h>
#include "Utils\FinalAction.h"
#define ATRYBUT_PORT_SERWERA "portSerwera"

namespace SpEx{
	SerwerMulti::SerwerMulti(const UstawieniaAplikacji& ustawienia)
		: Nasluchiwacz(std::stoi(ustawienia[ATRYBUT_PORT_SERWERA], nullptr, 10), std::stoi(ustawienia[ATRYBUT_PORT_SERWERA], nullptr, 10))
	{}

	void SerwerMulti::wykonuj(){
		auto clearing = finally(std::bind(&SerwerMulti::clear,this));
		Nasluchiwacz::wykonuj();
	}

	bool SerwerMulti::polaczeniePrzychodzace(SOCKET gniazdoKlienta, sockaddr_in & addr){
		polaczenia_.emplace_back(gniazdoKlienta, addr);
		polaczenia_.back().odblokuj();
		return true;
	}

	void SerwerMulti::clear(){
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
