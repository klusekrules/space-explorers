#include "LadowniaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

LadowniaInfo::LadowniaInfo( const Objetosc& max, const Info& i ) throw()
	: Info(i),pojemnoscMax(max), przyrostPojemnoscMax(nullptr)
{
}

LadowniaInfo::LadowniaInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: Info(n), przyrostPojemnoscMax(nullptr)
{
	if(n){
		try{
			pojemnoscMax(stold(n->Attribute(ATRYBUT_XML_POJEMNOSC_MAKSYMALNA)));
			przyrostPojemnoscMax = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_POJEMNOSC_MAKSYMALNA));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

Objetosc LadowniaInfo::getPojemnoscMaksymalna(const PodstawoweParametry& p ) const{
	if(przyrostPojemnoscMax)
		return Objetosc(przyrostPojemnoscMax->value(pojemnoscMax(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()()));
	else
		return pojemnoscMax;
}
		
string LadowniaInfo::toString() const{
	Logger str(CLASSNAME(LadowniaInfo));
	str.addClass(Info::toString());
	str.addField("MaksymalnaPojemnosc",pojemnoscMax);
	if(przyrostPojemnoscMax!=nullptr)
		str.addField("ZmianaMaksymalnaPojemnosc",*przyrostPojemnoscMax);
	return str.toString();
}