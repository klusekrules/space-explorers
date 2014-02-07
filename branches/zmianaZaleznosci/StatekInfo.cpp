#include "StatekInfo.h"
#include "Gra.h"
#include "definicjeWezlowXML.h"
#include "Logger\Logger.h"

namespace SpEx{
	StatekInfo::StatekInfo(XmlBO::ElementWezla wezel) throw(WyjatekParseraXML)
		: ObiektInfo(wezel),
		JednostkaLatajacaInfo(XmlBO::ZnajdzWezel<THROW>(wezel, WEZEL_XML_JEDNOSTKA_LATAJACA_INFO)),
		JednostkaAtakujacaInfo(XmlBO::ZnajdzWezel<THROW>(wezel, WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO)),
		LadowniaInfo(XmlBO::ZnajdzWezel<THROW>(wezel, WEZEL_XML_LADOWNIA_INFO)),
		HangarInfo(XmlBO::ZnajdzWezel<THROW>(wezel, WEZEL_XML_HANGAR_INFO)), przechowywanyWHangarze_(false)
	{
		if (wezel){
			auto przyrostowy = XmlBO::WczytajAtrybut<int>(wezel, ATRYBUT_XML_HANGAR, 0);
			switch (przyrostowy){
			case 1: przechowywanyWHangarze_ = true;
				break;
			case 2: przechowywanyWHangarze_ = false;
				break;
			default: SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);
			}
		}
	}
	
	bool StatekInfo::czyMoznaDodacDoHangaru() const{
		return przechowywanyWHangarze_();
	}

	const STyp::Identyfikator& StatekInfo::pobierzIdentyfikator() const{
		return ObiektInfo::pobierzIdentyfikator();
	}

	STyp::Powierzchnia StatekInfo::pobierzPowierzchnie(const PodstawoweParametry& parametry)const{
		return Utils::ObliczZmiane(zmianaPowierzchni_, powierzchnia_, parametry);
	}

	STyp::Masa StatekInfo::pobierzMase(const PodstawoweParametry& parametry)const{
		return Utils::ObliczZmiane(zmianaMasy_, masa_, parametry);
	}

	Statek* StatekInfo::tworzEgzemplarz(const PodstawoweParametry& parametry) const{
		return new Statek(parametry, *this);
	}

	bool StatekInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const{
		return false;//gra.wybudujNaPlanecie(planeta, *this, ilosc, poziom);
	}

	std::string StatekInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(StatekInfo));
		str.dodajKlase(ObiektInfo::napis());
		str.dodajKlase(JednostkaLatajacaInfo::napis());
		str.dodajKlase(JednostkaAtakujacaInfo::napis());
		str.dodajKlase(LadowniaInfo::napis());
		str.dodajKlase(HangarInfo::napis());
		str.dodajPole(NAZWAPOLA(przechowywanyWHangarze_), przechowywanyWHangarze_);
		return str.napis();
	}
}
