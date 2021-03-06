#include "SurowceInfo.h"
#include "Logger\Logger.h"
#include "Planeta.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "TypyProste\TypyProsteBO.h"
#include "Utils\Utils.h"
#include "Utils\StackThrow.h"

namespace SpEx{
	SurowceInfo::SurowceInfo(XmlBO::ElementWezla wezel)
		: ObiektInfo(SUROWIEC, typAtrybutu, wezel), przyrostowy_(false), zmianaCzasu_(nullptr)
	{
		if (wezel){
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_MASA, masa_);
			zmianaMasy_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_MASA));
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_OBJETOSC, objetosc_);
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

	bool SurowceInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy& atrybut) const{
		return planeta.dodajObiekt<Surowce>(Surowce::SharedPtr(tworzEgzemplarz(PodstawoweParametry(atrybut, typAtrybutu_))));
	}

	bool SurowceInfo::tworz(Planeta& planeta, const XmlBO::ElementWezla& element) const{
		auto surowce = Surowce::SharedPtr(tworzEgzemplarz(PodstawoweParametry(PodstawoweParametry::AtrybutPodstawowy(), typAtrybutu_)));
		if (surowce && element){
			if (!surowce->odczytaj(element))
				return false;
			return planeta.dodajObiekt<Surowce>(surowce);
		}
		return false;
	}

	STyp::Czas SurowceInfo::pobierzCzasBudowy(const PodstawoweParametry& parametryPodstawowe)const{
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
		std::stringstream streamPrzyrostowy_;
		streamPrzyrostowy_.imbue(std::locale());
		streamPrzyrostowy_ << std::boolalpha << przyrostowy_();
		str.dodajPole(NAZWAPOLA(przyrostowy_), NAZWAKLASY2(przyrostowy_), streamPrzyrostowy_.str());
		if (zmianaCzasu_)
			str.dodajPole(NAZWAPOLA(zmianaCzasu_), *zmianaCzasu_);
		return str.napis();
	}
}