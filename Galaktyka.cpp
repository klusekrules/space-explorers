#include "Galaktyka.h"
#include "definicjeWezlowXML.h"

namespace SpEx{

	Galaktyka::Galaktyka(const STyp::Identyfikator& identyfikator)
		: identyfikator_(identyfikator)
	{
	}
	
	std::shared_ptr<UkladSloneczny> Galaktyka::pobierzUklad(const STyp::Identyfikator& identyfikator) const{
		auto iter = uklady_.find(identyfikator);
		if (iter != uklady_.end())
			return iter->second;
		return nullptr;
	}

	bool Galaktyka::dodajUklad(std::shared_ptr<UkladSloneczny> uklad){
		auto iter = uklady_.find(uklad->pobierzIdentyfikator());
		if (iter != uklady_.end())
			return false;
		uklady_.insert(make_pair(uklad->pobierzIdentyfikator(), uklad));
		return true;
	}

	bool Galaktyka::zapisz(XmlBO::ElementWezla wezel) const{
		auto element = wezel->tworzElement(WEZEL_XML_GALAKTYKA);
		//TODO: zapisywanie identyfikatora.
		for (auto uklad : uklady_)
		if (!uklad.second->zapisz(element))
			return false;
		return true;
	}

	bool Galaktyka::odczytaj(XmlBO::ElementWezla wezel){
		if (wezel){
			//TODO: Odczytywanie identyfikatora galaktyki.
			//TODO: U¿yæ foreach na wezle.
			for (XmlBO::ElementWezla element = wezel->pobierzElement(WEZEL_XML_UKLAD_SLONECZNY); element; element = element->pobierzNastepnyElement(WEZEL_XML_UKLAD_SLONECZNY)){
				auto uklad = std::make_shared<UkladSloneczny>(STyp::Identyfikator(), pobierzIdentyfikator());
				if (!uklad->odczytaj(element))
					return false;
				auto iter = uklady_.find(uklad->pobierzIdentyfikator());
				if (iter != uklady_.end())
					return false;
				uklady_.insert(std::make_pair(uklad->pobierzIdentyfikator(), uklad));
			}
			return true;
		}
		return false;
	}

	std::string Galaktyka::napis() const{
		SLog::Logger str(NAZWAKLASY(Galaktyka));
		//str.dodajKlase(Bazowa::napis());
		for (auto a : uklady_){
			if (a.second){
				str.dodajPole("Uklad", *a.second);
			}
		}
		return str.napis();
	}
}
