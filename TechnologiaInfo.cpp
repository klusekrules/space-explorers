#include "TechnologiaInfo.h"
#include "XmlBO.h"
#include "Logger.h"

TechnologiaInfo::TechnologiaInfo( ticpp::Node* e )
	: ObiektBaseInfo(XmlBO::IterateChildren<THROW>(e,CLASSNAME(ObiektBaseInfo)))
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

Technologia* TechnologiaInfo::TworzEgzemplarz( const Ilosc& i ) const{
	return new Technologia( Poziom(0), *this );
}

string TechnologiaInfo::toString()const{
	Logger str(CLASSNAME(TechnologiaInfo));
	str.addClass(ObiektBaseInfo::toString());
	return str.toString();
}
