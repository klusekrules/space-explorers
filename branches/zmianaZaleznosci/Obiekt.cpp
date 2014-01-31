#include "Obiekt.h"
#include "Logger\Logger.h"
#include "definicjeWezlowXML.h"
#include "ObronaInfo.h"

namespace SpEx{

	Obiekt::Obiekt(const PodstawoweParametry& parametry, const ObiektInfo& obiektinfo) throw()
		: PodstawoweParametry(parametry), identyfikator_(obiektinfo.pobierzIdentyfikator()), obiektInfo_(obiektinfo)
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

	/*
	bool ObiektBazowy::polacz( const ObiektBazowy& obiektBazowy ){
	if(czyMoznaPolaczyc(obiektBazowy)){
	ilosc_+=obiektBazowy.pobierzIlosc();
	return true;
	}else{
	return false;
	}
	}

	*/

	bool Obiekt::czyMoznaPolaczyc(const Obiekt& obiekt)const{
		return typeid(*this) == typeid(obiekt) && obiekt.pobierzIdentyfikator() == pobierzIdentyfikator() && obiekt.typAtrybutu()==typAtrybutu();
	}


	bool Obiekt::czyMoznaPodzielic(const STyp::Ilosc& ilosc) const{
		return typAtrybutu()==ILOSC && pobierzAtrybut().ilosc > ilosc();
	}

	Wymagania::PrzetworzoneWarunki Obiekt::pobierzKryteriaRozbudowy() const{
		PodstawoweParametry parametry(pobierzAtrybut(), typAtrybutu(), pobierzIdentyfikatorPlanety());
		switch (parametry.typAtrybutu()){
		case ILOSC: parametry.ustawAtrybut(wpisIlosc(1.0));
			break;
		case POZIOM: parametry.ustawAtrybut(wpisPoziom(parametry.pobierzAtrybut().poziom + 1));
			break; 
		}
		return obiektInfo_.pobierzWarunki(parametry);
	}
	
	bool Obiekt::czyMoznaRozbudowac()const{
		PodstawoweParametry parametry(pobierzAtrybut(), typAtrybutu(), pobierzIdentyfikatorPlanety());
		switch (parametry.typAtrybutu()){
		case ILOSC: parametry.ustawAtrybut(wpisIlosc(1.0));
			break;
		case POZIOM: parametry.ustawAtrybut(wpisPoziom(parametry.pobierzAtrybut().poziom + 1));
			break; 
		}
		return obiektInfo_.czySpelniaWymagania(parametry);
	}

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

