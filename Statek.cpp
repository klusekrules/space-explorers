#include "Statek.h"
#include "StatekInfo.h"
#include "Logger.h"

Statek::Statek( const Ilosc& i ,const StatekInfo& s )
	: Obiekt( i,s ), JednostkaAtakujaca(s), JednostkaLatajaca(s), Ladownia(s)
{
}

Statek::~Statek(){
}


string Statek::toString() const{
	Logger str(LogStatek::className());
	str.addClass(Obiekt::toString());
	str.addClass(JednostkaAtakujaca::toString());
	str.addClass(JednostkaLatajaca::toString());
	str.addClass(Ladownia::toString());
	return str.toString();
}
