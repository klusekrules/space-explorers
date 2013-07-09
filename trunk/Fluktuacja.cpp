#include "Fluktuacja.h"
#include "Logger.h"
#include "Stale.h"

Fluktuacja::Fluktuacja()
	: BaseInterface( Stale::fluktuacjaDomyslny )
{
}

Fluktuacja::Fluktuacja( const Fluktuacja& a )
	: BaseInterface(a)
{
}

Fluktuacja::Fluktuacja( const type_name& f )
	: BaseInterface(f)
{
}

Fluktuacja::~Fluktuacja(){
}

bool Fluktuacja::operator==( const Fluktuacja& a)const{
	return wartosc_==a.wartosc_;
}

bool Fluktuacja::operator!=( const Fluktuacja& a)const{
	return wartosc_!=a.wartosc_;
}

bool Fluktuacja::operator<( const Fluktuacja& a )const{
	return wartosc_ < a.wartosc_;
}

bool Fluktuacja::operator>( const Fluktuacja& a)const{
	return wartosc_ > a.wartosc_;
}

bool Fluktuacja::operator<=( const Fluktuacja& a)const{
	return wartosc_ <= a.wartosc_;
}

bool Fluktuacja::operator>=( const Fluktuacja& a)const{
	return wartosc_ >= a.wartosc_;
}

Fluktuacja& Fluktuacja::operator=( const Fluktuacja& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

Fluktuacja& Fluktuacja::operator-=( const Fluktuacja& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

Fluktuacja& Fluktuacja::operator+=( const Fluktuacja& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

Fluktuacja Fluktuacja::operator-( const Fluktuacja& p )const{
	return Fluktuacja( wartosc_ - p.wartosc_ );
}

Fluktuacja Fluktuacja::operator+( const Fluktuacja& p )const{
	return Fluktuacja( wartosc_ + p.wartosc_ );
}

string Fluktuacja::toString() const{
	return Logger::field(CLASSNAME(Fluktuacja),wartosc_);
}
