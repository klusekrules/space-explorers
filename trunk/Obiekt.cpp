#include "Obiekt.h"
#include "ObiektInfo.h"
#include "Logger.h"

Obiekt::Obiekt( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const ObiektInfo& obiektInfo ) throw()
	: PodstawoweParametry(poziom, identyfikatorPlanety), ObiektBazowy( ilosc, poziom, identyfikatorPlanety, obiektInfo ), obiektInfo_( obiektInfo )
{
}

Obiekt::Obiekt( const Ilosc& ilosc, const PodstawoweParametry& podstawoweParametry , const ObiektInfo& obiektInfo ) throw()
	: PodstawoweParametry(podstawoweParametry), ObiektBazowy( ilosc, podstawoweParametry, obiektInfo ), obiektInfo_( obiektInfo )
{
}

Obiekt::~Obiekt(){
}

Obiekt* Obiekt::kopia() const{
	return new Obiekt(*this);
}

Obiekt* Obiekt::podziel( const Ilosc& ilosc ){
	if( ilosc_>ilosc ){
		Obiekt* o = new Obiekt( ilosc , pobierzPoziom(), pobierzIdentyfikatorPlanety(), obiektInfo_ );
		ilosc_-=ilosc;
		return o; 
	}
	return nullptr;
}	

Powierzchnia Obiekt::pobierzPowierzchnie() const{
	return Powierzchnia(obiektInfo_.pobierzPowierzchnie(pobierzPoziom(), pobierzIdentyfikatorPlanety())()*(pobierzIlosc()()));
}

Objetosc Obiekt::pobierzObjetosc() const{
	return Objetosc(obiektInfo_.pobierzObjetosc(pobierzPoziom(), pobierzIdentyfikatorPlanety())()*(pobierzIlosc()()));
}

Objetosc Obiekt::pobierzObjetoscJednostkowa() const{
	return obiektInfo_.pobierzObjetosc(pobierzPoziom(), pobierzIdentyfikatorPlanety());
}

Masa Obiekt::pobierzMase() const{
	return Masa(obiektInfo_.pobierzMase(pobierzPoziom(), pobierzIdentyfikatorPlanety())()*(pobierzIlosc()()));
}

bool Obiekt::zapisz( TiXmlElement* wezel) const{
	return ObiektBazowy::zapisz(wezel);
}

bool Obiekt::odczytaj (TiXmlElement* wezel){
	return ObiektBazowy::odczytaj(wezel);
}

string Obiekt::napis() const{
	Logger str(NAZWAKLASY(Obiekt));
	str.dodajKlase(ObiektBazowy::napis());
	str.dodajPole(NAZWAKLASY(ObiektInfo)+"ID",obiektInfo_.pobierzIdentyfikator());
	return str.napis();
}
