
#include "JednostkaLatajaca.h"
#include "Logger.h"

JednostkaLatajaca::JednostkaLatajaca( const IdType& idP, const JednostkaLatajacaInfo& jInfo )
	: idPlanety(idP), jednostkaLatajacaInfo(jInfo)
{
}
JednostkaLatajaca::JednostkaLatajaca( const JednostkaLatajaca& a )
	: idPlanety(a.idPlanety), jednostkaLatajacaInfo(a.jednostkaLatajacaInfo)
{
}
	
JednostkaLatajaca::~JednostkaLatajaca(){
}

ZuzyciePaliwa JednostkaLatajaca::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ,const Poziom& pz  ) const{
	return ZuzyciePaliwa(jednostkaLatajacaInfo.getZuzyciePaliwa(pz,idPlanety).value()* ( d.value() / p.value() ) );
}

ZuzyciePaliwa JednostkaLatajaca::getJednostkoweZuzyciePaliwa( const Poziom& pz  )const{
	return jednostkaLatajacaInfo.getZuzyciePaliwa(pz,idPlanety);
}

MocSilnika JednostkaLatajaca::getMocSilnika( const Poziom& pz  )const{
	return jednostkaLatajacaInfo.getMocSilnika(pz,idPlanety);
}

Masa JednostkaLatajaca::getMasaSilnika( const Poziom& pz  )const{
	return jednostkaLatajacaInfo.getMasaNapedu(pz,idPlanety);
}

Fluktuacja JednostkaLatajaca::getSprawnoscSilnika( const Poziom& pz  )const{
	return jednostkaLatajacaInfo.getSprawnoscSilnika(pz,idPlanety);
}

Predkosc JednostkaLatajaca::PredkoscMaksymalna( const Poziom& p ) const{
	long double eta_m = jednostkaLatajacaInfo.getSprawnoscSilnika(p,idPlanety).value();
	long double a = 0.01;
	long double P = jednostkaLatajacaInfo.getMocSilnika(p,idPlanety).value();
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