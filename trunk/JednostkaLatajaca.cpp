
#include "JednostkaLatajaca.h"
#include "Logger.h"

JednostkaLatajaca::JednostkaLatajaca( const Poziom& p, const IdType& idP, const JednostkaLatajacaInfo& jInfo )
	: PodstawoweParametry(p,idP), jednostkaLatajacaInfo(jInfo)
{
}
	
JednostkaLatajaca::~JednostkaLatajaca(){
}

ZuzyciePaliwa JednostkaLatajaca::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const{
	return ZuzyciePaliwa(jednostkaLatajacaInfo.getZuzyciePaliwa(getPoziom(),getIdPlanety()).value()* ( d.value() / p.value() ) );
}

ZuzyciePaliwa JednostkaLatajaca::getJednostkoweZuzyciePaliwa()const{
	return jednostkaLatajacaInfo.getZuzyciePaliwa(getPoziom(),getIdPlanety());
}

MocSilnika JednostkaLatajaca::getMocSilnika()const{
	return jednostkaLatajacaInfo.getMocSilnika(getPoziom(),getIdPlanety());
}

Masa JednostkaLatajaca::getMasaSilnika()const{
	return jednostkaLatajacaInfo.getMasaNapedu(getPoziom(),getIdPlanety());
}

Fluktuacja JednostkaLatajaca::getSprawnoscSilnika()const{
	return jednostkaLatajacaInfo.getSprawnoscSilnika(getPoziom(),getIdPlanety());
}

Predkosc JednostkaLatajaca::PredkoscMaksymalna() const{
	long double eta_m = jednostkaLatajacaInfo.getSprawnoscSilnika(getPoziom(),getIdPlanety()).value();
	long double a = 0.01;
	long double P = jednostkaLatajacaInfo.getMocSilnika(getPoziom(),getIdPlanety()).value();
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