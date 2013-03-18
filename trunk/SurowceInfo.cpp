
#include "SurowceInfo.h"
#include "Logger.h"
#include "XmlBO.h"

SurowceInfo::~SurowceInfo(){
}

SurowceInfo::SurowceInfo( const ObiektInfo& o )
	: ObiektInfo(o)
{
}

SurowceInfo::SurowceInfo( ticpp::Node* n )
	: ObiektInfo(XmlBO::IterateChildren(n,ObiektInfo::LogObiektInfo::className()))
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