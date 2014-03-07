#include "PodstawoweParametry.h"
#include "Logger\Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include "Walidator.h"

namespace SpEx{

	PodstawoweParametry::PodstawoweParametry(const AtrybutPodstawowy& atrybut, TypAtrybutu typ, const STyp::Identyfikator& planeta)
		: atrybutPodstawowy_(atrybut), typAtrybutu_(typ), identyfikatorPlanety_(planeta)
	{
	}

	PodstawoweParametry::PodstawoweParametry(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety)
		: atrybutPodstawowy_(wpisIlosc(ilosc)), typAtrybutu_(ILOSC), identyfikatorPlanety_(identyfikatorPlanety)
	{
	}

	PodstawoweParametry::PodstawoweParametry(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety)
		: atrybutPodstawowy_(wpisPoziom(poziom)), typAtrybutu_(POZIOM), identyfikatorPlanety_(identyfikatorPlanety)
	{
	}
	
	const PodstawoweParametry::AtrybutPodstawowy& PodstawoweParametry::pobierzAtrybut() const{
		return atrybutPodstawowy_;
	}

	void PodstawoweParametry::ustawAtrybut(const AtrybutPodstawowy& atrybut){
		atrybutPodstawowy_ = atrybut;
	}

	const STyp::Identyfikator& PodstawoweParametry::pobierzIdentyfikatorPlanety() const{
		return identyfikatorPlanety_;
	}

	void PodstawoweParametry::ustawIdentyfikatorPlanety(const STyp::Identyfikator& identyfikatorPlanety){
		identyfikatorPlanety_ = identyfikatorPlanety;
	}

	void PodstawoweParametry::ustawKontekst(const PodstawoweParametry& podstawoweParametry){
		atrybutPodstawowy_ = podstawoweParametry.atrybutPodstawowy_;
		typAtrybutu_ = podstawoweParametry.typAtrybutu_;
		identyfikatorPlanety_ = podstawoweParametry.identyfikatorPlanety_;
	}
	void PodstawoweParametry::wzrostAtrybutu(const AtrybutPodstawowy& atrybut){
		switch (typAtrybutu_){
		case POZIOM: atrybutPodstawowy_.poziom += atrybut.poziom; break;
		case ILOSC:	atrybutPodstawowy_.ilosc += atrybut.ilosc; break;
		}
	}

	PodstawoweParametry::AtrybutPodstawowy PodstawoweParametry::wpisPoziom(const STyp::Poziom& poziom){
		AtrybutPodstawowy atr;
		atr.poziom = poziom();
		return atr;
	}

	PodstawoweParametry::AtrybutPodstawowy PodstawoweParametry::wpisIlosc(const STyp::Ilosc& ilosc){
		AtrybutPodstawowy atr;
		atr.ilosc = ilosc();
		return atr;
	}

	PodstawoweParametry::TypAtrybutu PodstawoweParametry::typAtrybutu()const{
		return typAtrybutu_;
	}

	STyp::Poziom PodstawoweParametry::pobierzPoziom()const{
		return typAtrybutu_ == POZIOM ? atrybutPodstawowy_.poziom : STyp::Poziom(0);
	}
	STyp::Ilosc PodstawoweParametry::pobierzIlosc()const{
		return typAtrybutu_ == ILOSC ? atrybutPodstawowy_.ilosc : STyp::Ilosc(0);
	}

	bool PodstawoweParametry::zapisz(XmlBO::ElementWezla wezel) const{
		wezel->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR_PLANETY, identyfikatorPlanety_.napis().c_str());
		switch (typAtrybutu_){
		case POZIOM:
			if (atrybutPodstawowy_.poziom <= 0)
				return false;
			wezel->tworzAtrybut(ATRYBUT_XML_POZIOM, STyp::Poziom(atrybutPodstawowy_.poziom).napis().c_str());
			break;
		case ILOSC:
			if (atrybutPodstawowy_.ilosc <= 0)
				return false;
			wezel->tworzAtrybut(ATRYBUT_XML_ILOSC, STyp::Ilosc(atrybutPodstawowy_.ilosc).napis().c_str());
			break;
		}
		return true;
	}

	bool PodstawoweParametry::odczytaj(XmlBO::ElementWezla wezel){
		int opcja = XmlBO::WczytajAtrybut<int>(wezel, ATRYBUT_XML_OPCJA, 0);
		if (opcja == 1)
			return true;
		XmlBO::WczytajAtrybut<THROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR_PLANETY, identyfikatorPlanety_);
		STyp::Poziom poziom;
		STyp::Ilosc ilosc;
		if (XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_POZIOM, poziom)){
			if (XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_ILOSC, ilosc)){
				Utils::generujWyjatekBleduStruktury(wezel);
				return false;
			}
			typAtrybutu_ = POZIOM;
			atrybutPodstawowy_.poziom = poziom();
		}else{
			XmlBO::WczytajAtrybut<THROW>(wezel, ATRYBUT_XML_ILOSC, ilosc);
			typAtrybutu_ = ILOSC;
			atrybutPodstawowy_.ilosc = ilosc();
		}
		Walidator::pobierzInstancje().dodajUzytyIdentyfikatorPlanety(identyfikatorPlanety_);
		return true;
	}

	std::string PodstawoweParametry::napis() const{
		SLog::Logger str(NAZWAKLASY(PodstawoweParametry));
		switch (typAtrybutu_){
		case POZIOM: str.dodajPole(NAZWAPOLA(POZIOM), STyp::Poziom(atrybutPodstawowy_.poziom)); break;
		case ILOSC:	str.dodajPole(NAZWAPOLA(ILOSC), STyp::Ilosc(atrybutPodstawowy_.ilosc)); break;
		}
		str.dodajPole(NAZWAPOLA(identyfikatorPlanety_), identyfikatorPlanety_);
		return str.napis();
	}
}