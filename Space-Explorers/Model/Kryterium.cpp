#include "Kryterium.h"
#include "Logger\Logger.h"
#include "Utils\Utils.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\StackThrow.h"

namespace SpEx{

	Kryterium::Kryterium(const AtrybutKryterium& atrybut, TypAtrybutu typ, const STyp::Identyfikator& identyfikator)
		: atrybutPodstawowy_(atrybut), typAtrybutu_(typ), identyfikator_(identyfikator)
	{
	}

	Kryterium::Kryterium(XmlBO::ElementWezla wezel){
		odczytaj(wezel);
	}
	
	Kryterium::Kryterium(Kryterium&& obiekt){
		*this = std::move(obiekt);
	}
	
	Kryterium& Kryterium::operator=(Kryterium&& obiekt){
		if (this != &obiekt)
		{
			typAtrybutu_ = std::move(obiekt.typAtrybutu_);
			atrybutPodstawowy_ = std::move(obiekt.atrybutPodstawowy_);
			identyfikator_ = std::move(obiekt.identyfikator_);
		}
		return *this;
	}

	const Kryterium::AtrybutKryterium& Kryterium::pobierzAtrybut() const{
		return atrybutPodstawowy_;
	}

	void Kryterium::ustawAtrybut(const AtrybutKryterium& atrybut){
		atrybutPodstawowy_ = atrybut;
	}

	const STyp::Identyfikator& Kryterium::pobierzIdentyfikator() const{
		return identyfikator_;
	}

	void Kryterium::ustawIdentyfikator(const STyp::Identyfikator& identyfikator){
		identyfikator_ = identyfikator;
	}

	Kryterium::TypAtrybutu Kryterium::typAtrybutu()const{
		return typAtrybutu_;
	}


	bool Kryterium::zapisz(XmlBO::ElementWezla wezel) const{
		wezel->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(identyfikator_()).c_str());
		switch (typAtrybutu_){
		case POZIOM:
			if (atrybutPodstawowy_.poziom <= 0)
				return false;
			wezel->tworzAtrybut(ATRYBUT_XML_POZIOM, std::to_string(STyp::Poziom(atrybutPodstawowy_.poziom)()).c_str());
			break;
		case ILOSC:
			if (atrybutPodstawowy_.ilosc <= 0)
				return false;
			wezel->tworzAtrybut(ATRYBUT_XML_ILOSC, std::to_string(STyp::Ilosc(atrybutPodstawowy_.ilosc)()).c_str());
			break;
		}
		return true;
	}

	bool Kryterium::odczytaj(XmlBO::ElementWezla wezel){
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator_);
		STyp::Poziom poziom;
		STyp::Ilosc ilosc;
		if (XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_POZIOM, poziom)){
			if (XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_ILOSC, ilosc)){
				Utils::generujWyjatekBleduStruktury(wezel);
				return false;
			}
			typAtrybutu_ = POZIOM;
			atrybutPodstawowy_.poziom = poziom();
		}
		else{
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_ILOSC, ilosc);
			typAtrybutu_ = ILOSC;
			atrybutPodstawowy_.ilosc = ilosc();
		}			
		return true;
	}

	STyp::Poziom Kryterium::pobierzPoziom()const{
		return typAtrybutu_ == POZIOM ? atrybutPodstawowy_.poziom : STyp::Poziom(0);
	}
	STyp::Ilosc Kryterium::pobierzIlosc()const{
		return typAtrybutu_ == ILOSC ? atrybutPodstawowy_.ilosc : STyp::Ilosc(0);
	}
	
	std::string Kryterium::napis() const{
		SLog::Logger str(NAZWAKLASY(Kryterium));
		switch (typAtrybutu_){
		case POZIOM: str.dodajPole(NAZWAPOLA(POZIOM), STyp::Poziom(atrybutPodstawowy_.poziom)); break;
		case ILOSC:	str.dodajPole(NAZWAPOLA(ILOSC), STyp::Ilosc(atrybutPodstawowy_.ilosc)); break;
		}
		str.dodajPole(NAZWAPOLA(identyfikator_), identyfikator_);
		return str.napis();
	}
}