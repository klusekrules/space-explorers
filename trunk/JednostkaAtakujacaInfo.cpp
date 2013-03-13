#include "JednostkaAtakujacaInfo.h"
#include "Logger.h"

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo(const Info& info, const Obrazenia& oAtak,const Obrazenia& oPancerz, const Obrazenia& oOslona)
	: Info(info), atak(oAtak), pancerz(oPancerz), oslona(oOslona), zmAtak(nullptr), zmPancerz(nullptr), zmOslona(nullptr)
{
}

JednostkaAtakujacaInfo::~JednostkaAtakujacaInfo(){
}

Obrazenia JednostkaAtakujacaInfo::getAtak() const{
	if(zmAtak==nullptr)
		return atak;
	else
		return zmAtak->value(atak);
}
	
Obrazenia JednostkaAtakujacaInfo::getPancerz() const{
	if(zmPancerz==nullptr)
		return pancerz;
	else
		return zmPancerz->value(pancerz);
}

Obrazenia JednostkaAtakujacaInfo::getOslona() const{
	if(zmOslona==nullptr)
		return oslona;
	else
		return zmOslona->value(oslona);
}

string JednostkaAtakujacaInfo::toString() const{
	Logger str(LogJednostkaAtakujacaInfo::className());
	str.addField("Atak",atak);
	str.addField("Pancerz",pancerz);
	str.addField("Oslona",oslona);
	if(zmAtak!=nullptr)
		str.addField("ZmianaMasy",*zmAtak);
	if(zmPancerz!=nullptr)
		str.addField("ZmianaObjetosci",*zmPancerz);
	if(zmOslona!=nullptr)
		str.addField("ZmianaPowierzchni",*zmOslona);
	return str.toString();
}