#include "StatekInfo.h"
#include "XmlBO.h"
#include "Gra.h"
#include "definicjeWezlowXML.h"

StatekInfo::StatekInfo(	const ObiektInfo& obiektInfo , const JednostkaLatajacaInfo& jednostkaLatajacaInfo , const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo , const LadowniaInfo& ladowniaInfo ) throw()
	: ObiektInfo(obiektInfo), JednostkaLatajacaInfo(jednostkaLatajacaInfo), JednostkaAtakujacaInfo(jednostkaAtakujacaInfo), LadowniaInfo(ladowniaInfo)
{
}

StatekInfo::StatekInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML)
	: ObiektInfo(wezel),
	JednostkaLatajacaInfo(XmlBO::ZnajdzWezel<THROW>(wezel,WEZEL_XML_JEDNOSTKA_LATAJACA_INFO)),
	JednostkaAtakujacaInfo(XmlBO::ZnajdzWezel<THROW>(wezel,WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO)),
	LadowniaInfo(XmlBO::ZnajdzWezel<THROW>(wezel,WEZEL_XML_LADOWNIA_INFO))
{
}

StatekInfo::~StatekInfo(){
}

const Identyfikator& StatekInfo::pobierzIdentyfikator() const{
	return ObiektInfo::pobierzIdentyfikator();
}

Statek* StatekInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const{
	return new Statek(ilosc,pobierzPoziom(), identyfikatorPlanety, *this);
}

bool StatekInfo::tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc ) const{
	return gra.wybudujNaPlanecie(planeta,*this,ilosc);
}

string StatekInfo::napis() const{
	Logger str(NAZWAKLASY(StatekInfo));
	str.dodajKlase(ObiektInfo::napis());
	str.dodajKlase(JednostkaLatajacaInfo::napis());
	str.dodajKlase(JednostkaAtakujacaInfo::napis());
	str.dodajKlase(LadowniaInfo::napis());
	return str.napis();
}
