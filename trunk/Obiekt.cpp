#include "Obiekt.h"
#include "ObiektInfo.h"
#include "Logger.h"



Obiekt::Obiekt( const Ilosc& i, const ObiektInfo& obiekt )
	: ObiektBase( i, obiekt ), obiektInfoClass( obiekt )
{
}

Obiekt::~Obiekt(){
}

Obiekt* Obiekt::Kopia() const{
	return new Obiekt(*this);
}

Obiekt* Obiekt::Podziel( const Ilosc& i ){
	if( ilosc>i ){
		Obiekt* o = new Obiekt( i , this->obiektInfoClass );
		ilosc-=i;
		return o; 
	}
	return nullptr;
}	
Powierzchnia Obiekt::getPowierzchnia() const{
	return Powierzchnia(obiektInfoClass.getPowierzchnia().value()*(this->getIlosc().value()));
}

Objetosc Obiekt::getObjetosc() const{
	return Objetosc(obiektInfoClass.getObjetosc().value()*(this->getIlosc().value()));
}

Masa Obiekt::getMasa() const{
	return Masa(obiektInfoClass.getMasa().value()*(this->getIlosc().value()));
}
		

string Obiekt::toString() const{
	Logger str(LogObiekt::className());
	str.addClass(ObiektBase::toString());
	str.addField(ObiektInfo::LogObiektInfo::className()+"ID",obiektInfoClass.ID());
	return str.toString();
}