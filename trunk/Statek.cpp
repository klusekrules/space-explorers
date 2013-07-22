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

ZuzyciePaliwa Statek::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p) const {
	return ZuzyciePaliwa( ilosc_() * JednostkaLatajaca::WyliczZuzyciePaliwa(d,p)()  );
}

Statek* Statek::Kopia() const{
	return new Statek(*this);
}

Statek* Statek::Podziel( const Ilosc& i ){
	if( ilosc_>i ){
		Statek* o = new Statek( i , *this, this->statekinfo );
		ilosc_-=i;
		this->przeliczZajeteMiejsce();
		if(this->WolneMiejsce() < Fluktuacja(0.0)){
			Zbiornik* zb = this->PodzielLadownie(this->zajete-this->getPojemnoscMax(),o->getPojemnoscMax());
			o->obiekty.moveAll(*zb);
		}
		return o; 
	}
	return nullptr;
}	

bool Statek::Polacz(const ObiektBazowy& o ){
	if(czyMoznaPolaczyc(o)){
		Statek & t = (Statek&)o;
		t.przeliczZajeteMiejsce();
		this->przeliczZajeteMiejsce();
		if((this->getPojemnoscMax()+t.getPojemnoscMax()) >= (t.getZajeteMiejsce()+this->getZajeteMiejsce())){
			if(ObiektBazowy::Polacz(o)){
				Ladownia::Polacz(t);
				this->przeliczZajeteMiejsce();
				return true;
			}
		}
	}
	return false;
}

Obrazenia Statek::Atak() const {
	return Obrazenia( ilosc_() * JednostkaAtakujaca::Atak()() );
}

Obrazenia Statek::Pancerz( const Obrazenia& a ) const {
	Obrazenia o (JednostkaAtakujaca::Pancerz(a)() * ilosc_());
	return a > o ? a - o : Obrazenia(0);
}

Obrazenia Statek::Oslona( const Obrazenia& a ) const {
	Obrazenia o (JednostkaAtakujaca::Oslona(a)() * ilosc_());
	return a > o ? a - o : Obrazenia(0);
}

Obrazenia Statek::getAtak() const{
	return Obrazenia (JednostkaAtakujaca::getAtak()() * ilosc_());
}

Obrazenia Statek::getPancerz() const{
	return Obrazenia (JednostkaAtakujaca::getPancerz()() * ilosc_());
}

Obrazenia Statek::getOslona() const{
	return Obrazenia (JednostkaAtakujaca::getOslona()() * ilosc_());
}

Objetosc Statek::getPojemnoscMax() const{
	return Ladownia::getPojemnoscMax()*pobierzIlosc();
}

Masa Statek::getMasaSilnika()const{
	return Masa(JednostkaLatajaca::getMasaSilnika()()* ilosc_());
}

ZuzyciePaliwa Statek::getJednostkoweZuzyciePaliwa()const{
	return ZuzyciePaliwa(JednostkaLatajaca::getJednostkoweZuzyciePaliwa()()*ilosc_() );
}

Masa Statek::getMasa() const{
	return Obiekt::getMasa() + Ladownia::getMasaZawartosciLadowni() + Statek::getMasaSilnika();
}

Fluktuacja Statek::WolneMiejsce() const{
	return Ladownia::WolneMiejsce();
}

bool Statek::DodajObiektDoLadowni( Item& i){
	return Ladownia::DodajObiektDoLadowni(i);
}

bool Statek::czMoznaDodacDoLadownii( const Ladownia& c ) const{
	return c.czMoznaDodacDoLadownii(*this);
}

MocSilnika Statek::getMocSilnika()const{
	return JednostkaLatajaca::getMocSilnika();
}
	
Fluktuacja Statek::getSprawnoscSilnika()const{
	return JednostkaLatajaca::getSprawnoscSilnika();
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

string Statek::napis() const{
	Logger str(NAZWAKLASY(Statek));
	str.dodajKlase(Obiekt::napis());
	str.dodajKlase(JednostkaAtakujaca::napis());
	str.dodajKlase(JednostkaLatajaca::napis());
	str.dodajKlase(Ladownia::napis());
	str.dodajPole(NAZWAKLASY(StatekInfo)+"ID",statekinfo.getId());
	return str.napis();
}
