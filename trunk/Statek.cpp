#include "Statek.h"
#include "StatekInfo.h"
#include "Logger.h"
#include "DefinicjeWezlowXML.h"

Statek::Statek( const Ilosc& i, const Poziom& p , const Identyfikator& idP, const StatekInfo& s )
	: PodstawoweParametry(p, idP), Obiekt( i, p, idP, s ), JednostkaAtakujaca(pobierzPoziom(),pobierzIdentyfikatorPlanety(),s), JednostkaLatajaca(pobierzPoziom(),pobierzIdentyfikatorPlanety(),s), Ladownia(pobierzPoziom(),pobierzIdentyfikatorPlanety(),s), statekinfo(s)
{
}

Statek::Statek( const Ilosc& i, const PodstawoweParametry& p, const StatekInfo& s )
	: PodstawoweParametry(p), Obiekt( i, p, s ), JednostkaAtakujaca(p,s), JednostkaLatajaca(p,s), Ladownia(p,s), statekinfo(s)
{
}

ZuzyciePaliwa Statek::wyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p) const {
	return ZuzyciePaliwa( ilosc_() * JednostkaLatajaca::wyliczZuzyciePaliwa(d,p)()  );
}

Statek* Statek::kopia() const{
	return new Statek(*this);
}

//Tranzakcyjna
Statek* Statek::podziel( const Ilosc& i ){
	if( ilosc_>i ){
		Statek* o = new Statek( i , *this, this->statekinfo );
		ilosc_-=i;
		this->przeliczZajeteMiejsce();
		if(this->wolneMiejsce() < Fluktuacja(0.0)){
			Zbiornik zb = this->podzielLadownie( this->zajete_ - this->pobierzPojemnoscMaksymalna(), o->pobierzPojemnoscMaksymalna());
			if( zb.pusty() || !o->obiekty_.przeniesWszystkie(zb) ){
				delete o;
				ilosc_+=i;
				if( !obiekty_.przeniesWszystkie(zb) ){
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("Nieoczekiwany wyjatek"),Tekst("Wystapi³ nieoczekiwany wyjatek, który zaburzy³ dzia³anie aplikacji."));
				}
				this->przeliczZajeteMiejsce();
				return false;
			}
		}
		return o; 
	}
	return nullptr;
}	

//Tranzakcyjna
bool Statek::polacz(const ObiektBazowy& o ){
	if(czyMoznaPolaczyc(o)){
		Statek & t = (Statek&)o;
		t.przeliczZajeteMiejsce();
		this->przeliczZajeteMiejsce();
		if((this->pobierzPojemnoscMaksymalna()+t.pobierzPojemnoscMaksymalna()) >= (t.pobierzZajeteMiejsce()+this->pobierzZajeteMiejsce())){
			if(ObiektBazowy::polacz(o)){
				if(Ladownia::polacz(t)){
					this->przeliczZajeteMiejsce();
					return true;
				}
				ilosc_ -= o.pobierzIlosc();
			}
		}
	}
	return false;
}

Obrazenia Statek::pobierzAtak() const{
	return Obrazenia (JednostkaAtakujaca::pobierzAtak()() * ilosc_());
}

Obrazenia Statek::pobierzPancerz() const{
	return Obrazenia (JednostkaAtakujaca::pobierzPancerz()() * ilosc_());
}

Obrazenia Statek::pobierzOslone() const{
	return Obrazenia (JednostkaAtakujaca::pobierzOslone()() * ilosc_());
}

Objetosc Statek::pobierzPojemnoscMaksymalna() const{
	return Ladownia::pobierzPojemnoscMaksymalna()*pobierzIlosc();
}

Masa Statek::pobierzMasaSilnika()const{
	return Masa(JednostkaLatajaca::pobierzMasaSilnika()()* ilosc_());
}

ZuzyciePaliwa Statek::pobierzJednostkoweZuzyciePaliwa()const{
	return ZuzyciePaliwa(JednostkaLatajaca::pobierzJednostkoweZuzyciePaliwa()()*ilosc_() );
}

Masa Statek::pobierzMase() const{
	return Obiekt::pobierzMase() + Ladownia::pobierzMaseZawartosciLadowni() + Statek::pobierzMasaSilnika();
}

Fluktuacja Statek::wolneMiejsce() const{
	return Ladownia::wolneMiejsce();
}

bool Statek::czMoznaDodacDoLadownii( const Ladownia& c ) const{
	return c.czMoznaDodacDoLadownii(*this);
}

MocSilnika Statek::pobierzMocSilnika()const{
	return JednostkaLatajaca::pobierzMocSilnika();
}
	
Fluktuacja Statek::pobierzSprawnoscSilnika()const{
	return JednostkaLatajaca::pobierzSprawnoscSilnika();
}

const StatekInfo& Statek::getStatekInfo() const{
	return statekinfo;
}

bool Statek::zapisz( TiXmlElement* e ) const {
	TiXmlElement* n = new TiXmlElement(WEZEL_XML_STATEK);
	e->LinkEndChild( n );
	return Obiekt::zapisz(n) && Ladownia::zapisz(n);
}

bool Statek::odczytaj( TiXmlElement* e ) {
	return Obiekt::odczytaj(e) && Ladownia::odczytaj(e->FirstChildElement(WEZEL_XML_LADOWNIA));
}

Masa Statek::calkowitaMasaJednostki() const{
	return Statek::pobierzMase();
}

string Statek::napis() const{
	Logger str(NAZWAKLASY(Statek));
	str.dodajKlase(Obiekt::napis());
	str.dodajKlase(JednostkaAtakujaca::napis());
	str.dodajKlase(JednostkaLatajaca::napis());
	str.dodajKlase(Ladownia::napis());
	str.dodajPole(NAZWAKLASY(StatekInfo)+"ID",statekinfo.getId());
	return str.napis();
}
