
#include "JednostkaLatajaca.h"
#include "Logger.h"

JednostkaLatajaca::JednostkaLatajaca( const JednostkaLatajacaInfo& jInfo )
	: jednostkaLatajacaInfo(jInfo)
{
}
JednostkaLatajaca::JednostkaLatajaca( const JednostkaLatajaca& a )
	: jednostkaLatajacaInfo(a.jednostkaLatajacaInfo)
{
}
	
JednostkaLatajaca::~JednostkaLatajaca(){
}

ZuzyciePaliwa JednostkaLatajaca::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const{
	return ZuzyciePaliwa(jednostkaLatajacaInfo.getZuzyciePaliwa().value()* ( d.value() / p.value() ) );
}

Predkosc JednostkaLatajaca::PredkoscMaksymalna() const{
	long double eta_m = jednostkaLatajacaInfo.getSprawnoscSilnika().value();
	long double a = 0.01;
	long double P = jednostkaLatajacaInfo.getMocSilnika().value();
	return Predkosc( ( P * eta_m )/(CalkowitaMasaJednostki().value() * a) );
}

Masa JednostkaLatajaca::CalkowitaMasaJednostki() const{
	return Masa();
}

string JednostkaLatajaca::toString() const{
	Logger str(className());
	str.addField("IdJednostkiLatajacej",jednostkaLatajacaInfo.getId());
	return str.toString();
}