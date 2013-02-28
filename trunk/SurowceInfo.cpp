
#include "SurowceInfo.h"
#include "Logger.h"

SurowceInfo::SurowceInfo()
	: ObiektInfo( )
{
}

SurowceInfo::~SurowceInfo(){
}

SurowceInfo::SurowceInfo( const ObiektInfo& o )
	: ObiektInfo(o)
{
}

SurowceInfo::SurowceInfo( const SurowceInfo& a )
	: ObiektInfo(a)
{
}

Surowce* SurowceInfo::TworzEgzemplarz( const Ilosc& ilosc ) const{
	return new Surowce( ilosc , *this );
}

string SurowceInfo::toString() const{
	Logger str(LogSurowceInfo::className());
	str.addClass(ObiektInfo::toString());
	return str.toString();
}