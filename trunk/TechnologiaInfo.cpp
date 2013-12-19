#include "TechnologiaInfo.h"
#include "XmlBO.h"
#include "Logger.h"
#include "Gra.h"

TechnologiaInfo::TechnologiaInfo( tinyxml2::XMLElement* wezel )
	: ObiektBazowyInfo(wezel)
{
}

TechnologiaInfo::~TechnologiaInfo(void)
{
}

Technologia* TechnologiaInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety , const Poziom& poziom ) const{
	return new Technologia( poziom, identyfikatorPlanety, *this );
}

Technologia* TechnologiaInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety  ) const{
	return tworzEgzemplarz( ilosc, identyfikatorPlanety, pobierzPoziom() );
}

bool TechnologiaInfo::tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc , const Poziom& poziom) const{
	return gra.wybudujNaPlanecie(planeta,*this,ilosc,poziom);
}

string TechnologiaInfo::napis()const{
	Logger str(NAZWAKLASY(TechnologiaInfo));
	str.dodajKlase(ObiektBazowyInfo::napis());
	return str.napis();
}
