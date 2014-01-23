#include "Obiekt.h"
#include "Logger\Logger.h"
#include "definicjeWezlowXML.h"

namespace SpEx{

	Obiekt::Obiekt(const PodstawoweParametry& parametry, const STyp::Identyfikator& identyfikator) throw()
		: PodstawoweParametry(parametry), identyfikator_(identyfikator)//, ObiektBazowy(ilosc, poziom, identyfikatorPlanety, obiektInfo), obiektInfo_(obiektInfo)
	{
	}
	
	/*Obiekt* Obiekt::kopia() const{
		return new Obiekt(*this);
	}

	Obiekt* Obiekt::podziel(const STyp::Ilosc& ilosc){
		if ( typAtrybutu() == ILOSC ){
			AtrybutPodstawowy atr;
			atr.ilosc = -ilosc();
			this->wzrostAtrybutu(atr);
			atr.ilosc = -atr.ilosc;
			return new Obiekt(PodstawoweParametry(atr, ILOSC, this->pobierzIdentyfikatorPlanety()), identyfikator_);
		}
		return nullptr;
	}*/

	bool Obiekt::wybuduj(const PodstawoweParametry& parametry){
		if (typAtrybutu() != parametry.typAtrybutu() || parametry.pobierzIdentyfikatorPlanety() != pobierzIdentyfikatorPlanety()){
			return false;
		}
		wzrostAtrybutu(parametry.pobierzAtrybut());
		return true;
	}

	const STyp::Identyfikator& Obiekt::pobierzIdentyfikator() const{
		return identyfikator_;
	}

	void Obiekt::ustawIdentyfikator(const STyp::Identyfikator& identyfikator){
		identyfikator_ = identyfikator;
	}

	bool Obiekt::zapisz(XmlBO::ElementWezla wezel) const{
		if (!PodstawoweParametry::zapisz(wezel)){
			return false;
		}
		return wezel->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, identyfikator_.napis().c_str()) != nullptr;
	}

	bool Obiekt::odczytaj(XmlBO::ElementWezla wezel){
		if (!PodstawoweParametry::odczytaj(wezel)){
			return false;
		}
		return XmlBO::WczytajAtrybut<THROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator_);
	}

	std::string Obiekt::napis() const{
		SLog::Logger str(NAZWAKLASY(Obiekt));
		str.dodajKlase(PodstawoweParametry::napis());
		str.dodajPole(NAZWAPOLA(identyfikator_), identyfikator_);
		return str.napis();
	}
}


/*
bool ObiektBazowy::polacz( const ObiektBazowy& obiektBazowy ){
if(czyMoznaPolaczyc(obiektBazowy)){
ilosc_+=obiektBazowy.pobierzIlosc();
return true;
}else{
return false;
}
}

bool ObiektBazowy::czyMoznaPolaczyc( const ObiektBazowy& obiektBazowy )const{
return typeid(*this) == typeid(obiektBazowy) && obiektBazowy.pobierzIdentyfikator() == pobierzIdentyfikator() && obiektBazowy.pobierzPoziom() == pobierzPoziom();
}

bool ObiektBazowy::czyMoznaPodzielic( const Ilosc& ilosc ) const{
return ilosc_>ilosc;
}

Wymagania::PrzetworzonaCena ObiektBazowy::pobierzKosztyRozbudowy() const{
PodstawoweParametry param(*this);
param.wzrostPoziomu();
return obiektBazowyInfo_.pobierzKoszty(pobierzIlosc(),param);
}

Wymagania::PrzetworzoneWymogi ObiektBazowy::pobierzWarunkiRozbudowy()const{
PodstawoweParametry param(*this);
param.wzrostPoziomu();
return obiektBazowyInfo_.pobierzWymogi(param);
}

bool ObiektBazowy::czyMoznaRozbudowac()const{
PodstawoweParametry param(*this);
param.wzrostPoziomu();
return obiektBazowyInfo_.czySpelniaWymagania(pobierzIlosc(),param);
}

*/