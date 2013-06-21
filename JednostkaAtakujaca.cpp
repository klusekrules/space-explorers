
#include "JednostkaAtakujaca.h"
#include "Logger.h"
#include "Aplikacja.h"

JednostkaAtakujaca::JednostkaAtakujaca( const JednostkaAtakujacaInfo& jInfo )
	: jednostkaAtakujacaInfo(jInfo)
{
}

JednostkaAtakujaca::~JednostkaAtakujaca(){
}


Obrazenia JednostkaAtakujaca::Atak(const Poziom& p ) const {
	return Obrazenia( jednostkaAtakujacaInfo.getAtak(p).value() * (std::normal_distribution<>(srednia,odchylenie))(jednostkaAtakujacaInfo.getGenerator()));
}

Obrazenia JednostkaAtakujaca::Pancerz( const Obrazenia& a ,const Poziom& p  ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getPancerz(p));
	return a > o ? a - o : Obrazenia(0);
}		

Obrazenia JednostkaAtakujaca::Oslona( const Obrazenia& a ,const Poziom& p  ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getOslona(p).value() * (std::normal_distribution<>(srednia,odchylenie))(jednostkaAtakujacaInfo.getGenerator()));
	return a > o ? a - o : Obrazenia(0);
}

string JednostkaAtakujaca::toString() const{
	Logger str(CLASSNAME(JednostkaAtakujaca));
	str.addField(CLASSNAME(JednostkaAtakujacaInfo)+"ID",jednostkaAtakujacaInfo.getId());
	return str.toString();
}

const double JednostkaAtakujaca::srednia = 0.8;
const double JednostkaAtakujaca::odchylenie = 0.10;
