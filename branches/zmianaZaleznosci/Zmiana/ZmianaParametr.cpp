#include "ZmianaParametr.h"
#include "Logger\Logger.h"
#include <string>

namespace SZmi{
	ZmianaParametr::ZmianaParametr(SPar::ParserElement& wezel)
	{
		//TODO: Do uzupelnienia.
		//idObiektu_ = XmlBO::WczytajAtrybut<int>(e, ATRYBUT_XML_IDENTYFIKATOR, 0);
		//wspolczynnikObiektu_ = XmlBO::WczytajAtrybut<long double>(e, ATRYBUT_XML_WSPOLCZYNNIK, 0);
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
