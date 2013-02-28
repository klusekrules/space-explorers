#include "ObiektBase.h"
#include "ObiektInfo.h"
#include "Logger.h"

ObiektBase::ObiektBase( )
	: Ilosc() , Poziom(), info(nullptr)
{
}

ObiektBase::ObiektBase( const ObiektInfo& iInfo )
	: Ilosc(iInfo), Base(iInfo) , Poziom(iInfo) , info(&iInfo)
{
}

ObiektBase::ObiektBase( const Ilosc& i, const Poziom & pPoziom, const ObiektInfo* iInfo , const Base & bBase )
	: Ilosc(i), Base(bBase) , Poziom(pPoziom) , info(iInfo)
{
}

ObiektBase::ObiektBase( const Ilosc& i, const Poziom & pPoziom, const ObiektInfo* iInfo , const IdType& id)
	: Base(id), Ilosc(i), Poziom(pPoziom), info(iInfo)
{
}

ObiektBase::ObiektBase( const IdType& id, const Poziom & p )
	: Base(id), Ilosc(), Poziom(p), info(nullptr)
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
		return new ObiektBase( *this, *this, info, *this );
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

ObiektInfo* ObiektBase::getObiektInfo() const{
	return const_cast<ObiektInfo*>(info);	
}

void ObiektBase::setObiektInfo( const ObiektInfo* iInfo ){
	info = iInfo;
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
	if(info!=nullptr)
		str.addField<ObiektInfo>("ObiektInfo", *info );
	return str.toString();
}
