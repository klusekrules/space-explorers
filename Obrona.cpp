#include "Obrona.h"
#include "ObronaInfo.h"
#include "Logger\Logger.h"
#include "DefinicjeWezlowXML.h"

namespace SpEx{

	Obrona::Obrona(const PodstawoweParametry& podstawoweParametry, const ObronaInfo& obronaInfo)
		: PodstawoweParametry(podstawoweParametry), Obiekt(podstawoweParametry, obronaInfo), JednostkaAtakujaca(podstawoweParametry, obronaInfo), obronaInfo_(obronaInfo)
	{
	}

	Obrona* Obrona::kopia() const{
		return new Obrona(*this);
	}

	bool Obrona::polacz(const Obiekt& obiekt){
		return false;
	}

	STyp::Obrazenia Obrona::pobierzAtak() const{
		return STyp::Obrazenia(JednostkaAtakujaca::pobierzAtak()() * pobierzIlosc()());
	}

	Obrona* Obrona::podziel(const STyp::Ilosc& ilosc){
		return nullptr;
	}

	bool Obrona::czyMoznaPolaczyc(const Obiekt& obiektBase) const{
		return false;
	}

	bool Obrona::czyMoznaPodzielic(const STyp::Ilosc& ilosc) const{
		return false;
	}

	STyp::Obrazenia Obrona::pobierzPancerz() const{
		return STyp::Obrazenia(JednostkaAtakujaca::pobierzPancerz()() * pobierzIlosc()());
	}

	STyp::Obrazenia Obrona::pobierzOslone() const{
		return STyp::Obrazenia(JednostkaAtakujaca::pobierzOslone()() * pobierzIlosc()());
	}

	STyp::Powierzchnia Obrona::pobierzPowierzchnie()const{
		return obronaInfo_.pobierzPowierzchnie(*this)() * pobierzIlosc()();
	}

	const ObronaInfo& Obrona::pobierzObronaInfo() const{
		return obronaInfo_;
	}

	bool Obrona::zapisz(XmlBO::ElementWezla wezel) const {
		return Obiekt::zapisz(wezel->tworzElement(WEZEL_XML_OBRONA));
	}

	bool Obrona::odczytaj(XmlBO::ElementWezla wezel) {
		return Obiekt::odczytaj(wezel);
	}

	std::string Obrona::napis() const{
		SLog::Logger str(NAZWAKLASY(Obrona));
		str.dodajKlase(Obiekt::napis());
		str.dodajKlase(JednostkaAtakujaca::napis());
		str.dodajPole(NAZWAPOLA(obronaInfo_), obronaInfo_);
		return str.napis();
	}
}
