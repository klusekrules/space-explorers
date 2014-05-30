#include "ZmianaPotegowa.h"
#include "Logger\Logger.h"
#include "ZmianaStaleXml.h"

namespace SZmi{
	ZmianaPotegowa::ZmianaPotegowa(XmlBO::ElementWezla wezel)
		: wspolczynnik_(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, XML_WEZEL_ZMIANA_PARAM, XML_ATRYBUT_ZMIANA_ID, XML_WARTOSC_ATRYBUTU_ZMIANA_0X1)),
		wykladnik_(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, XML_WEZEL_ZMIANA_PARAM, XML_ATRYBUT_ZMIANA_ID, XML_WARTOSC_ATRYBUTU_ZMIANA_0X2))
	{
	}

	ZmianaInterfejs* ZmianaPotegowa::TworzZmianaPotegowa(XmlBO::ElementWezla wezel){
		return new ZmianaPotegowa(wezel);
	}

	STyp::Wartosc ZmianaPotegowa::policzWartosc(const STyp::Wartosc& wartosc, const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety)const{
		return wartosc * wspolczynnik_.pobierzWspolczynnik() * pow(wykladnik_.pobierzWspolczynnik()(), static_cast<long double>(poziom()-1));
	}

	ZmianaPotegowa* ZmianaPotegowa::Kopia()const{
		return new ZmianaPotegowa(*this);
	}

	bool ZmianaPotegowa::RejestrujZmianaPotegowa(ZmianaFabryka &fabryka){
		return fabryka.rejestracjaZmiany(identyfikator_, ZmianaPotegowa::TworzZmianaPotegowa);
	}

	std::string ZmianaPotegowa::napis()const{
		SLog::Logger str(NAZWAKLASY(ZmianaPotegowa));
		str.dodajPole(NAZWAPOLA(wspolczynnik_), wspolczynnik_);
		str.dodajPole(NAZWAPOLA(wykladnik_), wykladnik_);
		return str.napis();
	}
}
