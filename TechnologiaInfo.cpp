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

Technologia* TechnologiaInfo::TworzEgzemplarz( const Ilosc& i, const IdType& idP ) const{
	return new Technologia( getPoziom(), idP, *this );
}

bool TechnologiaInfo::Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const{
	return g.wybudujNaPlanecie(p,*this,i);
}

string TechnologiaInfo::toString()const{
	Logger str(CLASSNAME(TechnologiaInfo));
	str.addClass(ObiektBaseInfo::toString());
	return str.toString();
}
