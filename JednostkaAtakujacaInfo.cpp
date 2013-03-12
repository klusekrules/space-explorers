#include "JednostkaAtakujacaInfo.h"
#include "Logger.h"

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo(const Info& info, const Obrazenia& oAtak,const Obrazenia& oPancerz, const Obrazenia& oOslona)
	: Info(info), atak(oAtak), pancerz(oPancerz), oslona(oOslona), zmAtak(nullptr), zmPancerz(nullptr), zmOslona(nullptr)
{
}

JednostkaAtakujacaInfo::~JednostkaAtakujacaInfo(){
}

const Obrazenia& JednostkaAtakujacaInfo::getAtak() const{
	return atak;
}
	
const Obrazenia& JednostkaAtakujacaInfo::getPancerz() const{
	return pancerz;
}

const Obrazenia& JednostkaAtakujacaInfo::getOslona() const{
	return oslona;
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