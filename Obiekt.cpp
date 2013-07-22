#include "Obiekt.h"
#include "ObiektInfo.h"
#include "Logger.h"
#include "Ladownia.h"

Obiekt::Obiekt( const Ilosc& i, const Poziom& p, const Identyfikator& idP, const ObiektInfo& obiekt ) throw()
	: PodstawoweParametry(p, idP), ObiektBazowy( i, p, idP, obiekt ), obiektInfoClass( obiekt )
{
}

Obiekt::Obiekt( const Ilosc& i, const PodstawoweParametry&p , const ObiektInfo& obiekt ) throw()
	: PodstawoweParametry(p), ObiektBazowy( i, p, obiekt ), obiektInfoClass( obiekt )
{
}

Obiekt::~Obiekt(){
}

Obiekt* Obiekt::Kopia() const{
	return new Obiekt(*this);
}

Obiekt* Obiekt::Podziel( const Ilosc& i ){
	if( ilosc_>i ){
		Obiekt* o = new Obiekt( i , pobierzPoziom(), pobierzIdentyfikatorPlanety(), this->obiektInfoClass );
		ilosc_-=i;
		return o; 
	}
	return nullptr;
}	
Powierzchnia Obiekt::getPowierzchnia() const{
	return Powierzchnia(obiektInfoClass.pobierzPowierzchnie(pobierzPoziom(), pobierzIdentyfikatorPlanety())()*(this->pobierzIlosc()()));
}

Objetosc Obiekt::getObjetosc() const{
	return Objetosc(obiektInfoClass.pobierzObjetosc(pobierzPoziom(), pobierzIdentyfikatorPlanety())()*(this->pobierzIlosc()()));
}

Masa Obiekt::getMasa() const{
	return Masa(obiektInfoClass.pobierzMase(pobierzPoziom(), pobierzIdentyfikatorPlanety())()*(this->pobierzIlosc()()));
}

bool Obiekt::czMoznaDodacDoLadownii( const Ladownia& c ) const{
	return false;
}

bool Obiekt::zapisz( TiXmlElement* e) const{
	return ObiektBazowy::zapisz(e);
}
bool Obiekt::odczytaj (TiXmlElement* e){
	return ObiektBazowy::odczytaj(e);
}

string Obiekt::napis() const{
	Logger str(NAZWAKLASY(Obiekt));
	str.dodajKlase(ObiektBazowy::napis());
	str.dodajPole(NAZWAKLASY(ObiektInfo)+"ID",obiektInfoClass.pobierzIdentyfikator());
	return str.napis();
}