#include "ObiektInfo.h"
#include "Logger.h"

ObiektInfo::ObiektInfo( ){
	setObiektInfo(this);
}

ObiektInfo::ObiektInfo( const Masa& masa, const Objetosc& obj, const Powierzchnia& pow, const Info& info, const ObiektBase& base )
	: Base(base), Info(info), Masa(masa), Objetosc(obj), Powierzchnia(pow), ObiektBase(base)
{
	setObiektInfo(nullptr);
}

ObiektInfo::~ObiektInfo(){
}

Obiekt* ObiektInfo::TworzEgzemplarz( const Ilosc& iIlosc ) const {
	Obiekt* o = new Obiekt( *this );
	o->setIlosc(iIlosc.value());
	return o;
}

string ObiektInfo::toString() const{
	Logger str(LogObiektInfo::className());
	str.addClass(Base::toString());
	str.addClass(ObiektBase::toString());
	str.addClass(Logger::reMakeSimpleClassString(Masa::className(),Masa::toString()));
	str.addClass(Logger::reMakeSimpleClassString(Objetosc::className(),Objetosc::toString()));
	str.addClass(Logger::reMakeSimpleClassString(Powierzchnia::className(),Powierzchnia::toString()));
	return str.toString();
}