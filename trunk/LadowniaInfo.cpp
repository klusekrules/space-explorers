#include "LadowniaInfo.h"
#include "Logger.h"
#include "XmlBO.h"

LadowniaInfo::LadowniaInfo( const Objetosc& max, const Info& i )
	: Info(i),pojemnoscMax(max), przyrostPojemnoscMax(nullptr)
{
}

LadowniaInfo::LadowniaInfo( ticpp::Node* n )
	: Info(XmlBO::InterateChildren(n,Info::LogInfo::className())), przyrostPojemnoscMax(nullptr)
{
	if(n!=nullptr){
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

Objetosc LadowniaInfo::getPojemnoscMaksymalna() const{
	if(przyrostPojemnoscMax==nullptr)
		return pojemnoscMax;
	else
		return przyrostPojemnoscMax->value(pojemnoscMax);
}
		
string LadowniaInfo::toString() const{
	Logger str(LogLadowniaInfo::className());
	str.addClass(Info::toString());
	str.addField("MaksymalnaPojemnosc",pojemnoscMax);
	if(przyrostPojemnoscMax!=nullptr)
		str.addField("ZmianaMaksymalnaPojemnosc",*przyrostPojemnoscMax);
	return str.toString();
}