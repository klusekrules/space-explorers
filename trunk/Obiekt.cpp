#include "Obiekt.h"
#include "Logger\Logger.h"
#include "definicjeWezlowXML.h"
#include "ObronaInfo.h"
#include "StackThrow.h"

namespace SpEx{

	Obiekt::Obiekt(const PodstawoweParametry& parametry, const ObiektInfo& obiektinfo) throw()
		: PodstawoweParametry(parametry), identyfikator_(obiektinfo.pobierzIdentyfikator()), obiektInfo_(obiektinfo)
	{
	}
	
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
		if (typAtrybutu() != parametry.typAtrybutu()){
			return false;
		}
		wzrostAtrybutu(parametry.pobierzAtrybut());
		return true;
	}

	STyp::Czas Obiekt::pobierzCzasRozbudowy()const{
		PodstawoweParametry parametry(pobierzAtrybut(), typAtrybutu(), pobierzIdentyfikatorPlanety());
		switch (parametry.typAtrybutu()){
		case ILOSC: parametry.ustawAtrybut(wpisIlosc(1.0));
			break;
		case POZIOM: parametry.ustawAtrybut(wpisPoziom(parametry.pobierzAtrybut().poziom + 1));
			break;
		}
		return obiektInfo_.pobierzCzasBudowy(parametry);
	}

	const STyp::Identyfikator& Obiekt::pobierzIdentyfikator() const{
		return identyfikator_;
	}

	const ObiektInfo& Obiekt::pobierzObiektInfo()const{
		return obiektInfo_;
	}

	void Obiekt::ustawIdentyfikator(const STyp::Identyfikator& identyfikator){
		identyfikator_ = identyfikator;
	}

	bool Obiekt::zapisz(XmlBO::ElementWezla wezel) const{
		if (!PodstawoweParametry::zapisz(wezel)){
			return false;
		}
		return wezel->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(identyfikator_()).c_str()) != nullptr;
	}

	bool Obiekt::odczytaj(XmlBO::ElementWezla wezel){
		if (!PodstawoweParametry::odczytaj(wezel)){
			return false;
		}
		return XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator_);
	}

	std::string Obiekt::napis() const{
		SLog::Logger str(NAZWAKLASY(Obiekt));
		str.dodajKlase(PodstawoweParametry::napis());
		str.dodajPole(NAZWAPOLA(identyfikator_), identyfikator_);
		return str.napis();
	}
}

