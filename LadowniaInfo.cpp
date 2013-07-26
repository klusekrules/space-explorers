#include "LadowniaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

LadowniaInfo::LadowniaInfo( const Objetosc& maksymalnaObjetosc, const Info& info ) throw()
	: Info(info), pojemnoscMaksymalna_(maksymalnaObjetosc), przyrostPojemnosciMaksymalnej_(nullptr)
{
}

LadowniaInfo::LadowniaInfo( const LadowniaInfo& obiekt )
	: Info(obiekt), pojemnoscMaksymalna_(obiekt.pojemnoscMaksymalna_), przyrostPojemnosciMaksymalnej_(nullptr)
{
}

LadowniaInfo::~LadowniaInfo(){
}

LadowniaInfo::LadowniaInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML)
	: Info(wezel), przyrostPojemnosciMaksymalnej_(nullptr)
{
	if(wezel){
		try{
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_POJEMNOSC_MAKSYMALNA,pojemnoscMaksymalna_);
			przyrostPojemnosciMaksymalnej_ = Aplikacja::getInstance().getGra().pobierzFabrykeZmian().Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_POJEMNOSC_MAKSYMALNA));
		}catch(exception& wyjatek){
			throw WyjatekParseraXML(EXCEPTION_PLACE,wyjatek,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

Objetosc LadowniaInfo::pobierzPojemnoscMaksymalna(const PodstawoweParametry& p ) const{
	if(przyrostPojemnosciMaksymalnej_)
		return Objetosc(przyrostPojemnosciMaksymalnej_->policzWartosc(pojemnoscMaksymalna_(),static_cast<int>(p.pobierzPoziom()()),p.pobierzIdentyfikatorPlanety()()));
	else
		return pojemnoscMaksymalna_;
}
		
string LadowniaInfo::napis() const{
	Logger str(NAZWAKLASY(LadowniaInfo));
	str.dodajKlase(Info::napis());
	str.dodajPole("MaksymalnaPojemnosc",pojemnoscMaksymalna_);
	if(przyrostPojemnosciMaksymalnej_)
		str.dodajPole("ZmianaMaksymalnaPojemnosc",*przyrostPojemnosciMaksymalnej_);
	return str.napis();
}
