
#include "JednostkaLatajaca.h"
#include "Logger.h"

JednostkaLatajaca::JednostkaLatajaca( const Poziom& p, const IdType& idP, const JednostkaLatajacaInfo& jInfo )
	: PodstawoweParametry(p,idP), jednostkaLatajacaInfo(jInfo)
{
}
	
JednostkaLatajaca::JednostkaLatajaca( const PodstawoweParametry& p , const JednostkaLatajacaInfo& jInfo )
	: PodstawoweParametry(p), jednostkaLatajacaInfo(jInfo)
{
}

ZuzyciePaliwa JednostkaLatajaca::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const{
	return ZuzyciePaliwa(jednostkaLatajacaInfo.getZuzyciePaliwa(*this).value()* ( d.value() / p.value() ) );
}

ZuzyciePaliwa JednostkaLatajaca::getJednostkoweZuzyciePaliwa()const{
	return jednostkaLatajacaInfo.getZuzyciePaliwa(*this);
}

MocSilnika JednostkaLatajaca::getMocSilnika()const{
	return jednostkaLatajacaInfo.getMocSilnika(*this);
}

Masa JednostkaLatajaca::getMasaSilnika()const{
	return jednostkaLatajacaInfo.getMasaNapedu(*this);
}

Fluktuacja JednostkaLatajaca::getSprawnoscSilnika()const{
	return jednostkaLatajacaInfo.getSprawnoscSilnika(*this);
}

Predkosc JednostkaLatajaca::PredkoscMaksymalna() const{
	long double eta_m = jednostkaLatajacaInfo.getSprawnoscSilnika(*this).value();
	long double a = 0.01;
	long double P = jednostkaLatajacaInfo.getMocSilnika(*this).value();
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