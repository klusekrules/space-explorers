#include "ZmianaLiniowa.h"
#include "ZmianaFabryka.h"
#include "Logger\Logger.h"
#include "ZmianaStaleXml.h"
#include "TypyProste\TypyProsteBO.h"

namespace SZmi{
	ZmianaLiniowa::ZmianaLiniowa(XmlBO::ElementWezla wezel)
		: parametr_(XmlBO::ZnajdzWezel<NOTHROW>(wezel, XML_WEZEL_ZMIANA_PARAM))
	{
	}

	STyp::Wartosc ZmianaLiniowa::policzWartosc(const STyp::Wartosc& wartosc, const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety)const{
		return STyp::pomnozWartosc(wartosc * parametr_.pobierzWspolczynnik() , poziom);
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
		str.dodajPole(NAZWAPOLA(parametr_), parametr_);
		return str.napis();
	}
}
