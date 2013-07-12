
#include "JednostkaAtakujaca.h"
#include "Logger.h"
#include "Aplikacja.h"

JednostkaAtakujaca::JednostkaAtakujaca( const Poziom& p , const IdType& idP, const JednostkaAtakujacaInfo& jInfo )
	: PodstawoweParametry(p,idP), jednostkaAtakujacaInfo(jInfo)
{
}

JednostkaAtakujaca::JednostkaAtakujaca( const PodstawoweParametry& p, const JednostkaAtakujacaInfo& jInfo )
	: PodstawoweParametry(p), jednostkaAtakujacaInfo(jInfo)
{
}

Obrazenia JednostkaAtakujaca::Atak() const {
	return Obrazenia( jednostkaAtakujacaInfo.getAtak(*this)() * (std::normal_distribution<>(srednia,odchylenie))(jednostkaAtakujacaInfo.getGenerator()));
}

Obrazenia JednostkaAtakujaca::Pancerz( const Obrazenia& a ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getPancerz(*this));
	return a > o ? o : a;
}		

Obrazenia JednostkaAtakujaca::Oslona( const Obrazenia& a ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getOslona(*this)() * (std::normal_distribution<>(srednia,odchylenie))(jednostkaAtakujacaInfo.getGenerator()));
	return a > o ? o : a;
}

string JednostkaAtakujaca::napis() const{
	Logger str(NAZWAKLASY(JednostkaAtakujaca));
	str.dodajPole(NAZWAKLASY(JednostkaAtakujacaInfo)+"ID",jednostkaAtakujacaInfo.getId());
	return str.napis();
}

Obrazenia JednostkaAtakujaca::getAtak() const{
	return jednostkaAtakujacaInfo.getAtak(*this);
}

Obrazenia JednostkaAtakujaca::getPancerz() const{
	return jednostkaAtakujacaInfo.getPancerz(*this);
}

Obrazenia JednostkaAtakujaca:: getOslona() const{
	return jednostkaAtakujacaInfo.getOslona(*this);
}

const double JednostkaAtakujaca::srednia = 0.8;
const double JednostkaAtakujaca::odchylenie = 0.10;
