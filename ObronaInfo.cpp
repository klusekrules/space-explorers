#include "ObronaInfo.h"
#include "Logger\Logger.h"
#include "Gra.h"

namespace SpEx{
	
	ObronaInfo::ObronaInfo(XmlBO::ElementWezla wezel) throw(WyjatekParseraXML)
		: ObiektInfo(wezel),
		JednostkaAtakujacaInfo(XmlBO::ZnajdzWezel<THROW>(wezel, WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO))
	{
		XmlBO::WczytajAtrybut<THROW>(wezel, ATRYBUT_XML_POWIERZCHNIA, powierzchnia_);
		zmianaPowierzchni_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_POWIERZCHNIA));
	}
	
	Obrona* ObronaInfo::tworzEgzemplarz(const PodstawoweParametry& parametry) const{
		return new Obrona(parametry, *this);
	}

	bool ObronaInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const{
		return planeta.dodajObiekt(std::shared_ptr<Obrona>(tworzEgzemplarz(PodstawoweParametry(atrybut, PodstawoweParametry::ILOSC))));
	}

	STyp::Powierzchnia ObronaInfo::pobierzPowierzchnie(const PodstawoweParametry& parametry)const{
		return Utils::ObliczZmiane(zmianaPowierzchni_, powierzchnia_, parametry);
	}

	std::string ObronaInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(ObronaInfo));
		str.dodajKlase(ObiektInfo::napis());
		str.dodajKlase(JednostkaAtakujacaInfo::napis());
		return str.napis();
	}
}