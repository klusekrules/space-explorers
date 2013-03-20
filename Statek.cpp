#include "Statek.h"
#include "StatekInfo.h"
#include "Logger.h"

Statek::Statek( const Ilosc& i ,const StatekInfo& s )
	: Obiekt( i,s ), JednostkaAtakujaca(s), JednostkaLatajaca(s), Ladownia(s), statekinfo(s)
{
}

Statek::~Statek(){
}

ZuzyciePaliwa Statek::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const {
	return ZuzyciePaliwa( ilosc.value() * JednostkaLatajaca::WyliczZuzyciePaliwa(d,p).value()  );
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


Obrazenia Statek::Atak() const {
	return Obrazenia( ilosc.value() * JednostkaAtakujaca::Atak().value() );
}

Obrazenia Statek::Pancerz( const Obrazenia& a ) const {
	Obrazenia o (jednostkaAtakujacaInfo.getPancerz().value() * ilosc.value());
	return a > o ? a - o : Obrazenia(0);
}

Obrazenia Statek::Oslona( const Obrazenia& a ) const {
	Obrazenia o (jednostkaAtakujacaInfo.getOslona().value() * ilosc.value());
	return a > o ? a - o : Obrazenia(0);
}

Objetosc Statek::getPojemnoscMax() const{
	return ladowniaInfo.getPojemnoscMaksymalna()*getIlosc();
}

string Statek::toString() const{
	Logger str(LogStatek::className());
	str.addClass(Obiekt::toString());
	str.addClass(JednostkaAtakujaca::toString());
	str.addClass(JednostkaLatajaca::toString());
	str.addClass(Ladownia::toString());
	str.addField(StatekInfo::LogStatekInfo::className()+"ID",statekinfo.ID());
	return str.toString();
}
