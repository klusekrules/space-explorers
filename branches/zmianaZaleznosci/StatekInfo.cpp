#include "StatekInfo.h"
#include "XmlBO.h"
#include "Gra.h"
#include "definicjeWezlowXML.h"
#include "Logger\Logger.h"

StatekInfo::StatekInfo(	const ObiektInfo& obiektInfo , const JednostkaLatajacaInfo& jednostkaLatajacaInfo , const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo , const LadowniaInfo& ladowniaInfo, const HangarInfo& hangarInfo ) throw()
	: ObiektInfo(obiektInfo), JednostkaLatajacaInfo(jednostkaLatajacaInfo), JednostkaAtakujacaInfo(jednostkaAtakujacaInfo), LadowniaInfo(ladowniaInfo), HangarInfo(hangarInfo),przechowywanyWHangarze_(false)
{
}

StatekInfo::StatekInfo( tinyxml2::XMLElement* wezel ) throw(WyjatekParseraXML)
	: ObiektInfo(wezel),
	JednostkaLatajacaInfo(XmlBO::ZnajdzWezel<THROW>(wezel,WEZEL_XML_JEDNOSTKA_LATAJACA_INFO)),
	JednostkaAtakujacaInfo(XmlBO::ZnajdzWezel<THROW>(wezel,WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO)),
	LadowniaInfo(XmlBO::ZnajdzWezel<THROW>(wezel,WEZEL_XML_LADOWNIA_INFO)),
	HangarInfo(XmlBO::ZnajdzWezel<THROW>(wezel,WEZEL_XML_HANGAR_INFO)),przechowywanyWHangarze_(false)
{
	if(wezel){
		auto przyrostowy = XmlBO::WczytajAtrybut<int>(wezel,ATRYBUT_XML_HANGAR,0);
		switch(przyrostowy){
		case 1 : przechowywanyWHangarze_ = true;
			break;
		case 2 : przechowywanyWHangarze_ = false;
			break;
		default: Utils::generujWyjatekBleduStruktury(EXCEPTION_PLACE,wezel);
		}
	}
}

StatekInfo::~StatekInfo(){
}

bool StatekInfo::czyMoznaDodacDoHangaru() const{
	return przechowywanyWHangarze_();
}

const Identyfikator& StatekInfo::pobierzIdentyfikator() const{
	return ObiektInfo::pobierzIdentyfikator();
}

Statek* StatekInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const{
	return tworzEgzemplarz(ilosc, identyfikatorPlanety,pobierzPoziom());
}

Statek* StatekInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety, const Poziom& poziom ) const{
	return new Statek(ilosc,poziom, identyfikatorPlanety, *this);
}

bool StatekInfo::tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc, const Poziom& poziom ) const{
	return gra.wybudujNaPlanecie(planeta,*this,ilosc, poziom);
}

string StatekInfo::napis() const{
	Logger str(NAZWAKLASY(StatekInfo));
	str.dodajKlase(ObiektInfo::napis());
	str.dodajKlase(JednostkaLatajacaInfo::napis());
	str.dodajKlase(JednostkaAtakujacaInfo::napis());
	str.dodajKlase(LadowniaInfo::napis());
	str.dodajKlase(HangarInfo::napis());
	str.dodajPole("CzyMoznaDodacDoHangaru",przechowywanyWHangarze_);
	return str.napis();
}
