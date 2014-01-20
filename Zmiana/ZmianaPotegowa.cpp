#include "ZmianaPotegowa.h"
#include "Logger\Logger.h"

namespace SZmi{
	ZmianaPotegowa::ZmianaPotegowa(SPar::ParserElement& wezel)
		: wspolczynnik_(/*XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_PARAM, ATRYBUT_XML_IDENTYFIKATOR, "0x1")*/),
		wykladnik_(/*XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_PARAM, ATRYBUT_XML_IDENTYFIKATOR, "0x2")*/)
	{
	}

	ZmianaInterfejs* ZmianaPotegowa::TworzZmianaPotegowa(SPar::ParserElement& wezel){
		return new ZmianaPotegowa(wezel);
	}

	long double ZmianaPotegowa::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const{
		return wartosc * wspolczynnik_.pobierzWspolczynnik() * pow(static_cast<long double>(poziom), wykladnik_.pobierzWspolczynnik());
	}

	ZmianaPotegowa* ZmianaPotegowa::Kopia()const{
		return new ZmianaPotegowa(*this);
	}

	bool ZmianaPotegowa::RejestrujZmianaPotegowa(ZmianaFabryka &fabryka){
		return fabryka.rejestracjaZmiany(identyfikator_, ZmianaPotegowa::TworzZmianaPotegowa);
	}

	std::string ZmianaPotegowa::napis()const{
		SLog::Logger str(NAZWAKLASY(ZmianaPotegowa));
		str.dodajPole("wspolczynnik", wspolczynnik_);
		str.dodajPole("wykladnik", wykladnik_);
		return str.napis();
	}
}