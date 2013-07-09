#include "LadowniaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"

LadowniaInfo::LadowniaInfo( const Objetosc& max, const Info& i ) throw()
	: Info(i),pojemnoscMax(max), przyrostPojemnoscMax(nullptr)
{
}

LadowniaInfo::LadowniaInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: Info(XmlBO::IterateChildren<THROW>(n,CLASSNAME(Info))), przyrostPojemnoscMax(nullptr)
{
	if(n){
		try{
			pojemnoscMax.setObjetosc(stold(n->Attribute("pojemnoscMaksymalna")));
			przyrostPojemnoscMax = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenIf<NOTHROW>(n,"Zmiana","for","pojemnoscMaksymalna"));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

Objetosc LadowniaInfo::getPojemnoscMaksymalna(const PodstawoweParametry& p ) const{
	if(przyrostPojemnoscMax)
		return Objetosc(przyrostPojemnoscMax->value(pojemnoscMax.value(),static_cast<int>(p.getPoziom().value()),p.getIdPlanety().value()));
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