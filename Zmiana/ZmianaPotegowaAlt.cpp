#include "ZmianaPotegowaAlt.h"
#include "Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "ZmianaUtils.h"

namespace SZmi{
	ZmianaPotegowaAlt::ZmianaPotegowaAlt(SPar::ParserElement& wezel)
		: wspolczynnik_(/*XmlBO::ZnajdzWezel<NOTHROW>(wezel, WEZEL_XML_PARAM)*/), wykladnik_(nullptr)
	{
		/*tinyxml2::XMLElement * zmiana = XmlBO::ZnajdzWezel<NOTHROW>(wezel, WEZEL_XML_ZMIANA);
		if (fabryka_ && zmiana){
			wykladnik_ = fabryka_->Tworz(zmiana);
			if (!wykladnik_)
				UtilsZmiana::generujWyjatekBleduStruktury(zmiana);
		}*/
	}

	ZmianaInterfejs* ZmianaPotegowaAlt::TworzZmianaPotegowaAlt(SPar::ParserElement& wezel){
		return new ZmianaPotegowaAlt(wezel);
	}

	long double ZmianaPotegowaAlt::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const{
		if (wykladnik_)
			return wartosc * pow(static_cast<long double>(wspolczynnik_.pobierzWspolczynnik()), -(wykladnik_->policzWartosc(wartosc, poziom, identyfikatorPlanety)));
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
		str.dodajPole("wspolczynnik", wspolczynnik_);
		if (wykladnik_)
			str.dodajPole("wykladnik", *wykladnik_);
		return str.napis();
	}
}
