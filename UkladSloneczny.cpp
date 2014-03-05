#include "UkladSloneczny.h"
#include <random>
#include "definicjeWezlowXML.h"

namespace SpEx{

	UkladSloneczny::UkladSloneczny(const STyp::Identyfikator& id, const STyp::Identyfikator& idGalaktyki)
		: identyfikator_(id), idGalaktyki_(idGalaktyki)
	{
	}
	
	void UkladSloneczny::ustawSredniceGwiazdy(const STyp::Dystans& srednica){
		srednicaGwiazdy_=srednica;
	}

	const STyp::Dystans& UkladSloneczny::pobierzSredniceGwiazdy() const{
		return srednicaGwiazdy_;
	}

	const STyp::Identyfikator& UkladSloneczny::pobierzIdentyfikator()const{
		return identyfikator_;
	}

	void UkladSloneczny::ustawSredniaTemperatureGwiazdy(const STyp::Temperatura& temperatura){
		sredniaTemperaturaGwiazdy_ = temperatura;
	}

	const STyp::Temperatura& UkladSloneczny::pobierzSredniaTemperatureGwiazdy() const{
		return sredniaTemperaturaGwiazdy_;
	}

	STyp::Moc UkladSloneczny::pobierzMocGwiazdy() const{
		return STyp::Moc(srednicaGwiazdy_()*sredniaTemperaturaGwiazdy_());
	}

	bool UkladSloneczny::dodajPlanete(UkladSloneczny::Planeta planeta){
		if (!planeta || planety_.find(planeta->pobierzIdentyfikator()) != planety_.end())
			return false;
		planety_[planeta->pobierzIdentyfikator()] = planeta;
		return true;
	}

	UkladSloneczny::Planeta UkladSloneczny::pobierzPlanete(const STyp::Identyfikator& numer){
		return planety_[numer];
	}

	int UkladSloneczny::liczbaPlanet() const{
		return static_cast<int>(planety_.size());
	}

	const STyp::Identyfikator& UkladSloneczny::pobierzIdGalaktyki() const{
		return idGalaktyki_;
	}

	bool UkladSloneczny::zapisz(XmlBO::ElementWezla wezel) const{
		auto element = wezel->tworzElement(WEZEL_XML_UKLAD_SLONECZNY);
		element->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, identyfikator_.napis().c_str());
		element->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR_RODZICA, idGalaktyki_.napis().c_str());
		element->tworzAtrybut(ATRYBUT_XML_SREDNICA_GWIAZDY, srednicaGwiazdy_.napis().c_str());
		element->tworzAtrybut(ATRYBUT_XML_SREDNICA_GWIAZDY, srednicaGwiazdy_.napis().c_str());
		element->tworzAtrybut(ATRYBUT_XML_SREDNIA_TEMPERATURA_GWIAZDY, sredniaTemperaturaGwiazdy_.napis().c_str());
		for (auto planeta : planety_)
		if (!planeta.second->zapisz(element))
			return false;
		return true; //TODO: Zapis identyfikatora.
	}

	bool UkladSloneczny::odczytaj(XmlBO::ElementWezla wezel){
		if (wezel){
			XmlBO::WczytajAtrybut<THROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator_);
			XmlBO::WczytajAtrybut<THROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR_RODZICA, idGalaktyki_);
			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_SREDNICA_GWIAZDY, srednicaGwiazdy_))
				return false;
			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_SREDNIA_TEMPERATURA_GWIAZDY, sredniaTemperaturaGwiazdy_))
				return false;
			//TODO:Uzycie foreach.
			for (auto element = wezel->pobierzElement(WEZEL_XML_PLANETA); element; element = element->pobierzNastepnyElement(WEZEL_XML_PLANETA)){
				auto planeta = std::make_shared<SpEx::Planeta>(STyp::Identyfikator(), pobierzIdentyfikator());
				if (!planeta->odczytaj(element))
					return false;
				planety_[planeta->pobierzIdentyfikator()] = planeta;
			}
			return true;
		}
		return false;
	}

	std::string UkladSloneczny::napis() const {
		SLog::Logger str(NAZWAKLASY(UkladSloneczny));
		str.dodajPole(NAZWAPOLA(srednicaGwiazdy_), srednicaGwiazdy_);
		str.dodajPole(NAZWAPOLA(sredniaTemperaturaGwiazdy_), sredniaTemperaturaGwiazdy_);
		for (auto planeta : planety_){
			if (planeta.second){
				str.dodajPole(NAZWAPOLA(planeta), *planeta.second);
			}
		}
		return str.napis();
	}
}
