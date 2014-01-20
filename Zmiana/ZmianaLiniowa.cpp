#include "ZmianaLiniowa.h"
#include "ZmianaFabryka.h"
#include "Logger\Logger.h"

namespace SZmi{
	ZmianaLiniowa::ZmianaLiniowa(XmlBO::ElementWezla wezel)
		: parametr_(XmlBO::ZnajdzWezel<NOTHROW>(wezel, "Param")) //TODO: U¿yæ sta³ej.
	{
	}

	long double ZmianaLiniowa::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const{
		return wartosc * parametr_.pobierzWspolczynnik() * poziom;
	}

	ZmianaLiniowa* ZmianaLiniowa::Kopia()const{
		return new ZmianaLiniowa(*this);
	}

	bool ZmianaLiniowa::RejestrujZmianaLiniowa(ZmianaFabryka &fabryka){
		return fabryka.rejestracjaZmiany(identyfikator_, ZmianaLiniowa::TworzZmianaLiniowa);
	}

	ZmianaInterfejs* ZmianaLiniowa::TworzZmianaLiniowa(XmlBO::ElementWezla wezel){
		return new ZmianaLiniowa(wezel);
	}

	std::string ZmianaLiniowa::napis()const{
		SLog::Logger str(NAZWAKLASY(ZmianaLiniowa));
		str.dodajPole("Parametr", parametr_);
		return str.napis();
	}
}
