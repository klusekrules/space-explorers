#include "Technologia.h"
#include "TechnologiaInfo.h"
#include "DefinicjeWezlowXML.h"
#include "Logger\Logger.h"

namespace SpEx{
	Technologia::Technologia(const PodstawoweParametry& podstawoweParametry, const TechnologiaInfo& technologiaInfo)
		: PodstawoweParametry(podstawoweParametry), Obiekt(podstawoweParametry, technologiaInfo), technologiaInfo_(technologiaInfo)
	{
	}

	Technologia* Technologia::kopia() const{
		return new Technologia(*this, technologiaInfo_);
	}

	Technologia* Technologia::podziel(const STyp::Ilosc& ilosc){
		return nullptr;
	}

	bool Technologia::polacz(const Obiekt& obiektBase){
		return false;
	}

	bool Technologia::czyMoznaPolaczyc(const Obiekt& obiektBase) const{
		return false;
	}

	bool Technologia::czyMoznaPodzielic(const STyp::Ilosc& ilosc) const{
		return false;
	}
	
	bool Technologia::zapisz(XmlBO::ElementWezla wezel) const {
		return Obiekt::zapisz(wezel->tworzElement(WEZEL_XML_TECHNOLOGIA));
	}

	bool Technologia::odczytaj(XmlBO::ElementWezla wezel) {
		return Obiekt::odczytaj(wezel);
	}

	std::string Technologia::napis() const{
		SLog::Logger str(NAZWAKLASY(Technologia));
		str.dodajKlase(Obiekt::napis());
		str.dodajPole(NAZWAPOLA(technologiaInfo_), technologiaInfo_);
		return str.napis();
	}
}