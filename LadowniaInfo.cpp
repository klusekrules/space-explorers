#include "LadowniaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"

LadowniaInfo::LadowniaInfo( const Objetosc& max, const Info& i ) throw()
	: Info(i),pojemnoscMax(max), przyrostPojemnoscMax(nullptr)
{
}

LadowniaInfo::LadowniaInfo( ticpp::Node* n ) throw(WyjatekParseraXML)
	: Info(XmlBO::IterateChildren<THROW>(n,CLASSNAME(Info))), przyrostPojemnoscMax(nullptr)
{
	if(n){
		try{
			pojemnoscMax.setObjetosc(stold(n->ToElement()->GetAttribute("pojemnoscMaksymalna")));
			przyrostPojemnoscMax = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenElementIf<NOTHROW>(n,"Zmiana","for","pojemnoscMaksymalna"));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

LadowniaInfo::~LadowniaInfo()
{
}

Objetosc LadowniaInfo::getPojemnoscMaksymalna(const Poziom& p, const IdType& idPlanety) const{
	if(przyrostPojemnoscMax==nullptr)
		return pojemnoscMax;
	else
		return Objetosc(przyrostPojemnoscMax->value(pojemnoscMax.value(),static_cast<int>(p.value()),idPlanety.value()));
}
		
string LadowniaInfo::toString() const{
	Logger str(CLASSNAME(LadowniaInfo));
	str.addClass(Info::toString());
	str.addField("MaksymalnaPojemnosc",pojemnoscMax);
	if(przyrostPojemnoscMax!=nullptr)
		str.addField("ZmianaMaksymalnaPojemnosc",*przyrostPojemnoscMax);
	return str.toString();
}