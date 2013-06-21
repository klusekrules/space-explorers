#include "JednostkaAtakujacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo(const Info& info, const Obrazenia& oAtak,const Obrazenia& oPancerz, const Obrazenia& oOslona) throw()
	: Info(info), rd(), gen(rd()), atak(oAtak), zmAtak(nullptr), pancerz(oPancerz), zmPancerz(nullptr), oslona(oOslona), zmOslona(nullptr)
{
}
JednostkaAtakujacaInfo::JednostkaAtakujacaInfo( ticpp::Node* n ) throw(WyjatekParseraXML)
	: Info(XmlBO::IterateChildren<THROW>(n,CLASSNAME(Info))), rd(), gen(rd()),zmAtak(nullptr), zmPancerz(nullptr), zmOslona(nullptr)
{
	if(n){
		try{
			ticpp::Element* e = n->ToElement();
			atak.setObrazenia(stold(e->GetAttribute("atak")));
			pancerz.setObrazenia(stold(e->GetAttribute("pancerz")));
			oslona.setObrazenia(stold(e->GetAttribute("oslona")));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo( const JednostkaAtakujacaInfo& e )
	: Info(e), rd(), gen(rd()), atak(e.atak), pancerz(e.pancerz), oslona(e.oslona),zmAtak(nullptr), zmPancerz(nullptr), zmOslona(nullptr)
{
}

JednostkaAtakujacaInfo::~JednostkaAtakujacaInfo(){
}

Obrazenia JednostkaAtakujacaInfo::getAtak() const{
	return atak;
}
	
Obrazenia JednostkaAtakujacaInfo::getPancerz() const{
	return pancerz;
}

Obrazenia JednostkaAtakujacaInfo::getOslona() const{
	return oslona;
}

Obrazenia JednostkaAtakujacaInfo::getAtak(const Poziom& p ) const{
	if(zmAtak==nullptr)
		return atak;
	else
		return Obrazenia(zmAtak->value(atak.value(),static_cast<int>(p.value())));
}
	
Obrazenia JednostkaAtakujacaInfo::getPancerz( const Poziom& p ) const{
	if(zmPancerz==nullptr)
		return pancerz;
	else
		return Obrazenia(zmPancerz->value(pancerz.value(),static_cast<int>(p.value())));
}

Obrazenia JednostkaAtakujacaInfo::getOslona(const Poziom& p ) const{
	if(zmOslona==nullptr)
		return oslona;
	else
		return Obrazenia(zmOslona->value(oslona.value(),static_cast<int>(p.value())));
}

std::mt19937& JednostkaAtakujacaInfo::getGenerator()const{
	return gen;
}

string JednostkaAtakujacaInfo::toString() const{
	Logger str(CLASSNAME(JednostkaAtakujacaInfo));
	str.addClass(Info::toString());
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