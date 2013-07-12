#include "TechnologiaInfo.h"
#include "XmlBO.h"
#include "Logger.h"
#include "Gra.h"

TechnologiaInfo::TechnologiaInfo( TiXmlElement* e )
	: ObiektBaseInfo(e)
{
}

TechnologiaInfo::~TechnologiaInfo(void)
{
}

TechnologiaInfo::TechnologiaInfo( const ObiektBaseInfo& o )
	: ObiektBaseInfo(o)
{
}

TechnologiaInfo::TechnologiaInfo( const TechnologiaInfo& o )
	: ObiektBaseInfo(o)
{
}

Technologia* TechnologiaInfo::TworzEgzemplarz( const Ilosc& i, const Identyfikator& idP ) const{
	return new Technologia( getPoziom(), idP, *this );
}

bool TechnologiaInfo::Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const{
	return g.wybudujNaPlanecie(p,*this,i);
}

string TechnologiaInfo::napis()const{
	Logger str(NAZWAKLASY(TechnologiaInfo));
	str.dodajKlase(ObiektBaseInfo::napis());
	return str.napis();
}
