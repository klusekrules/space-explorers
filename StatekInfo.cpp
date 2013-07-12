#include "StatekInfo.h"
#include "XmlBO.h"
#include "Gra.h"
#include "definicjeWezlowXML.h"

StatekInfo::StatekInfo( const ObiektInfo& o , const JednostkaLatajacaInfo& j , const JednostkaAtakujacaInfo& a , const LadowniaInfo& l  ) throw()
	: ObiektInfo(o), JednostkaLatajacaInfo(j), JednostkaAtakujacaInfo(a), LadowniaInfo(l)
{
}

StatekInfo::StatekInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: ObiektInfo(n),
	JednostkaLatajacaInfo(XmlBO::ZnajdzWezel<THROW>(n,WEZEL_XML_JEDNOSTKA_LATAJACA_INFO)),
	JednostkaAtakujacaInfo(XmlBO::ZnajdzWezel<THROW>(n,WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO)),
	LadowniaInfo(XmlBO::ZnajdzWezel<THROW>(n,WEZEL_XML_LADOWNIA_INFO))
{
}

StatekInfo::~StatekInfo(){
}

const IdType& StatekInfo::getId() const{
	return ObiektInfo::getId();
}

Statek* StatekInfo::TworzEgzemplarz( const Ilosc& i, const IdType& idP ) const{
	return new Statek(i,getPoziom(), idP, *this);
}

bool StatekInfo::Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const{
	return g.wybudujNaPlanecie(p,*this,i);
}

string StatekInfo::napis() const{
	Logger str(NAZWAKLASY(StatekInfo));
	str.dodajKlase(ObiektInfo::napis());
	str.dodajKlase(JednostkaLatajacaInfo::napis());
	str.dodajKlase(JednostkaAtakujacaInfo::napis());
	str.dodajKlase(LadowniaInfo::napis());
	return str.napis();
}