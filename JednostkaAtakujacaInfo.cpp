#include "JednostkaAtakujacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo(const Info& info, const Obrazenia& oAtak,const Obrazenia& oPancerz, const Obrazenia& oOslona) throw()
	: Info(info), rd(), gen(rd()), atak(oAtak), zmAtak(nullptr), pancerz(oPancerz), zmPancerz(nullptr), oslona(oOslona), zmOslona(nullptr)
{
}
JednostkaAtakujacaInfo::JednostkaAtakujacaInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: Info(n), rd(), gen(rd()),zmAtak(nullptr), zmPancerz(nullptr), zmOslona(nullptr)
{
	if(n){
		try{
			ZmianaFabryka& fabryka = Aplikacja::getInstance().getGra().getZmianaFabryka();
			atak(stold(n->Attribute(ATRYBUT_XML_ATAK)));
			zmAtak = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_ATAK));

			pancerz(stold(n->Attribute(ATRYBUT_XML_PANCERZ)));
			zmPancerz = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_PANCERZ));

			oslona(stold(n->Attribute(ATRYBUT_XML_OSLONA)));
			zmOslona = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_OSLONA));
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