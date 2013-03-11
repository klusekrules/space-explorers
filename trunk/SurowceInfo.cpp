
#include "SurowceInfo.h"
#include "Logger.h"

SurowceInfo::~SurowceInfo(){
}

SurowceInfo::SurowceInfo( const ObiektInfo& o )
	: Base(o), ObiektInfo(o)
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