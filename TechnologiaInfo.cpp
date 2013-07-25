#include "TechnologiaInfo.h"
#include "XmlBO.h"
#include "Logger.h"
#include "Gra.h"

TechnologiaInfo::TechnologiaInfo( TiXmlElement* wezel )
	: ObiektBazowyInfo(wezel)
{
}

TechnologiaInfo::~TechnologiaInfo(void)
{
}

Technologia* TechnologiaInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const{
	return new Technologia( pobierzPoziom(), identyfikatorPlanety, *this );
}

bool TechnologiaInfo::tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc ) const{
	return gra.wybudujNaPlanecie(planeta,*this,ilosc);
}

string TechnologiaInfo::napis()const{
	Logger str(NAZWAKLASY(TechnologiaInfo));
	str.dodajKlase(ObiektBazowyInfo::napis());
	return str.napis();
}
