#include "Surowce.h"
#include "SurowceInfo.h"
#include "Logger.h"
#include "Ladownia.h"
#include "DefinicjeWezlowXML.h"
#include "Aplikacja.h"
#include "XmlBO.h"

Surowce::Surowce( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const SurowceInfo& surowceInfo )
	:  PodstawoweParametry(poziom, identyfikatorPlanety), Obiekt( ilosc, poziom, identyfikatorPlanety, surowceInfo ), surowceInfo_(surowceInfo)
{
}

Surowce::Surowce( const Ilosc& ilosc , const Surowce& surowce )
	:  PodstawoweParametry(surowce), Obiekt( ilosc, surowce, surowce.surowceInfo_ ), surowceInfo_(surowce.surowceInfo_)
{
}

Surowce::Surowce( const Ilosc& ilosc, const PodstawoweParametry& parametryPodstawowe, const SurowceInfo& surowceInfo )
	:  PodstawoweParametry(parametryPodstawowe), Obiekt( ilosc, parametryPodstawowe, surowceInfo ), surowceInfo_(surowceInfo)
{
}

Surowce::~Surowce(){
}

Surowce* Surowce::kopia() const{
	return new Surowce( *this );
}

Surowce* Surowce::podziel( const Ilosc& ilosc ){
	if( ilosc <= Ilosc(0.0l) || ilosc >= this->ilosc_ )
		return nullptr;
	this->ilosc_ -= ilosc;
	return new Surowce( ilosc , *this );
}

Surowce& Surowce::operator=( const Surowce& obiekt )  throw ( NiezgodnyTypSurowca ) {
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	ilosc_ = obiekt.ilosc_;
	return *this;
}

bool Surowce::operator==( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	return ilosc_ == obiekt.ilosc_;
}

bool Surowce::operator!=( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	return ilosc_ != obiekt.ilosc_;
}

bool Surowce::operator>( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	return ilosc_ > obiekt.ilosc_;
}

bool Surowce::operator<( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	return ilosc_ < obiekt.ilosc_;
}

bool Surowce::operator>=( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	return ilosc_ >= obiekt.ilosc_;
}

bool Surowce::operator<=( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	return ilosc_ <= obiekt.ilosc_ ;
}

Surowce Surowce::operator+( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	return Surowce( ilosc_ + obiekt.ilosc_ , obiekt );
}

Surowce& Surowce::operator+=( const Surowce& obiekt )  throw ( NiezgodnyTypSurowca ){
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	ilosc_ += obiekt.ilosc_;
	return *this;
}

Surowce Surowce::operator-( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	return Surowce( ilosc_ - obiekt.ilosc_, obiekt  );
}

Surowce& Surowce::operator-=( const Surowce& obiekt ) throw ( NiezgodnyTypSurowca ){
	if( this->ID() != obiekt.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , obiekt.ID() );
	ilosc_ -= obiekt.ilosc_;
	return *this;
}

bool Surowce::Dodaj( const Surowce& obiekt ){
	if( this->ID() != obiekt.ID() )
		return false;
	ilosc_ += obiekt.ilosc_;
	return true;
}

bool Surowce::Usun( const Surowce& obiekt ){
	if( this->ID() != obiekt.ID() )
		return false;
	ilosc_ -= obiekt.ilosc_;
	return true;
}

const SurowceInfo& Surowce::pobierzSurowceInfo() const{
	return surowceInfo_;
}

bool Surowce::czyTypPrzyrostowy()const{
	return surowceInfo_.czyTypPrzyrostowy();
}

Czas Surowce::pobierzCzas()const{
	return surowceInfo_.pobierzCzas(ilosc_,*this);
}

bool Surowce::zapisz( TiXmlElement* wezel ) const {
	TiXmlElement* element = new TiXmlElement(WEZEL_XML_SUROWCE);
	wezel->LinkEndChild( element );
	return Obiekt::zapisz(element);
}

bool Surowce::odczytaj( TiXmlElement* wezel ) {
	return Obiekt::odczytaj(wezel);
}

string Surowce::napis() const{
	Logger str(NAZWAKLASY(Surowce));
	str.dodajKlase(Obiekt::napis());
	str.dodajPole(NAZWAKLASY(Ilosc),ilosc_);
	str.dodajPole(NAZWAKLASY(SurowceInfo)+"ID",surowceInfo_.pobierzIdentyfikator());
	return str.napis();
}
