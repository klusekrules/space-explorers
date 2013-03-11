#include "ObiektBase.h"
#include "ObiektInfo.h"
#include "Logger.h"

ObiektBase::ObiektBase( const Ilosc& i, const Poziom & pPoziom, const Info& iInfo)
	: Base(iInfo), Ilosc(i), Poziom(pPoziom), info(iInfo)
{
}

ObiektBase::~ObiektBase( ){
}

ObiektBase* ObiektBase::Kopia() const{
	return new ObiektBase(*this);
}

ObiektBase* ObiektBase::Podziel( const Ilosc& i ){
	if( czyMoznaPodzielic(i) ){
		Ilosc::operator-=(i);
		return new ObiektBase( i ,*this, info );
	}
	return nullptr;
}

bool ObiektBase::Polacz( const ObiektBase& obj ){
	if(czyMoznaPolaczyc(obj)){
		Ilosc::operator+=(obj);
		return true;
	}else{
		return false;
	}
}
		
Klucz ObiektBase::ID() const{
	return Klucz( *this , *this );
}


bool ObiektBase::czyMoznaPolaczyc( const ObiektBase& objBase )const{
	return typeid(*this) == typeid(objBase) && objBase.getId() == getId() && objBase.getPoziom() == getPoziom();
}

bool ObiektBase::czyMoznaPodzielic( const Ilosc& i ) const{
	return Ilosc::operator>( i );
}

string ObiektBase::toString() const{
	Logger str(LogObiektBase::className());
	str.addClass(Base::toString());
	str.addClass(Logger::reMakeSimpleClassString(Ilosc::className(),Ilosc::toString()));
	str.addClass(Logger::reMakeSimpleClassString(Poziom::className(),Poziom::toString()));
	str.addClass( info.Base::toString() );
	return str.toString();
}
