
#include "JednostkaAtakujaca.h"
#include "Logger.h"

JednostkaAtakujaca::JednostkaAtakujaca( const JednostkaAtakujacaInfo& jInfo )
	: jednostkaAtakujacaInfo(jInfo)
{
}

JednostkaAtakujaca::~JednostkaAtakujaca(){
}


Obrazenia JednostkaAtakujaca::Atak(const Poziom& p ) const {
	return jednostkaAtakujacaInfo.getAtak(p);
}

Obrazenia JednostkaAtakujaca::Pancerz( const Obrazenia& a ,const Poziom& p  ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getPancerz(p));
	return a > o ? a - o : Obrazenia(0);
}		

Obrazenia JednostkaAtakujaca::Oslona( const Obrazenia& a ,const Poziom& p  ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getOslona(p));
	return a > o ? a - o : Obrazenia(0);
}


string JednostkaAtakujaca::toString() const{
	Logger str(LogJednostkaAtakujaca::className());
	str.addField(JednostkaAtakujacaInfo::LogJednostkaAtakujacaInfo::className()+"ID",jednostkaAtakujacaInfo.getId());
	return str.toString();
}