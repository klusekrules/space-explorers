#include "Obiekt.h"
#include "ObiektInfo.h"
#include "Logger.h"
#include "Ladownia.h"

Obiekt::Obiekt( const Ilosc& i, const Poziom& p, const ObiektInfo& obiekt ) throw()
	: ObiektBase( i, p, obiekt ), obiektInfoClass( obiekt )
{
}

Obiekt::~Obiekt(){
}

Obiekt* Obiekt::Kopia() const{
	return new Obiekt(*this);
}

Obiekt* Obiekt::Podziel( const Ilosc& i ){
	if( ilosc>i ){
		Obiekt* o = new Obiekt( i , getPoziom(), this->obiektInfoClass );
		ilosc-=i;
		return o; 
	}
	return nullptr;
}	
Powierzchnia Obiekt::getPowierzchnia() const{
	return Powierzchnia(obiektInfoClass.getPowierzchnia(getPoziom()).value()*(this->getIlosc().value()));
}

Objetosc Obiekt::getObjetosc() const{
	return Objetosc(obiektInfoClass.getObjetosc(getPoziom()).value()*(this->getIlosc().value()));
}

Masa Obiekt::getMasa() const{
	return Masa(obiektInfoClass.getMasa(getPoziom()).value()*(this->getIlosc().value()));
}

bool Obiekt::czMoznaDodacDoLadownii( const Ladownia& c ) const{
	return false;
}

string Obiekt::toString() const{
	Logger str(CLASSNAME(Obiekt));
	str.addClass(ObiektBase::toString());
	str.addField(CLASSNAME(ObiektInfo)+"ID",obiektInfoClass.getId());
	return str.toString();
}