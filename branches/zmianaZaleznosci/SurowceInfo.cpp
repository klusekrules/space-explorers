#include "SurowceInfo.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"
#include "TypyProste\TypyProsteBO.h"

namespace SpEx{
	SurowceInfo::SurowceInfo(XmlBO::ElementWezla wezel)
		: ObiektInfo(wezel), przyrostowy_(false), zmianaCzasu_(nullptr)
	{
		if (wezel){
			XmlBO::WczytajAtrybut<THROW>(wezel, ATRYBUT_XML_MASA, masa_);
			zmianaMasy_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_MASA));
			XmlBO::WczytajAtrybut<THROW>(wezel, ATRYBUT_XML_OBJETOSC, objetosc_);
			zmianaObjetosci_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_OBJETOSC));
			zmianaCzasu_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, WEZEL_XML_CZAS));
			auto przyrostowy = XmlBO::WczytajAtrybut<int>(wezel, ATRYBUT_XML_TYP, -1);
			switch (przyrostowy){
			case 1: przyrostowy_ = true;
				break;
			case 0: przyrostowy_ = false;
				break;
			default: Utils::generujWyjatekBleduStruktury(wezel);
			}
		}
	}

	bool SurowceInfo::czyTypPrzyrostowy()const{
		return przyrostowy_();
	}

	bool SurowceInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const{
		return planeta.dodajObiekt(std::shared_ptr<Surowce>(tworzEgzemplarz(PodstawoweParametry(atrybut,PodstawoweParametry::ILOSC))));
	}

	bool SurowceInfo::tworz(Planeta& planeta, const XmlBO::ElementWezla element) const{
		auto surowce = std::shared_ptr<Surowce>(tworzEgzemplarz(PodstawoweParametry(PodstawoweParametry::AtrybutPodstawowy(), PodstawoweParametry::ILOSC)));
		if (surowce && element){
			if (!surowce->odczytaj(element))
				return false;
			return planeta.dodajObiekt(surowce);
		}
		return false;
	}

	STyp::Czas SurowceInfo::pobierzCzas(const PodstawoweParametry& parametryPodstawowe)const{
		return Utils::ObliczZmiane(zmianaCzasu_, STyp::Czas(parametryPodstawowe.pobierzIlosc()), parametryPodstawowe);
	}

	Surowce* SurowceInfo::tworzEgzemplarz(const PodstawoweParametry& parametryPodstawowe) const{
		return new Surowce(parametryPodstawowe, *this);
	}

	STyp::Objetosc SurowceInfo::pobierzObjetosc(const PodstawoweParametry& parametry)const{
		return STyp::pomnozPrzezIlosc(Utils::ObliczZmiane(zmianaObjetosci_, objetosc_, parametry), parametry.pobierzIlosc());
	}

	STyp::Masa SurowceInfo::pobierzMase(const PodstawoweParametry& parametry)const{
		return STyp::pomnozPrzezIlosc(Utils::ObliczZmiane(zmianaMasy_, masa_, parametry), parametry.pobierzIlosc());
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