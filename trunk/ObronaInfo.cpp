#include "ObronaInfo.h"
#include "Logger\Logger.h"
#include "XmlBO.h"
#include "Gra.h"

ObronaInfo::ObronaInfo(	const ObiektInfo& obiektInfo , const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo )
	: ObiektInfo(obiektInfo),JednostkaAtakujacaInfo(jednostkaAtakujacaInfo)
{
}

ObronaInfo::~ObronaInfo()
{
}

ObronaInfo::ObronaInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML)
	: ObiektInfo(wezel),
	JednostkaAtakujacaInfo(XmlBO::ZnajdzWezel<THROW>(wezel,WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO))
{
}

const Identyfikator& ObronaInfo::pobierzIdentyfikator() const{
	return ObiektInfo::pobierzIdentyfikator();
}

Obrona* ObronaInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const{
	return new Obrona(ilosc,pobierzPoziom(), identyfikatorPlanety, *this);
}

bool ObronaInfo::tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc ) const{
	return gra.wybudujNaPlanecie(planeta,*this,ilosc);
}

string ObronaInfo::napis() const{
	Logger str(NAZWAKLASY(ObronaInfo));
	str.dodajKlase(ObiektInfo::napis());
	str.dodajKlase(JednostkaAtakujacaInfo::napis());
	return str.napis();
}