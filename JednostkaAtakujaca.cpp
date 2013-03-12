
#include "JednostkaAtakujaca.h"
#include "Logger.h"

JednostkaAtakujaca::JednostkaAtakujaca( JednostkaAtakujacaInfo * jInfo )
	: jednostkaAtakujacaInfo(jInfo)
{
}

JednostkaAtakujaca::~JednostkaAtakujaca(){
}


Obrazenia JednostkaAtakujaca::Atak() const throw ( NiezainicjalizowanaKlasa ) {
	if(jednostkaAtakujacaInfo==nullptr)
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,JednostkaAtakujacaInfo::LogJednostkaAtakujacaInfo::className());
	return jednostkaAtakujacaInfo->getAtak();
}

Obrazenia JednostkaAtakujaca::Pancerz( const Obrazenia& a ) const throw ( NiezainicjalizowanaKlasa ){
	if(jednostkaAtakujacaInfo==nullptr)
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,JednostkaAtakujacaInfo::LogJednostkaAtakujacaInfo::className());
	Obrazenia o (jednostkaAtakujacaInfo->getPancerz());
	return a > o ? a - o : Obrazenia(0);
}		

Obrazenia JednostkaAtakujaca::Oslona( const Obrazenia& a ) const throw ( NiezainicjalizowanaKlasa ){
	if(jednostkaAtakujacaInfo==nullptr)
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,JednostkaAtakujacaInfo::LogJednostkaAtakujacaInfo::className());
	Obrazenia o (jednostkaAtakujacaInfo->getOslona());
	return a > o ? a - o : Obrazenia(0);
}

JednostkaAtakujacaInfo* JednostkaAtakujaca::getJednostkaAtakujacaInfo() const{
	return jednostkaAtakujacaInfo;
}

void JednostkaAtakujaca::setJednostkaAtakujacaInfo( JednostkaAtakujacaInfo* i){
	jednostkaAtakujacaInfo = i;
}

string JednostkaAtakujaca::toString() const{
	Logger str(LogJednostkaAtakujaca::className());
	if(this->jednostkaAtakujacaInfo!=nullptr)
		str.addField("JednostkaAtakuj¹caInfo",jednostkaAtakujacaInfo->getId());
	return str.toString();
}