#include "Obrazenia.h"
#include "Logger.h"
#include "Stale.h"

Obrazenia::Obrazenia()
	: BaseInterface( Stale::obrazeniaDomyslny )
{
}

Obrazenia::Obrazenia( const Obrazenia& a )
	: BaseInterface(a)
{
}

Obrazenia::Obrazenia( const type_name& f )
	: BaseInterface(f)
{
}

Obrazenia::~Obrazenia(){
}

bool Obrazenia::operator==( const Obrazenia& a)const{
	return wartosc_==a.wartosc_;
}

bool Obrazenia::operator!=( const Obrazenia& a)const{
	return wartosc_!=a.wartosc_;
}

bool Obrazenia::operator<( const Obrazenia& a )const{
	return wartosc_ < a.wartosc_;
}

bool Obrazenia::operator<=( const Obrazenia& a )const{
	return wartosc_ <= a.wartosc_;
}

bool Obrazenia::operator>( const Obrazenia& a )const{
	return wartosc_ > a.wartosc_;
}

bool Obrazenia::operator>=( const Obrazenia& a )const{
	return wartosc_ >= a.wartosc_;
}

Obrazenia& Obrazenia::operator=( const Obrazenia& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

Obrazenia& Obrazenia::operator-=( const Obrazenia& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

Obrazenia& Obrazenia::operator+=( const Obrazenia& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

Obrazenia Obrazenia::operator-( const Obrazenia& p )const{
	return Obrazenia( wartosc_ - p.wartosc_ );
}

Obrazenia Obrazenia::operator+( const Obrazenia& p )const{
	return Obrazenia( wartosc_ + p.wartosc_ );
}

string Obrazenia::toString() const{
	return Logger::field(CLASSNAME(Obrazenia),wartosc_);
} 