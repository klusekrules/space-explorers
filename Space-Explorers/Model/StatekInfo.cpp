#include "StatekInfo.h"
#include "Planeta.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Logger\Logger.h"
#include "TypyProste\TypyProsteBO.h"
#include "Utils\Utils.h"
#include "Utils\StackThrow.h"

namespace SpEx{
	StatekInfo::StatekInfo(XmlBO::ElementWezla wezel)
		: ObiektInfo(STATEK, typAtrybutu, wezel),
		JednostkaLatajacaInfo(XmlBO::ZnajdzWezel<STACKTHROW>(wezel, WEZEL_XML_JEDNOSTKA_LATAJACA_INFO)),
		JednostkaAtakujacaInfo(XmlBO::ZnajdzWezel<STACKTHROW>(wezel, WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO)),
		LadowniaInfo(XmlBO::ZnajdzWezel<STACKTHROW>(wezel, WEZEL_XML_LADOWNIA_INFO)),
		HangarInfo(XmlBO::ZnajdzWezel<STACKTHROW>(wezel, WEZEL_XML_HANGAR_INFO)), przechowywanyWHangarze_(false)
	{
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_MASA, masa_);
		zmianaMasy_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_MASA));
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA, powierzchnia_);
		zmianaPowierzchni_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_POWIERZCHNIA));
		auto przyrostowy = XmlBO::WczytajAtrybut<int>(wezel, ATRYBUT_XML_HANGAR, -1);
		switch (przyrostowy){
		case 1: przechowywanyWHangarze_ = true;
			break;
		case 0: przechowywanyWHangarze_ = false;
			break;
		default: Utils::generujWyjatekBleduStruktury(wezel);
		}
	}

	bool StatekInfo::czyMoznaDodacDoHangaru() const{
		return przechowywanyWHangarze_();
	}

	const STyp::Identyfikator& StatekInfo::pobierzIdentyfikator() const{
		return ObiektInfo::pobierzIdentyfikator();
	}

	STyp::Powierzchnia StatekInfo::pobierzPowierzchnie(const PodstawoweParametry& parametry)const{
		return STyp::pomnozPrzezIlosc(Utils::ObliczZmiane(zmianaPowierzchni_, powierzchnia_, parametry), parametry.pobierzIlosc());
	}

	STyp::Masa StatekInfo::pobierzMase(const PodstawoweParametry& parametry)const{
		return STyp::pomnozPrzezIlosc(Utils::ObliczZmiane(zmianaMasy_, masa_, parametry), parametry.pobierzIlosc());
	}

	Statek* StatekInfo::tworzEgzemplarz(const PodstawoweParametry& parametry) const{
		return new Statek(parametry, *this);
	}

	bool StatekInfo::tworz(Planeta& planeta, const XmlBO::ElementWezla& element) const{
		auto statek = Statek::SharedPtr(tworzEgzemplarz(PodstawoweParametry(PodstawoweParametry::AtrybutPodstawowy(), typAtrybutu_)));
		if (statek && element){
			if (!statek->odczytaj(element))
				return false;
			return planeta.dodajObiekt<Statek>(statek);
		}
		return false;
	}

	bool StatekInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy& atrybut) const{
		return planeta.dodajObiekt<Statek>(Statek::SharedPtr(tworzEgzemplarz(PodstawoweParametry(atrybut, typAtrybutu_))));
	}

	std::string StatekInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(StatekInfo));
		str.dodajKlase(ObiektInfo::napis());
		str.dodajKlase(JednostkaLatajacaInfo::napis());
		str.dodajKlase(JednostkaAtakujacaInfo::napis());
		str.dodajKlase(LadowniaInfo::napis());
		str.dodajKlase(HangarInfo::napis());
		std::stringstream streamPrzechowywanyWHangarze_;
		streamPrzechowywanyWHangarze_.imbue(std::locale());
		streamPrzechowywanyWHangarze_ << std::boolalpha << przechowywanyWHangarze_();
		str.dodajPole(NAZWAPOLA(przechowywanyWHangarze_), NAZWAKLASY2(przechowywanyWHangarze_), streamPrzechowywanyWHangarze_.str());
		return str.napis();
	}
}
