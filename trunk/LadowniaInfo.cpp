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
		return Objetosc(przyrostPojemnoscMax->policzWartosc(pojemnoscMax(),static_cast<int>(p.pobierzPoziom()()),p.pobierzIdentyfikatorPlanety()()));
	else
		return pojemnoscMax;
}
		
string LadowniaInfo::napis() const{
	Logger str(NAZWAKLASY(LadowniaInfo));
	str.dodajKlase(Info::napis());
	str.dodajPole("MaksymalnaPojemnosc",pojemnoscMax);
	if(przyrostPojemnoscMax!=nullptr)
		str.dodajPole("ZmianaMaksymalnaPojemnosc",*przyrostPojemnoscMax);
	return str.napis();
}