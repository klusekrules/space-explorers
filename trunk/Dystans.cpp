#include "Dystans.h"
#include "Logger.h"
#include "Stale.h"

Dystans::Dystans()
	: BaseInterface( Stale::dystansDomyslny )
{
}

Dystans::Dystans( const Dystans& a )
	: BaseInterface(a)
{
}

Dystans::Dystans( const type_name& f )
	: BaseInterface(f)
{
}

Dystans::~Dystans(){
}

bool Dystans::operator==( const Dystans& a)const{
	return wartosc_==a.wartosc_;
}

bool Dystans::operator!=( const Dystans& a)const{
	return wartosc_!=a.wartosc_;
}

bool Dystans::operator<( const Dystans& a )const{
	return wartosc_ < a.wartosc_;
}

bool Dystans::operator<=( const Dystans& a )const{
	return wartosc_ <= a.wartosc_;
}

bool Dystans::operator>( const Dystans& a )const{
	return wartosc_ > a.wartosc_;
}

bool Dystans::operator>=( const Dystans& a )const{
	return wartosc_ >= a.wartosc_;
}

Dystans& Dystans::operator=( const Dystans& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

Dystans& Dystans::operator-=( const Dystans& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

Dystans& Dystans::operator+=( const Dystans& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

Dystans Dystans::operator-( const Dystans& p )const{
	return Dystans( wartosc_ - p.wartosc_ );
}

Dystans Dystans::operator+( const Dystans& p )const{
	return Dystans( wartosc_ + p.wartosc_ );
}

string Dystans::toString() const{
	return Logger::tworzPole(NAZWAKLASY(Dystans),wartosc_);
} 