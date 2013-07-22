#include "Surowce.h"
#include "SurowceInfo.h"
#include "Logger.h"
#include "Ladownia.h"
#include "DefinicjeWezlowXML.h"
#include "Aplikacja.h"

Surowce::Surowce( const Ilosc& isIlosc, const Poziom& p, const Identyfikator& idP, const SurowceInfo& s )
	:  PodstawoweParametry(p, idP), Obiekt( isIlosc, p, idP, s ), surowceInfo(s)
{
}

Surowce::Surowce( const Ilosc& isIlosc , const Surowce& s )
	:  PodstawoweParametry(s), Obiekt( isIlosc, s, s.surowceInfo ), surowceInfo(s.surowceInfo)
{
}

Surowce::Surowce( const Ilosc& isIlosc, const PodstawoweParametry& p, const SurowceInfo& s )
	:  PodstawoweParametry(p), Obiekt( isIlosc, p, s ), surowceInfo(s)
{
}

Surowce::Surowce( TiXmlElement* e  )
	:  PodstawoweParametry(Poziom(),Identyfikator()), 
	Obiekt( Ilosc(), Poziom(), Identyfikator(), Aplikacja::getInstance().getGra().getSurowce(Identyfikator(stoul(e->Attribute(ATRYBUT_XML_IDENTYFIKATOR),nullptr,0)) )), 
	surowceInfo( Aplikacja::getInstance().getGra().getSurowce(Identyfikator(stoul(e->Attribute(ATRYBUT_XML_IDENTYFIKATOR),nullptr,0)) ))
{
	Obiekt::odczytaj(e);
}

Surowce* Surowce::Kopia() const{
	return new Surowce( *this );
}

Obiekt* Surowce::Podziel( const Ilosc& ilosc ) throw ( NiepoprawnaIloscObiektow ){
	if( ilosc <= Ilosc(0.0l) || ilosc >= this->ilosc_ )
		throw NiepoprawnaIloscObiektow(EXCEPTION_PLACE,ilosc);
	this->ilosc_ -= ilosc;
	return new Surowce( ilosc , *this );
}

Surowce& Surowce::operator=( const Surowce& sSurowce )  throw ( NiezgodnyTypSurowca ) {
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	ilosc_ = sSurowce.ilosc_;
	return *this;
}

bool Surowce::operator==( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc_ == sSurowce.ilosc_;
}
	
bool Surowce::operator!=( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc_ != sSurowce.ilosc_;
}
	
bool Surowce::operator>( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc_ > sSurowce.ilosc_;
}
	
bool Surowce::operator<( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc_ < sSurowce.ilosc_;
}
	
bool Surowce::operator>=( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc_ >= sSurowce.ilosc_;
}
	
bool Surowce::operator<=( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc_ <= sSurowce.ilosc_ ;
}

Surowce Surowce::operator+( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return Surowce( ilosc_ + sSurowce.ilosc_ , sSurowce );
}
	
Surowce& Surowce::operator+=( const Surowce& sSurowce )  throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	ilosc_ += sSurowce.ilosc_;
	return *this;
}
	
Surowce Surowce::operator-( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return Surowce( ilosc_ - sSurowce.ilosc_, sSurowce  );
}

Surowce& Surowce::operator-=( const Surowce& sSurowce ) throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	ilosc_ -= sSurowce.ilosc_;
	return *this;
}

bool Surowce::Dodaj( const Surowce& sSurowce ){
	if( this->ID() != sSurowce.ID() )
		return false;
	ilosc_ += sSurowce.ilosc_;
	return true;
}
	
bool Surowce::Usun( const Surowce& sSurowce ){
	if( this->ID() != sSurowce.ID() )
		return false;
	ilosc_ -= sSurowce.ilosc_;
	return true;
}
	
const Ilosc& Surowce::getIlosc() const{
	return ilosc_;
}
	
void Surowce::setIlosc( const Ilosc& isIlosc ) {
	ilosc_ = isIlosc;
}

const SurowceInfo& Surowce::getSurowceInfo() const{
	return surowceInfo;
}

bool Surowce::czyTypPrzyrostowy()const{
	return surowceInfo.czyTypPrzyrostowy();
}

bool Surowce::czMoznaDodacDoLadownii( const Ladownia& c ) const{
	return c.czMoznaDodacDoLadownii(*this);
}

Czas Surowce::pobierzCzas()const{
	return surowceInfo.pobierzCzas(ilosc_,*this);
}

bool Surowce::zapisz( TiXmlElement* e ) const {
	TiXmlElement* n = new TiXmlElement(WEZEL_XML_SUROWCE);
	e->LinkEndChild( n );
	return Obiekt::zapisz(n);
}

bool Surowce::odczytaj( TiXmlElement* e ) {
	return Obiekt::odczytaj(e);
}

string Surowce::napis() const{
	Logger str(NAZWAKLASY(Surowce));
	str.dodajKlase(Obiekt::napis());
	str.dodajPole(NAZWAKLASY(Ilosc),ilosc_);
	str.dodajPole(NAZWAKLASY(SurowceInfo)+"ID",surowceInfo.pobierzIdentyfikator());
	return str.napis();
}