#include "ZmianaParametr.h"
#include "Logger\Logger.h"
#include <string>
#include "ZmianaStaleXml.h"

namespace SZmi{
	ZmianaParametr::ZmianaParametr(XmlBO::ElementWezla wezel)
	{
		XmlBO::WczytajAtrybut<NOTHROW>(wezel, XML_ATRYBUT_ZMIANA_ID, idObiektu_);
		XmlBO::WczytajAtrybut<NOTHROW>(wezel, XML_ATRYBUT_ZMIANA_WSPOLCZYNNIK, wspolczynnikObiektu_);
	}

	const STyp::Identyfikator& ZmianaParametr::pobierzIdentyfikatorObiektu()const{
		return idObiektu_;
	}

	const STyp::Wartosc& ZmianaParametr::pobierzWspolczynnik()const{
		return wspolczynnikObiektu_;
	}

	std::string ZmianaParametr::napis()const{
		SLog::Logger str(NAZWAKLASY(ZmianaParametr));
		str.dodajPole(NAZWAPOLA(idObiektu_), idObiektu_);
		str.dodajPole(NAZWAPOLA(wspolczynnikObiektu_), wspolczynnikObiektu_);
		return str.napis();
	}
}
