#include "ZmianaParametr.h"
#include "Logger\Logger.h"
#include <string>

namespace SZmi{
	ZmianaParametr::ZmianaParametr(XmlBO::ElementWezla wezel)
	{
		idObiektu_ = XmlBO::WczytajAtrybut<int>(wezel, "id", 0); //TODO: U¿yæ sta³ej.
		wspolczynnikObiektu_ = XmlBO::WczytajAtrybut<long double>(wezel, "wspolczynnik", 0); //TODO: U¿yæ sta³ej.
	}

	int ZmianaParametr::pobierzIdentyfikatorObiektu()const{
		return idObiektu_;
	}

	long double ZmianaParametr::pobierzWspolczynnik()const{
		return wspolczynnikObiektu_;
	}

	std::string ZmianaParametr::napis()const{
		SLog::Logger str(NAZWAKLASY(ZmianaParametr));
		str.dodajPole("IdObiektu", SLog::Logger::tworzPole(idObiektu_));
		str.dodajPole("Parametr", SLog::Logger::tworzPole(wspolczynnikObiektu_));
		return str.napis();
	}
}
