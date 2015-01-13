#include "PolaczenieTCP.h"
#include "Logger\Logger.h"
#include <future>

namespace SpEx{

	PolaczenieTCP::PolaczenieTCP( Klient& klient)
		:klient_(klient)
	{
	}

	bool PolaczenieTCP::wyslij(std::shared_ptr<const std::string> zadanie, std::shared_ptr<std::string> rezultat) const{
		if (zadanie == nullptr || rezultat == nullptr)
			return false;
		auto zakoncz = std::make_shared<std::promise<bool>>();
		auto czyZakonczono = klient_.dodajZadanie(zakoncz,zadanie, rezultat);
		czyZakonczono.wait();
		return czyZakonczono.get();
	}
	
	std::string PolaczenieTCP::napis() const{
		SLog::Logger log(NAZWAKLASY(PolaczenieTCP));
		return log.napis();
	}
}
