#include "ObiektBaseInfo.h"
#include "Logger.h"

ObiektBaseInfo::ObiektBaseInfo(const Info& i , const Poziom& p)
	: Info(i), poziom(p)
{
}


ObiektBaseInfo::~ObiektBaseInfo(){
}


ObiektBase* ObiektBaseInfo::TworzEgzemplarz( const Ilosc& i ) const{
	return new ObiektBase(i,*this);
}

const Poziom& ObiektBaseInfo::getPoziom()const{
	return poziom;
}

string ObiektBaseInfo::toString() const{
	Logger str(LogObiektBaseInfo::className());
	str.addClass(Info::toString());	
	str.addField(poziom.className(),poziom);
	return str.toString();
}
