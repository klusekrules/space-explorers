
#include "JednostkaAtakujaca.h"
#include "Logger.h"

JednostkaAtakujaca::JednostkaAtakujaca( const JednostkaAtakujacaInfo& jInfo )
	: jednostkaAtakujacaInfo(jInfo)
{
}

JednostkaAtakujaca::~JednostkaAtakujaca(){
}


Obrazenia JednostkaAtakujaca::Atak() const {
	return jednostkaAtakujacaInfo.getAtak();
}

Obrazenia JednostkaAtakujaca::Pancerz( const Obrazenia& a ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getPancerz());
	return a > o ? a - o : Obrazenia(0);
}		

Obrazenia JednostkaAtakujaca::Oslona( const Obrazenia& a ) const{
	Obrazenia o (jednostkaAtakujacaInfo.getOslona());
	return a > o ? a - o : Obrazenia(0);
}


string JednostkaAtakujaca::toString() const{
	Logger str(LogJednostkaAtakujaca::className());
	str.addField(JednostkaAtakujacaInfo::LogJednostkaAtakujacaInfo::className()+"ID",jednostkaAtakujacaInfo.getId());
	return str.toString();
}