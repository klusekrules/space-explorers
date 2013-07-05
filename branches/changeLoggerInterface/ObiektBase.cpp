﻿#include "ObiektBase.h"
#include "ObiektBaseInfo.h"
#include "Logger.h"

ObiektBase::ObiektBase( const Ilosc& i, const ObiektBaseInfo& iInfo) throw()
	: Base(iInfo), ilosc(i), obiektBaseInfo(iInfo)
{
}

ObiektBase::~ObiektBase( ){
}

ObiektBase* ObiektBase::Kopia() const{
	return new ObiektBase(*this);
}

ObiektBase* ObiektBase::Podziel( const Ilosc& i ){
	if( czyMoznaPodzielic(i) ){
		ilosc-=i;
		return new ObiektBase( i , obiektBaseInfo );
	}
	return nullptr;
}

bool ObiektBase::Polacz( const ObiektBase& obj ){
	if(czyMoznaPolaczyc(obj)){
		ilosc+=obj.getIlosc();
		return true;
	}else{
		return false;
	}
}
		
Klucz ObiektBase::ID() const{
	return Klucz( getId() , obiektBaseInfo.getPoziom() );
}


bool ObiektBase::czyMoznaPolaczyc( const ObiektBase& objBase )const{
	return typeid(*this) == typeid(objBase) && objBase.getId() == getId() && objBase.getPoziom() == getPoziom();
}

bool ObiektBase::czyMoznaPodzielic( const Ilosc& i ) const{
	return ilosc>i;
}

const Ilosc& ObiektBase::getIlosc() const{
	return ilosc;
}

void ObiektBase::setIlosc( const Ilosc& i ){
	ilosc = i;
}

const Poziom& ObiektBase::getPoziom() const{
	return obiektBaseInfo.getPoziom();
}

Cennik::ListaSurowcow ObiektBase::PobierzKoszty() const{
	return obiektBaseInfo.PobierzKoszty(getIlosc(),getPoziom());
}


Warunek::PrzetworzoneWarunki ObiektBase::PobierzWarunki()const{
	return obiektBaseInfo.listaWarunkow(getPoziom());
}

string ObiektBase::toString() const{
	Logger str(CLASSNAME(ObiektBase));
	str.addClass(Base::toString());
	str.addField(CLASSNAME(Ilosc),ilosc);
	str.addField(CLASSNAME(ObiektBaseInfo)+"ID",obiektBaseInfo.ID());
	return str.toString();
}