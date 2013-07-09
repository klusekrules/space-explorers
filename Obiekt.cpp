#include "Obiekt.h"
#include "ObiektInfo.h"
#include "Logger.h"
#include "Ladownia.h"

Obiekt::Obiekt( const Ilosc& i, const Poziom& p, const IdType& idP, const ObiektInfo& obiekt ) throw()
	: PodstawoweParametry(p, idP), ObiektBase( i, p, idP, obiekt ), obiektInfoClass( obiekt )
{
}

Obiekt::Obiekt( const Ilosc& i, const PodstawoweParametry&p , const ObiektInfo& obiekt ) throw()
	: PodstawoweParametry(p), ObiektBase( i, p, obiekt ), obiektInfoClass( obiekt )
{
}

Obiekt::~Obiekt(){
}

Obiekt* Obiekt::Kopia() const{
	return new Obiekt(*this);
}

Obiekt* Obiekt::Podziel( const Ilosc& i ){
	if( ilosc>i ){
		Obiekt* o = new Obiekt( i , getPoziom(), getIdPlanety(), this->obiektInfoClass );
		ilosc-=i;
		return o; 
	}
	return nullptr;
}	
Powierzchnia Obiekt::getPowierzchnia() const{
	return Powierzchnia(obiektInfoClass.getPowierzchnia(getPoziom(),getIdPlanety())()*(this->getIlosc()()));
}

Objetosc Obiekt::getObjetosc() const{
	return Objetosc(obiektInfoClass.getObjetosc(getPoziom(),getIdPlanety())()*(this->getIlosc()()));
}

Masa Obiekt::getMasa() const{
	return Masa(obiektInfoClass.getMasa(getPoziom(),getIdPlanety())()*(this->getIlosc()()));
}

bool Obiekt::czMoznaDodacDoLadownii( const Ladownia& c ) const{
	return false;
}

bool Obiekt::zapisz( TiXmlElement* e) const{
	return ObiektBase::zapisz(e);
}
bool Obiekt::odczytaj (TiXmlElement* e){
	return ObiektBase::odczytaj(e);
}

string Obiekt::toString() const{
	Logger str(CLASSNAME(Obiekt));
	str.addClass(ObiektBase::toString());
	str.addField(CLASSNAME(ObiektInfo)+"ID",obiektInfoClass.getId());
	return str.toString();
}