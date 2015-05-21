#include "ZmianaPotegowaAlt.h"
#include "Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "ZmianaStaleXml.h"

namespace SZmi{
	ZmianaPotegowaAlt::ZmianaPotegowaAlt(XmlBO::ElementWezla wezel)
		: wspolczynnik_(XmlBO::ZnajdzWezel<NOTHROW>(wezel, XML_WEZEL_ZMIANA_PARAM)), wykladnik_(nullptr)
	{
		XmlBO::ElementWezla zmiana = XmlBO::ZnajdzWezel<NOTHROW>(wezel, XML_WEZEL_ZMIANA);
		if (fabryka_ && zmiana){
			wykladnik_ = fabryka_->tworz(zmiana);
			if (!wykladnik_)
				SPar::ParserUtils::generujWyjatekBleduStruktury(zmiana);
		}
	}

	ZmianaInterfejs* ZmianaPotegowaAlt::TworzZmianaPotegowaAlt(XmlBO::ElementWezla wezel){
		return new ZmianaPotegowaAlt(wezel);
	}

	STyp::Wartosc ZmianaPotegowaAlt::policzWartosc(const STyp::Wartosc& wartosc, const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety) const{
		if (wykladnik_)
			return wartosc * pow(static_cast<long double>(wspolczynnik_.pobierzWspolczynnik()()), -(wykladnik_->policzWartosc(wartosc, poziom, identyfikatorPlanety)()));
		else
			return wartosc;
	}

	ZmianaPotegowaAlt* ZmianaPotegowaAlt::Kopia()const{
		return new ZmianaPotegowaAlt(*this);
	}

	bool ZmianaPotegowaAlt::RejestrujZmianaPotegowaAlt(ZmianaFabryka &fabryka){
		fabryka_ = &fabryka;
		return fabryka.rejestracjaZmiany(identyfikator_, ZmianaPotegowaAlt::TworzZmianaPotegowaAlt);
	}

	std::string ZmianaPotegowaAlt::napis()const{
		SLog::Logger str(NAZWAKLASY(ZmianaPotegowaAlt));
		str.dodajPole(NAZWAPOLA(wspolczynnik_), wspolczynnik_);
		if (wykladnik_)
			str.dodajPole(NAZWAPOLA(wykladnik_), *wykladnik_);
		return str.napis();
	}
}
