#include "ZmianaLiniowaIlosciowa.h"
#include "ZmianaFabryka.h"
#include "Logger\Logger.h"
#include "ZmianaStaleXml.h"
#include "TypyProste\TypyProsteBO.h"

namespace SZmi{
	ZmianaLiniowaIlosciowa::ZmianaLiniowaIlosciowa(XmlBO::ElementWezla wezel)
		: parametr_(XmlBO::ZnajdzWezel<NOTHROW>(wezel, XML_WEZEL_ZMIANA_PARAM))
	{
	}

	STyp::Wartosc ZmianaLiniowaIlosciowa::policzWartosc(const STyp::Wartosc& wartosc, const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety)const{
		return wartosc * parametr_.pobierzWspolczynnik();
	}

	ZmianaLiniowaIlosciowa* ZmianaLiniowaIlosciowa::Kopia()const{
		return new ZmianaLiniowaIlosciowa(*this);
	}

	bool ZmianaLiniowaIlosciowa::RejestrujZmianaLiniowaIlosciowa(ZmianaFabryka &fabryka){
		return fabryka.rejestracjaZmiany(identyfikator_, ZmianaLiniowaIlosciowa::TworzZmianaLiniowaIlosciowa);
	}

	ZmianaInterfejs* ZmianaLiniowaIlosciowa::TworzZmianaLiniowaIlosciowa(XmlBO::ElementWezla wezel){
		return new ZmianaLiniowaIlosciowa(wezel);
	}

	std::string ZmianaLiniowaIlosciowa::napis()const{
		SLog::Logger str(NAZWAKLASY(ZmianaLiniowaIlosciowa));
		str.dodajPole(NAZWAPOLA(parametr_), parametr_);
		return str.napis();
	}
}
