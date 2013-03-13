#include "Statek.h"
#include "StatekInfo.h"
#include "Logger.h"

Statek::Statek( const Ilosc& i ,const StatekInfo& s )
	: Obiekt( i,s ), JednostkaAtakujaca(s), JednostkaLatajaca(s), Ladownia(s)
{
}

Statek::~Statek(){
}

ZuzyciePaliwa Statek::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const {
	return ZuzyciePaliwa( ilosc.value() * JednostkaLatajaca::WyliczZuzyciePaliwa(d,p).value()  );
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

string Statek::toString() const{
	Logger str(LogStatek::className());
	str.addClass(Obiekt::toString());
	str.addClass(JednostkaAtakujaca::toString());
	str.addClass(JednostkaLatajaca::toString());
	str.addClass(Ladownia::toString());
	return str.toString();
}
