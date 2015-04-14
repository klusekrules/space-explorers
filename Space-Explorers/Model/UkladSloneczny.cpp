#include "UkladSloneczny.h"
#include <random>
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\StackThrow.h"

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
		element->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(identyfikator_()).c_str());
		element->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR_RODZICA, std::to_string(idGalaktyki_()).c_str());
		element->tworzAtrybut(ATRYBUT_XML_SREDNICA_GWIAZDY, std::to_string(srednicaGwiazdy_()).c_str());
		element->tworzAtrybut(ATRYBUT_XML_SREDNICA_GWIAZDY, std::to_string(srednicaGwiazdy_()).c_str());
		element->tworzAtrybut(ATRYBUT_XML_SREDNIA_TEMPERATURA_GWIAZDY, std::to_string(sredniaTemperaturaGwiazdy_()).c_str());
		for (auto planeta : planety_)
		if (!planeta.second->zapisz(element))
			return false;
		return true;
	}

	bool UkladSloneczny::odczytaj(XmlBO::ElementWezla wezel){
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator_);
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR_RODZICA, idGalaktyki_);
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_SREDNICA_GWIAZDY, srednicaGwiazdy_);
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_SREDNIA_TEMPERATURA_GWIAZDY, sredniaTemperaturaGwiazdy_);
		return XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_PLANETA, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
			auto planeta = std::make_shared<SpEx::Planeta>(STyp::Identyfikator(), pobierzIdentyfikator());
			if (!planeta->odczytaj(element))
				return false;
			planety_[planeta->pobierzIdentyfikator()] = planeta;
			return true;
		}));
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
