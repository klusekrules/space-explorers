#include "Poziom.h"
#include "Logger.h"
#include "Stale.h"

Poziom::Poziom()
	: PodstawowyInterfejs(Stale::poziomDomyslny)
{
}

Poziom::Poziom( const type_name& poziom )
	: PodstawowyInterfejs(poziom)
{
}

Poziom::Poziom( const Poziom& poziom )
	: PodstawowyInterfejs( poziom )
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

string Poziom::napis() const {
	return Logger::tworzPole(NAZWAKLASY(Poziom),wartosc_);
}