#include "JednostkaAtakujacaInfo.h"
#include "Logger.h"

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo(){
}

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo(const Info& info, const Obrazenia& oAtak,const Obrazenia& oPancerz, const Obrazenia& oOslona)
	: Info(info), atak(oAtak), pancerz(oPancerz), oslona(oOslona)
{
}

JednostkaAtakujacaInfo::~JednostkaAtakujacaInfo(){
}

Obrazenia JednostkaAtakujacaInfo::getAtak() const{
	return atak;
}
	
void JednostkaAtakujacaInfo::setAtak( const Obrazenia& wzAtak ){
	atak = wzAtak;
}
	
Obrazenia JednostkaAtakujacaInfo::getPancerz() const{
	return pancerz;
}
	
void JednostkaAtakujacaInfo::setPancerz( const Obrazenia& wzPancerz ){
	pancerz = wzPancerz;
}
	
Obrazenia JednostkaAtakujacaInfo::getOslona() const{
	return oslona;
}
	
void JednostkaAtakujacaInfo::setOslona( const Obrazenia& wzOslona ){
	oslona = wzOslona;
}

string JednostkaAtakujacaInfo::toString() const{
	Logger str(LogJednostkaAtakujacaInfo::className());
	str.addField("Atak",atak);
	str.addField("Pancerz",pancerz);
	str.addField("Oslona",oslona);
	return str.toString();
}