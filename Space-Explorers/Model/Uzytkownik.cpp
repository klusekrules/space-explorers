#include "Uzytkownik.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Kontroler\Gra.h"
#include "Utils\Utils.h"
#include "Utils\StackThrow.h"

namespace SpEx{
	Uzytkownik::Uzytkownik(Gra& gra)
		: instancjaGry(gra)
	{
	}

	bool Uzytkownik::dodajPlanete(std::shared_ptr<Planeta> planeta){
		auto iterator = planety_.find(planeta->pobierzIdentyfikator());
		if (iterator != planety_.end())
			return false;
		planety_.insert(std::make_pair(planeta->pobierzIdentyfikator(), planeta));
		planeta->ustawWlasciciela(this);
		return true;
	}
	
	bool Uzytkownik::odpinaniePlanet(){
		for (auto &planeta : planety_){
			planeta.second->wyczyscZawartoscPlanety();
		}
		planety_.clear();
		return true;
	}

	bool Uzytkownik::odpinaniePlanet(const STyp::Identyfikator& id){
		auto iterator = planety_.find(id);
		if (iterator == planety_.end())
			return false;
		iterator->second->wyczyscZawartoscPlanety();
		planety_.erase(iterator);
		return true;
	}
	
	bool Uzytkownik::ustawPlaneteAktywna(const STyp::Identyfikator& identyfikator){
		if (planety_.find(identyfikator) == planety_.end())
			return false;
		aktywnaPlaneta_ = identyfikator;
		return true;
	}

	Planeta& Uzytkownik::pobierzPlanete(const STyp::Identyfikator& identyfikator) const{
		auto iterator = planety_.find(identyfikator);
		if (iterator != planety_.end())
			return *(iterator->second);
		throw NieznalezionoObiektu(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), STyp::Tekst("Nieznaleziono planety"));
	}

	Planeta& Uzytkownik::pobierzPlanete(){
		if (!planety_.empty()){
			if (planety_.find(aktywnaPlaneta_) == planety_.end())
				aktywnaPlaneta_ = planety_.begin()->first;
		}
		return pobierzPlanete(aktywnaPlaneta_);
	}

	const STyp::Tekst& Uzytkownik::pobierzNazweUzytkownika()const{
		return nazwaUzytkownika_;
	}

	const STyp::Tekst& Uzytkownik::pobierzSkrotKlucza()const{
		return skrotKlucza_;
	}

	void Uzytkownik::ustawNazweUzytkownika(const STyp::Tekst& nazwa){
		nazwaUzytkownika_ = nazwa;
	}

	bool Uzytkownik::zapisz(XmlBO::ElementWezla wezel) const{
		if (!wezel)
			return false;
		wezel->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwaUzytkownika_().c_str());
		wezel->tworzAtrybut(ATRYBUT_XML_HASH, skrotKlucza_().c_str());
		wezel->tworzAtrybut(ATRYBUT_XML_PLANETA_AKTYWNA, std::to_string(aktywnaPlaneta_()).c_str());
		for (auto planeta : planety_){
			auto element = wezel->tworzElement(WEZEL_XML_PLANETA);
			element->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(planeta.first()).c_str());
		}
		return true;
	}

	bool Uzytkownik::odczytaj(XmlBO::ElementWezla wezel){
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_NAZWA, nazwaUzytkownika_);
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_HASH, skrotKlucza_);
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_PLANETA_AKTYWNA, aktywnaPlaneta_);
		return XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_PLANETA, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
			STyp::Identyfikator idPlanety;
			if (!XmlBO::WczytajAtrybut<NOTHROW>(element, ATRYBUT_XML_IDENTYFIKATOR, idPlanety))
				return false;
			auto planeta = instancjaGry.pobierzPlanete(idPlanety);
			if (!planeta)
				return false;
			planeta->ustawWlasciciela(this);
			planety_[idPlanety] = planeta;
			return true;
		}));
	}

	std::string Uzytkownik::napis() const{
		SLog::Logger str(NAZWAKLASY(Uzytkownik));
		str.dodajPole(NAZWAPOLA(nazwaUzytkownika_), nazwaUzytkownika_);
		str.dodajPole(NAZWAPOLA(skrotKlucza_), skrotKlucza_);
		str.dodajPole(NAZWAPOLA(aktywnaPlaneta_), aktywnaPlaneta_);

		str.rozpocznijPodKlase(NAZWAPOLA(planety_), "SpEx::Uzytkownik::Planety");
		for (auto planeta : planety_){
			str.rozpocznijPodKlase(NAZWAPOLA(planety_), "Para");			
			str.dodajPole("first", planeta.first);
			if (planeta.second){
				std::stringstream streamPlanetaPtr;
				streamPlanetaPtr.imbue(std::locale("C"));
				streamPlanetaPtr << "0x" << std::hex << (unsigned __int64)(planeta.second.get());
				str.dodajPole("second", NAZWAKLASY(Planeta), streamPlanetaPtr.str());
			}else{
				str.dodajPole("second", NAZWAKLASY(Planeta), "nullptr");
			}
			
			str.zakonczPodKlase();
		}
		str.zakonczPodKlase();
		return str.napis();
	}
}
