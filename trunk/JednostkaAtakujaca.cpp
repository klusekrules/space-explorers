
#include "JednostkaAtakujaca.h"
#include "Logger.h"
#include "Aplikacja.h"

JednostkaAtakujaca::JednostkaAtakujaca( const Poziom& p , const IdType& idP, const JednostkaAtakujacaInfo& jInfo )
	: PodstawoweParametry(p,idP), jednostkaAtakujacaInfo(jInfo)
{
}

JednostkaAtakujaca::~JednostkaAtakujaca(){
}


Obrazenia JednostkaAtakujaca::Atak() const {
	return Obrazenia( jednostkaAtakujacaInfo.getAtak(getPoziom(),getIdPlanety()).value() * (std::normal_distribution<>(srednia,odchylenie))(jednostkaAtakujacaInfo.getGenerator()));
}

Obrazenia JednostkaAtakujaca::Pancerz( const Obrazenia& a ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getPancerz(getPoziom(),getIdPlanety()));
	return a > o ? o : a;
}		

Obrazenia JednostkaAtakujaca::Oslona( const Obrazenia& a ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getOslona(getPoziom(),getIdPlanety()).value() * (std::normal_distribution<>(srednia,odchylenie))(jednostkaAtakujacaInfo.getGenerator()));
	return a > o ? o : a;
}

string JednostkaAtakujaca::toString() const{
	Logger str(CLASSNAME(JednostkaAtakujaca));
	str.addField(CLASSNAME(JednostkaAtakujacaInfo)+"ID",jednostkaAtakujacaInfo.getId());
	return str.toString();
}

Obrazenia JednostkaAtakujaca::getAtak() const{
	return jednostkaAtakujacaInfo.getAtak(getPoziom(),getIdPlanety());
}

Obrazenia JednostkaAtakujaca::getPancerz() const{
	return jednostkaAtakujacaInfo.getPancerz(getPoziom(),getIdPlanety());
}

Obrazenia JednostkaAtakujaca:: getOslona() const{
	return jednostkaAtakujacaInfo.getOslona(getPoziom(),getIdPlanety());
}

const double JednostkaAtakujaca::srednia = 0.8;
const double JednostkaAtakujaca::odchylenie = 0.10;
