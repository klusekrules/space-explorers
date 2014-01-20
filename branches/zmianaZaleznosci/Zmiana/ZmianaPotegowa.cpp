#include "ZmianaPotegowa.h"
#include "Logger\Logger.h"

namespace SZmi{
	ZmianaPotegowa::ZmianaPotegowa(XmlBO::ElementWezla wezel)
		: wspolczynnik_(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, "Param", "id", "0x1")), //TODO: U¿yæ sta³ej.
		wykladnik_(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, "Param", "id", "0x2")) //TODO: U¿yæ sta³ej.
	{
	}

	ZmianaInterfejs* ZmianaPotegowa::TworzZmianaPotegowa(XmlBO::ElementWezla wezel){
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
