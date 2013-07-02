#include "Statek.h"
#include "StatekInfo.h"
#include "Logger.h"

Statek::Statek( const Ilosc& i, const Poziom& p , const IdType& idP, const StatekInfo& s )
	: Obiekt( i, p, idP, s ), JednostkaAtakujaca(getPoziom(),getIdPlanety(),s), JednostkaLatajaca(getPoziom(),getIdPlanety(),s), Ladownia(getPoziom(),getIdPlanety(),s), statekinfo(s)
{
}

Statek::~Statek(){
}

ZuzyciePaliwa Statek::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p) const {
	return ZuzyciePaliwa( ilosc.value() * JednostkaLatajaca::WyliczZuzyciePaliwa(d,p).value()  );
}

Statek* Statek::Kopia() const{
	return new Statek(*this);
}

Statek* Statek::Podziel( const Ilosc& i ){
	if( ilosc>i ){
		Statek* o = new Statek( i , getPoziom(), getIdPlanety(), this->statekinfo );
		ilosc-=i;
		return o; 
	}
	return nullptr;
}	

Obrazenia Statek::Atak() const {
	return Obrazenia( ilosc.value() * JednostkaAtakujaca::Atak().value() );
}

Obrazenia Statek::Pancerz( const Obrazenia& a ) const {
	Obrazenia o (JednostkaAtakujaca::Pancerz(a).value() * ilosc.value());
	return a > o ? a - o : Obrazenia(0);
}

Obrazenia Statek::Oslona( const Obrazenia& a ) const {
	Obrazenia o (JednostkaAtakujaca::Oslona(a).value() * ilosc.value());
	return a > o ? a - o : Obrazenia(0);
}

Obrazenia Statek::getAtak() const{
	return Obrazenia (JednostkaAtakujaca::getAtak().value() * ilosc.value());
}

Obrazenia Statek::getPancerz() const{
	return Obrazenia (JednostkaAtakujaca::getPancerz().value() * ilosc.value());
}

Obrazenia Statek::getOslona() const{
	return Obrazenia (JednostkaAtakujaca::getOslona().value() * ilosc.value());
}

Objetosc Statek::getPojemnoscMax() const{
	return Ladownia::getPojemnoscMax()*getIlosc();
}

Masa Statek::getMasaSilnika()const{
	return Masa(JednostkaLatajaca::getMasaSilnika().value()* ilosc.value());
}

ZuzyciePaliwa Statek::getJednostkoweZuzyciePaliwa()const{
	return ZuzyciePaliwa(JednostkaLatajaca::getJednostkoweZuzyciePaliwa().value()*ilosc.value() );
}

Masa Statek::getMasa() const{
	return Obiekt::getMasa() + Ladownia::getMasaZawartosciLadowni() + Statek::getMasaSilnika();
}

Fluktuacja Statek::WolneMiejsce() const{
	return Ladownia::WolneMiejsce();
}

bool Statek::DodajObiektDoLadowni( const Item& i){
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

string Statek::toString() const{
	Logger str(CLASSNAME(Statek));
	str.addClass(Obiekt::toString());
	str.addClass(JednostkaAtakujaca::toString());
	str.addClass(JednostkaLatajaca::toString());
	str.addClass(Ladownia::toString());
	str.addField(CLASSNAME(StatekInfo)+"ID",statekinfo.getId());
	return str.toString();
}
