#include "LadowniaInfo.h"
#include "Logger.h"
#include "XmlBO.h"

LadowniaInfo::LadowniaInfo( const Objetosc& max, const Info& i )
	: Info(i),pojemnoscMax(max), przyrostPojemnoscMax(nullptr)
{
}

LadowniaInfo::LadowniaInfo( ticpp::Node* n )
	: Info(XmlBO::IterateChildren(n,Info::LogInfo::className())), przyrostPojemnoscMax(nullptr)
{
	if(n){
		try{
			pojemnoscMax.setObjetosc(stold(n->ToElement()->GetAttribute("pojemnoscMaksymalna")));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

LadowniaInfo::~LadowniaInfo()
{
}

Objetosc LadowniaInfo::getPojemnoscMaksymalna(const Poziom& p) const{
	if(przyrostPojemnoscMax==nullptr)
		return pojemnoscMax;
	else
		return Objetosc(przyrostPojemnoscMax->value(pojemnoscMax.value(),p));
}
		
string LadowniaInfo::toString() const{
	Logger str(LogLadowniaInfo::className());
	str.addClass(Info::toString());
	str.addField("MaksymalnaPojemnosc",pojemnoscMax);
	if(przyrostPojemnoscMax!=nullptr)
		str.addField("ZmianaMaksymalnaPojemnosc",*przyrostPojemnoscMax);
	return str.toString();
}