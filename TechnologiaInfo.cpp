#include "TechnologiaInfo.h"
#include "XmlBO.h"
#include "Logger.h"
#include "Gra.h"

TechnologiaInfo::TechnologiaInfo( TiXmlElement* e )
	: ObiektBazowyInfo(e)
{
}

TechnologiaInfo::~TechnologiaInfo(void)
{
}

TechnologiaInfo::TechnologiaInfo( const ObiektBazowyInfo& o )
	: ObiektBazowyInfo(o)
{
}

TechnologiaInfo::TechnologiaInfo( const TechnologiaInfo& o )
	: ObiektBazowyInfo(o)
{
}

Technologia* TechnologiaInfo::tworzEgzemplarz( const Ilosc& i, const Identyfikator& idP ) const{
	return new Technologia( pobierzPoziom(), idP, *this );
}

bool TechnologiaInfo::tworz( const Gra& g, Planeta& p , const Ilosc& i ) const{
	return g.wybudujNaPlanecie(p,*this,i);
}

string TechnologiaInfo::napis()const{
	Logger str(NAZWAKLASY(TechnologiaInfo));
	str.dodajKlase(ObiektBazowyInfo::napis());
	return str.napis();
}
