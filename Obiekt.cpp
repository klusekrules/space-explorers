#include "Obiekt.h"
#include "ObiektInfo.h"
#include "Logger.h"



Obiekt::Obiekt( const ObiektInfo& obiekt )
	: Base( obiekt ), ObiektBase( obiekt ), obiektInfoClass( obiekt )
{
}

Obiekt::~Obiekt(){
}

Obiekt* Obiekt::Kopia() const{
	return new Obiekt(*this);
}

Obiekt* Obiekt::Podziel( const Ilosc& i ){
	if( Ilosc::operator>(i) ){
		Obiekt* o = new Obiekt( *this );
		Ilosc::operator-=(i);
		o->setIlosc(i.value());
		return o; 
	}
	return nullptr;
}	
Powierzchnia Obiekt::getPowierzchnia() const{
	return Powierzchnia(obiektInfoClass.getPowierzchnia().value()*(this->getIlosc()));
}

Objetosc Obiekt::getObjetosc() const{
	return Objetosc(obiektInfoClass.getObjetosc().value()*(this->getIlosc()));
}

Masa Obiekt::getMasa() const{
	return Masa(obiektInfoClass.getMasa().value()*(this->getIlosc()));
}
		

string Obiekt::toString() const{
	Logger str(LogObiekt::className());
	str.addClass(ObiektBase::toString());
	return str.toString();
}