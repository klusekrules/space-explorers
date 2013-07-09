#include "Poziom.h"
#include "Logger.h"
#include "Stale.h"

Poziom::Poziom()
	: BaseInterface(Stale::poziomDomyslny)
{
}

Poziom::Poziom( const type_name& poziom )
	: BaseInterface(poziom)
{
}

Poziom::Poziom( const Poziom& poziom )
	: BaseInterface( poziom )
{	
}

Poziom::~Poziom(){
}

bool Poziom::operator==( const Poziom& a)const{
	return wartosc_==a.wartosc_;
}

bool Poziom::operator!=( const Poziom& a)const{
	return wartosc_!=a.wartosc_;
}

bool Poziom::operator<( const Poziom& a )const{
	return wartosc_ < a.wartosc_;
}

bool Poziom::operator<=( const Poziom& a )const{
	return wartosc_ <= a.wartosc_;
}

bool Poziom::operator>( const Poziom& a )const{
	return wartosc_ > a.wartosc_;
}

bool Poziom::operator>=( const Poziom& a )const{
	return wartosc_ >= a.wartosc_;
}

Poziom& Poziom::operator=( const Poziom& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

Poziom& Poziom::operator-=( const Poziom& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

Poziom& Poziom::operator+=( const Poziom& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

Poziom Poziom::operator-( const Poziom& p )const{
	return Poziom( wartosc_ - p.wartosc_ );
}

Poziom Poziom::operator+( const Poziom& p )const{
	return Poziom( wartosc_ + p.wartosc_ );
}

Poziom& Poziom::operator++( ){
	++wartosc_;
	return (*this);
}

Poziom Poziom::operator++( int ){
	Poziom t(*this);
	++wartosc_;
	return t;
}

Poziom::operator size_t () const{
	return (size_t)wartosc_;
}

Poziom::type_name Poziom::getPoziom()const{
	return wartosc_;
}

void Poziom::setPoziom( const type_name& poziom ){
	wartosc_ = poziom;
}

string Poziom::toString() const {
	return Logger::field(CLASSNAME(Poziom),wartosc_);
}