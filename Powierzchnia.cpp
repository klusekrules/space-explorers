#include "Powierzchnia.h"
#include "Logger.h"
#include "Stale.h"

Powierzchnia::Powierzchnia()
	: BaseInterface( Stale::powierzchniaDomyslny )
{
}

Powierzchnia::Powierzchnia( const Powierzchnia& a )
	: BaseInterface( a )
{
}

Powierzchnia::Powierzchnia( const type_name& f )
	: BaseInterface(f)
{
}

Powierzchnia::~Powierzchnia(){
}

bool Powierzchnia::operator==( const Powierzchnia& a)const{
	return wartosc_==a.wartosc_;
}

bool Powierzchnia::operator!=( const Powierzchnia& a)const{
	return wartosc_!=a.wartosc_;
}

bool Powierzchnia::operator<( const Powierzchnia& a )const{
	return wartosc_ < a.wartosc_;
}

bool Powierzchnia::operator<=( const Powierzchnia& a )const{
	return wartosc_ <= a.wartosc_;
}

bool Powierzchnia::operator>( const Powierzchnia& a )const{
	return wartosc_ > a.wartosc_;
}

bool Powierzchnia::operator>=( const Powierzchnia& a )const{
	return wartosc_ >= a.wartosc_;
}

Powierzchnia& Powierzchnia::operator=( const Powierzchnia& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

Powierzchnia& Powierzchnia::operator-=( const Powierzchnia& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

Powierzchnia& Powierzchnia::operator+=( const Powierzchnia& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

Powierzchnia Powierzchnia::operator-( const Powierzchnia& p )const{
	return Powierzchnia( wartosc_ - p.wartosc_ );
}

Powierzchnia Powierzchnia::operator+( const Powierzchnia& p )const{
	return Powierzchnia( wartosc_ + p.wartosc_ );
}

Powierzchnia Powierzchnia::operator*( const Fluktuacja& f )const{
	return Powierzchnia( wartosc_ * f() );
}

Powierzchnia& Powierzchnia::operator*=( const Fluktuacja& f ){
	wartosc_ *= f();
	return *this;
}
Powierzchnia Powierzchnia::operator*( const Ilosc& f )const{
	return Powierzchnia( wartosc_ * f() );
}

Powierzchnia& Powierzchnia::operator*=( const Ilosc& f ){
	wartosc_ *= f();
	return *this;
}

string Powierzchnia::toString() const{
	return Logger::tworzPole(NAZWAKLASY(Powierzchnia),wartosc_);
} 