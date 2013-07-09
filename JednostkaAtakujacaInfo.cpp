#include "JednostkaAtakujacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo(const Info& info, const Obrazenia& oAtak,const Obrazenia& oPancerz, const Obrazenia& oOslona) throw()
	: Info(info), rd(), gen(rd()), atak(oAtak), zmAtak(nullptr), pancerz(oPancerz), zmPancerz(nullptr), oslona(oOslona), zmOslona(nullptr)
{
}
JednostkaAtakujacaInfo::JednostkaAtakujacaInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: Info(XmlBO::ZnajdzWezel<THROW>(n,CLASSNAME(Info))), rd(), gen(rd()),zmAtak(nullptr), zmPancerz(nullptr), zmOslona(nullptr)
{
	if(n){
		try{
			atak(stold(n->Attribute("atak")));
			zmAtak = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,"Zmiana","for","atak"));

			pancerz(stold(n->Attribute("pancerz")));
			zmPancerz = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,"Zmiana","for","pancerz"));

			oslona(stold(n->Attribute("oslona")));
			zmOslona = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,"Zmiana","for","oslona"));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo( const JednostkaAtakujacaInfo& e )
	: Info(e), rd(), gen(rd()), atak(e.atak), pancerz(e.pancerz), oslona(e.oslona),zmAtak(nullptr), zmPancerz(nullptr), zmOslona(nullptr)
{
	if(e.zmAtak)
		zmAtak = shared_ptr<ZmianaInterfejs>(e.zmAtak->Kopia());
	if(e.zmPancerz)
		zmPancerz = shared_ptr<ZmianaInterfejs>(e.zmPancerz->Kopia());
	if(e.zmOslona)
		zmOslona = shared_ptr<ZmianaInterfejs>(e.zmOslona->Kopia());
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

Obrazenia JednostkaAtakujacaInfo::getAtak(const PodstawoweParametry& p ) const{
	if(zmAtak)
		return Obrazenia(zmAtak->value(atak(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()()));
	else
		return atak;
}
	
Obrazenia JednostkaAtakujacaInfo::getPancerz( const PodstawoweParametry& p ) const{
	if(zmPancerz)
		return Obrazenia(zmPancerz->value(pancerz(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()()));
	else
		return pancerz;
}

Obrazenia JednostkaAtakujacaInfo::getOslona(const PodstawoweParametry& p ) const{
	if(zmOslona)
		return Obrazenia(zmOslona->value(oslona(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()()));
	else
		return oslona;
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