#include "Budynek.h"
#include "BudynekInfo.h"
#include "DefinicjeWezlowXML.h"
#include "Logger\Logger.h"

namespace SpEx{

	Budynek::Budynek(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const BudynekInfo& obiektInfo)
		: PodstawoweParametry(wpisPoziom(poziom), POZIOM, identyfikatorPlanety),
		Obiekt(PodstawoweParametry(wpisPoziom(poziom), POZIOM, identyfikatorPlanety), obiektInfo),
		budynekInfo_(obiektInfo)
	{}

	Budynek::Budynek(const PodstawoweParametry& podstawoweParametry, const BudynekInfo& obiektInfo)
		: PodstawoweParametry(podstawoweParametry), Obiekt(podstawoweParametry, obiektInfo), budynekInfo_(obiektInfo)
	{
	}

	Budynek* Budynek::kopia() const{
		return new Budynek(*this, budynekInfo_);
	}

	Budynek* Budynek::podziel(const STyp::Ilosc& ilosc){
		return nullptr;
	}

	/*bool Budynek::polacz(const ObiektBazowy& obiektbazowy) {
		return false;
	}

	bool Budynek::czyMoznaPolaczyc(const ObiektBazowy& obiektbazowy) const{
		return false;
	}

	bool Budynek::czyMoznaPodzielic(const Ilosc& ilosc) const{
		return false;
	}*/

	Wymagania::PrzetworzoneWarunki Budynek::pobierzZapotrzebowanie()const{
		return budynekInfo_.pobierzZapotrzebowanie(*this);
	}

	Wymagania::PrzetworzoneWarunki Budynek::pobierzProdukcje()const{
		return budynekInfo_.pobierzProdukcje(*this);
	}

	bool Budynek::zapisz(XmlBO::ElementWezla wezel) const {
		if (!wezel)
			return false;
		return Obiekt::zapisz(wezel->tworzElement(WEZEL_XML_BUDYNEK));
	}

	bool Budynek::odczytaj(XmlBO::ElementWezla wezel) {
		return Obiekt::odczytaj(wezel);
	}

	std::string Budynek::napis()const{
		SLog::Logger str(NAZWAKLASY(Budynek));
		str.dodajKlase(Obiekt::napis());
		str.dodajPole(NAZWAPOLA(budynekInfo_), budynekInfo_.pobierzIdentyfikator());
		return str.napis();
	}
}
