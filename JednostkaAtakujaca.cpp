
#include "JednostkaAtakujaca.h"
#include "Logger.h"
#include "Aplikacja.h"

JednostkaAtakujaca::JednostkaAtakujaca( const IdType& idP, const JednostkaAtakujacaInfo& jInfo )
	: idPlanety(idP), jednostkaAtakujacaInfo(jInfo)
{
}

JednostkaAtakujaca::~JednostkaAtakujaca(){
}


Obrazenia JednostkaAtakujaca::Atak(const Poziom& p ) const {
	return Obrazenia( jednostkaAtakujacaInfo.getAtak(p,idPlanety).value() * (std::normal_distribution<>(srednia,odchylenie))(jednostkaAtakujacaInfo.getGenerator()));
}

Obrazenia JednostkaAtakujaca::Pancerz( const Obrazenia& a ,const Poziom& p  ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getPancerz(p,idPlanety));
	return a > o ? o : a;
}		

Obrazenia JednostkaAtakujaca::Oslona( const Obrazenia& a ,const Poziom& p  ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getOslona(p,idPlanety).value() * (std::normal_distribution<>(srednia,odchylenie))(jednostkaAtakujacaInfo.getGenerator()));
	return a > o ? o : a;
}

string JednostkaAtakujaca::toString() const{
	Logger str(CLASSNAME(JednostkaAtakujaca));
	str.addField(CLASSNAME(JednostkaAtakujacaInfo)+"ID",jednostkaAtakujacaInfo.getId());
	return str.toString();
}

Obrazenia JednostkaAtakujaca::getAtak( const Poziom& p ) const{
	return jednostkaAtakujacaInfo.getAtak(p,idPlanety);
}

Obrazenia JednostkaAtakujaca::getPancerz( const Poziom& p  ) const{
	return jednostkaAtakujacaInfo.getPancerz(p,idPlanety);
}

Obrazenia JednostkaAtakujaca:: getOslona( const Poziom& p ) const{
	return jednostkaAtakujacaInfo.getOslona(p,idPlanety);
}

const double JednostkaAtakujaca::srednia = 0.8;
const double JednostkaAtakujaca::odchylenie = 0.10;
