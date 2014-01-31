#include "SurowceInfo.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

namespace SpEx{
	SurowceInfo::SurowceInfo(XmlBO::ElementWezla wezel) throw(WyjatekParseraXML)
		: ObiektInfo(wezel), przyrostowy_(false), zmianaCzasu_(nullptr)
	{
		if (wezel){
			zmianaCzasu_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, WEZEL_XML_CZAS));
			auto przyrostowy = XmlBO::WczytajAtrybut<int>(wezel, ATRYBUT_XML_TYP, 0);
			switch (przyrostowy){
			case 1: przyrostowy_ = true;
				break;
			case 2: przyrostowy_ = false;
				break;
			default: SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);
			}
		}
	}

	bool SurowceInfo::czyTypPrzyrostowy()const{
		return przyrostowy_();
	}

	bool SurowceInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const const{
		return false; //gra.wybudujNaPlanecie(planeta, *this, ilosc, poziom);
	}

	STyp::Czas SurowceInfo::pobierzCzas(const PodstawoweParametry& parametryPodstawowe)const{
		return Utils::ObliczZmiane(zmianaCzasu_, STyp::Czas(parametryPodstawowe.pobierzIlosc()), parametryPodstawowe);
	}

	Surowce* SurowceInfo::tworzEgzemplarz(const PodstawoweParametry& parametryPodstawowe) const{
		return new Surowce(parametryPodstawowe, *this);
	}
	
	std::string SurowceInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(SurowceInfo));
		str.dodajKlase(ObiektInfo::napis());
		str.dodajPole(NAZWAPOLA(przyrostowy_), przyrostowy_);
		if (zmianaCzasu_)
			str.dodajPole(NAZWAPOLA(zmianaCzasu_), *zmianaCzasu_);
		return str.napis();
	}
}