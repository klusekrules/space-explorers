#include "PodstawoweParametry.h"
#include "Logger\Logger.h"
#include "Utils\Utils.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\StackThrow.h"

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

	PodstawoweParametry::PodstawoweParametry(PodstawoweParametry&& e)
		: atrybutPodstawowy_(std::move(e.atrybutPodstawowy_)), typAtrybutu_(std::move(e.typAtrybutu_)), identyfikatorPlanety_(std::move(e.identyfikatorPlanety_))
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

	PodstawoweParametry::AtrybutPodstawowy PodstawoweParametry::wartoscJednostkowaAtrybutu(TypAtrybutu typ){
		switch (typ)
		{
		case SpEx::PodstawoweParametry::POZIOM:
			return wpisPoziom(STyp::Poziom(1));
			break;
		case SpEx::PodstawoweParametry::ILOSC:
			return wpisIlosc(STyp::Ilosc(1));
			break;
		default:
			break;
		}
		return AtrybutPodstawowy();
	}

	PodstawoweParametry PodstawoweParametry::wartoscJednostkowaParametru(TypAtrybutu typ){
		return PodstawoweParametry(wartoscJednostkowaAtrybutu(typ),typ);
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
		wezel->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR_PLANETY, std::to_string(identyfikatorPlanety_()).c_str());
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

	bool PodstawoweParametry::odczytaj(XmlBO::ElementWezla wezel){
		int opcja = XmlBO::WczytajAtrybut<int>(wezel, ATRYBUT_XML_OPCJA, 0);
		if (opcja == 1)
			return true;
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR_PLANETY, identyfikatorPlanety_);
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
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_ILOSC, ilosc);
			typAtrybutu_ = ILOSC;
			atrybutPodstawowy_.ilosc = ilosc();
		}
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