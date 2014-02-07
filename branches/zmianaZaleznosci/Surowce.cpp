#include "Surowce.h"
#include "SurowceInfo.h"
#include "Logger\Logger.h"
#include "Ladownia.h"
#include "DefinicjeWezlowXML.h"
#include "Aplikacja.h"

namespace SpEx{

	Surowce::Surowce(const STyp::Ilosc& ilosc, const Surowce& obiekt)
		: PodstawoweParametry(wpisIlosc(ilosc), ILOSC, obiekt.pobierzIdentyfikatorPlanety()),
		Obiekt(PodstawoweParametry(wpisIlosc(ilosc), ILOSC, obiekt.pobierzIdentyfikatorPlanety()), obiekt.surowceInfo_),
		surowceInfo_(obiekt.surowceInfo_)
	{
	}

	Surowce::Surowce(const PodstawoweParametry& parametryPodstawowe, const SurowceInfo& surowceInfo)
		: PodstawoweParametry(parametryPodstawowe), Obiekt(parametryPodstawowe, surowceInfo), surowceInfo_(surowceInfo)
	{
	}
	
	Surowce* Surowce::kopia() const{
		return new Surowce(*this);
	}

	bool Surowce::polacz(const Obiekt& obiekt){
		return false;
	}

	STyp::Objetosc Surowce::pobierzObjetosc(const PodstawoweParametry& parametryPodstawowe)const{
		return surowceInfo_.pobierzObjetosc(parametryPodstawowe);
	}

	STyp::Masa Surowce::pobierzMase(const PodstawoweParametry& parametryPodstawowe)const{
		return surowceInfo_.pobierzMase(parametryPodstawowe);
	}

	STyp::Objetosc Surowce::pobierzObjetosc()const{ 
		return pobierzObjetosc(*this);
	}

	STyp::Objetosc Surowce::pobierzObjetoscJednostkowa()const{
		return pobierzObjetosc( PodstawoweParametry( STyp::Ilosc(1),pobierzIdentyfikatorPlanety() ) );
	}

	STyp::Masa Surowce::pobierzMase()const{
		return pobierzMase(*this);
	}

	Surowce* Surowce::podziel(const STyp::Ilosc& ilosc){
		if (ilosc <= STyp::Ilosc(0.0l) || ilosc >= this->pobierzIlosc())
			return nullptr;
		this->wzrostAtrybutu(wpisIlosc( -ilosc ));
		return new Surowce(ilosc, *this);
	}

	Surowce& Surowce::operator=(const Surowce& obiekt)  throw (NiezgodnyTypSurowca) {
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		this->ustawAtrybut(obiekt.pobierzAtrybut());
		return *this;
	}

	bool Surowce::operator==(const Surowce& obiekt) const throw (NiezgodnyTypSurowca){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		return pobierzIlosc() == obiekt.pobierzIlosc();
	}

	bool Surowce::operator!=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		return pobierzIlosc() != obiekt.pobierzIlosc();
	}

	bool Surowce::operator>(const Surowce& obiekt) const throw (NiezgodnyTypSurowca){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		return pobierzIlosc() > obiekt.pobierzIlosc();
	}

	bool Surowce::operator<(const Surowce& obiekt) const throw (NiezgodnyTypSurowca){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		return pobierzIlosc() < obiekt.pobierzIlosc();
	}

	bool Surowce::operator>=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		return pobierzIlosc() >= obiekt.pobierzIlosc();
	}

	bool Surowce::operator<=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		return pobierzIlosc() <= obiekt.pobierzIlosc();
	}

	Surowce Surowce::operator+(const Surowce& obiekt) const throw (NiezgodnyTypSurowca){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		return Surowce(pobierzIlosc() + obiekt.pobierzIlosc(), obiekt);
	}

	Surowce& Surowce::operator+=(const Surowce& obiekt)  throw (NiezgodnyTypSurowca){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		wzrostAtrybutu(wpisIlosc(obiekt.pobierzIlosc()));
		return *this;
	}

	Surowce Surowce::operator-(const Surowce& obiekt) const throw (NiezgodnyTypSurowca){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		return Surowce(pobierzIlosc() - obiekt.pobierzIlosc(), obiekt);
	}

	Surowce& Surowce::operator-=(const Surowce& obiekt) throw (NiezgodnyTypSurowca){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			throw NiezgodnyTypSurowca(EXCEPTION_PLACE, this->pobierzIdentyfikator(), obiekt.pobierzIdentyfikator());
		wzrostAtrybutu(wpisIlosc(-obiekt.pobierzIlosc()));
		return *this;
	}

	bool Surowce::Dodaj(const Surowce& obiekt){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			return false;
		wzrostAtrybutu(wpisIlosc(obiekt.pobierzIlosc()));
		return true;
	}

	bool Surowce::Usun(const Surowce& obiekt){
		if (this->pobierzIdentyfikator() != obiekt.pobierzIdentyfikator())
			return false;
		wzrostAtrybutu(wpisIlosc(-obiekt.pobierzIlosc()));
		return true;
	}

	const SurowceInfo& Surowce::pobierzSurowceInfo() const{
		return surowceInfo_;
	}

	bool Surowce::czyTypPrzyrostowy()const{
		return surowceInfo_.czyTypPrzyrostowy();
	}

	STyp::Czas Surowce::pobierzCzas()const{
		return surowceInfo_.pobierzCzas(*this);
	}

	bool Surowce::zapisz(XmlBO::ElementWezla wezel) const {
		return Obiekt::zapisz(wezel->tworzElement(WEZEL_XML_SUROWCE));
	}

	bool Surowce::odczytaj(XmlBO::ElementWezla wezel) {
		return Obiekt::odczytaj(wezel);
	}

	std::string Surowce::napis() const{
		SLog::Logger str(NAZWAKLASY(Surowce));
		str.dodajKlase(Obiekt::napis());
		str.dodajPole(NAZWAPOLA(surowceInfo_), surowceInfo_);
		return str.napis();
	}
}
