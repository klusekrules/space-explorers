
#include "JednostkaLatajaca.h"
#include "Logger.h"

JednostkaLatajaca::JednostkaLatajaca( const Poziom& p,const IdType& idP, const JednostkaLatajacaInfo& jInfo )
	: poziomObiektu(p),idPlanety(idP), jednostkaLatajacaInfo(jInfo)
{
}
	
JednostkaLatajaca::~JednostkaLatajaca(){
}

ZuzyciePaliwa JednostkaLatajaca::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const{
	return ZuzyciePaliwa(jednostkaLatajacaInfo.getZuzyciePaliwa(poziomObiektu,idPlanety).value()* ( d.value() / p.value() ) );
}

ZuzyciePaliwa JednostkaLatajaca::getJednostkoweZuzyciePaliwa()const{
	return jednostkaLatajacaInfo.getZuzyciePaliwa(poziomObiektu,idPlanety);
}

MocSilnika JednostkaLatajaca::getMocSilnika()const{
	return jednostkaLatajacaInfo.getMocSilnika(poziomObiektu,idPlanety);
}

Masa JednostkaLatajaca::getMasaSilnika()const{
	return jednostkaLatajacaInfo.getMasaNapedu(poziomObiektu,idPlanety);
}

Fluktuacja JednostkaLatajaca::getSprawnoscSilnika()const{
	return jednostkaLatajacaInfo.getSprawnoscSilnika(poziomObiektu,idPlanety);
}

Predkosc JednostkaLatajaca::PredkoscMaksymalna() const{
	long double eta_m = jednostkaLatajacaInfo.getSprawnoscSilnika(poziomObiektu,idPlanety).value();
	long double a = 0.01;
	long double P = jednostkaLatajacaInfo.getMocSilnika(poziomObiektu,idPlanety).value();
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