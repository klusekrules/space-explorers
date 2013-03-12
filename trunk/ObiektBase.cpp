#include "ObiektBase.h"
#include "ObiektInfo.h"
#include "Logger.h"

ObiektBase::ObiektBase( const Ilosc& i, const Poziom & pPoziom, const Info& iInfo)
	: Base(iInfo), ilosc(i), poziom(pPoziom), info(iInfo)
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
		return new ObiektBase( i , poziom , info );
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
	return Klucz( getId() , poziom );
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

void ObiektBase::setPoziom( const Poziom& p ){
	poziom = p;
}
const Poziom& ObiektBase::getPoziom() const{
	return poziom;
}

string ObiektBase::toString() const{
	Logger str(LogObiektBase::className());
	str.addClass(Base::toString());
	str.addField(ilosc.className(),ilosc);
	str.addField(poziom.className(),poziom);
	str.addField(Info::LogInfo::className(),info.getId());
	return str.toString();
}
