
#include "JednostkaLatajaca.h"
#include "Logger.h"

JednostkaLatajaca::JednostkaLatajaca( const Poziom& p, const Identyfikator& idP, const JednostkaLatajacaInfo& jInfo )
	: PodstawoweParametry(p,idP), jednostkaLatajacaInfo_(jInfo)
{
}
	
JednostkaLatajaca::JednostkaLatajaca( const PodstawoweParametry& p , const JednostkaLatajacaInfo& jInfo )
	: PodstawoweParametry(p), jednostkaLatajacaInfo_(jInfo)
{
}

JednostkaLatajaca::~JednostkaLatajaca(){
}

ZuzyciePaliwa JednostkaLatajaca::wyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const{
	return ZuzyciePaliwa(jednostkaLatajacaInfo_.pobierzZuzyciePaliwa(*this)()* ( d() / p() ) );
}

ZuzyciePaliwa JednostkaLatajaca::pobierzJednostkoweZuzyciePaliwa()const{
	return jednostkaLatajacaInfo_.pobierzZuzyciePaliwa(*this);
}

MocSilnika JednostkaLatajaca::pobierzMocSilnika()const{
	return jednostkaLatajacaInfo_.pobierzMocSilnika(*this);
}

Masa JednostkaLatajaca::pobierzMasaSilnika()const{
	return jednostkaLatajacaInfo_.pobierzMasaNapedu(*this);
}

Fluktuacja JednostkaLatajaca::pobierzSprawnoscSilnika()const{
	return jednostkaLatajacaInfo_.pobierzSprawnoscSilnika(*this);
}

Predkosc JednostkaLatajaca::predkoscMaksymalna() const{
	long double eta_m = jednostkaLatajacaInfo_.pobierzSprawnoscSilnika(*this)();
	long double a = 0.01;
	long double P = jednostkaLatajacaInfo_.pobierzMocSilnika(*this)();
	return Predkosc( ( P * eta_m )/(calkowitaMasaJednostki()() * a) );
}

Masa JednostkaLatajaca::calkowitaMasaJednostki() const{
	return Masa();
}

string JednostkaLatajaca::napis() const{
	Logger str(NAZWAKLASY(JednostkaLatajaca));
	str.dodajPole(NAZWAKLASY(JednostkaLatajacaInfo)+"ID",jednostkaLatajacaInfo_.pobierzIdentyfikator());
	return str.napis();
}
