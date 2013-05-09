
#include "JednostkaLatajaca.h"
#include "Logger/Logger.h"

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

ZuzyciePaliwa JednostkaLatajaca::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ,const Poziom& pz  ) const{
	return ZuzyciePaliwa(jednostkaLatajacaInfo.getZuzyciePaliwa(pz).value()* ( d.value() / p.value() ) );
}

Predkosc JednostkaLatajaca::PredkoscMaksymalna( const Poziom& p ) const{
	long double eta_m = jednostkaLatajacaInfo.getSprawnoscSilnika(p).value();
	long double a = 0.01;
	long double P = jednostkaLatajacaInfo.getMocSilnika(p).value();
	return Predkosc( ( P * eta_m )/(CalkowitaMasaJednostki().value() * a) );
}

Masa JednostkaLatajaca::CalkowitaMasaJednostki() const{
	return Masa();
}

string JednostkaLatajaca::toString() const{
	Logger str(CLASSNAME(JednostkaLatajaca));
	str.addField(CLASSNAME(JednostkaLatajacaInfo)+"ID",jednostkaLatajacaInfo.getId());
	return str.toString();
}