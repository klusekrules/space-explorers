#include "Statek.h"
#include "StatekInfo.h"
#include "Logger.h"

Statek::Statek( const Ilosc& i ,const StatekInfo& s )
	: Obiekt( i,s ), JednostkaAtakujaca(s), JednostkaLatajaca(s), Ladownia(s), statekinfo(s)
{
}

Statek::~Statek(){
}

ZuzyciePaliwa Statek::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p, const Poziom& pz ) const {
	return ZuzyciePaliwa( ilosc.value() * JednostkaLatajaca::WyliczZuzyciePaliwa(d,p,getPoziom()).value()  );
}

Statek* Statek::Kopia() const{
	return new Statek(*this);
}

Statek* Statek::Podziel( const Ilosc& i ){
	if( ilosc>i ){
		Statek* o = new Statek( i , this->statekinfo );
		ilosc-=i;
		return o; 
	}
	return nullptr;
}	

Obrazenia Statek::Atak( const Poziom& pz ) const {
	return Obrazenia( ilosc.value() * JednostkaAtakujaca::Atak(getPoziom()).value() );
}

Obrazenia Statek::Pancerz( const Obrazenia& a, const Poziom& pz ) const {
	Obrazenia o (JednostkaAtakujaca::Pancerz(a,getPoziom()).value() * ilosc.value());
	return a > o ? a - o : Obrazenia(0);
}

Obrazenia Statek::Oslona( const Obrazenia& a, const Poziom& pz ) const {
	Obrazenia o (JednostkaAtakujaca::Oslona(a, getPoziom()).value() * ilosc.value());
	return a > o ? a - o : Obrazenia(0);
}

Obrazenia Statek::getAtak( const Poziom& pz ) const{
	return Obrazenia (JednostkaAtakujaca::getAtak(getPoziom()).value() * ilosc.value());
}

Obrazenia Statek::getPancerz( const Poziom& pz ) const{
	return Obrazenia (JednostkaAtakujaca::getPancerz(getPoziom()).value() * ilosc.value());
}

Obrazenia Statek::getOslona( const Poziom& pz ) const{
	return Obrazenia (JednostkaAtakujaca::getOslona(getPoziom()).value() * ilosc.value());
}

Objetosc Statek::getPojemnoscMax(  const Poziom& pz ) const{
	return Ladownia::getPojemnoscMax(getPoziom())*getIlosc();
}

Masa Statek::getMasaSilnika( const Poziom& pz  )const{
	return Masa(JednostkaLatajaca::getMasaSilnika(getPoziom()).value()* ilosc.value());
}

ZuzyciePaliwa Statek::getJednostkoweZuzyciePaliwa( const Poziom& pz  )const{
	return ZuzyciePaliwa(JednostkaLatajaca::getJednostkoweZuzyciePaliwa(getPoziom()).value()*ilosc.value() );
}

Masa Statek::getMasa() const{
	return Obiekt::getMasa() + Ladownia::getMasaZawartosciLadowni() + Statek::getMasaSilnika();
}

Fluktuacja Statek::WolneMiejsce( const Poziom& pz ) const{
	return Ladownia::WolneMiejsce(getPoziom());
}

bool Statek::DodajObiektDoLadowni( const Item& i, const Poziom& pz ){
	return Ladownia::DodajObiektDoLadowni(i,getPoziom());
}

bool Statek::czMoznaDodacDoLadownii( const Ladownia& c ) const{
	return c.czMoznaDodacDoLadownii(*this);
}

MocSilnika Statek::getMocSilnika( const Poziom& pz )const{
	return JednostkaLatajaca::getMocSilnika(getPoziom());
}
	
Fluktuacja Statek::getSprawnoscSilnika( const Poziom& pz )const{
	return JednostkaLatajaca::getSprawnoscSilnika(getPoziom());
}

const StatekInfo& Statek::getStatekInfo() const{
	return statekinfo;
}

string Statek::toString() const{
	Logger str(CLASSNAME(Statek));
	str.addClass(Obiekt::toString());
	str.addClass(JednostkaAtakujaca::toString());
	str.addClass(JednostkaLatajaca::toString());
	str.addClass(Ladownia::toString());
	str.addField(CLASSNAME(StatekInfo)+"ID",statekinfo.ID());
	return str.toString();
}
