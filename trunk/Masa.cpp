#include "Masa.h"
#include "Logger.h"
#include "Stale.h"

Masa::Masa()
	: PodstawowyInterfejs( Stale::masaDomyslny )
{
}

Masa::Masa( const Masa& a )
	: PodstawowyInterfejs( a )
{
}

Masa::Masa( const type_name& f )
	: PodstawowyInterfejs(f)
{
}

Masa::~Masa(){
}

bool Masa::operator==( const Masa& a)const{
	return wartosc_==a.wartosc_;
}

bool Masa::operator!=( const Masa& a)const{
	return wartosc_!=a.wartosc_;
}

bool Masa::operator<( const Masa& a )const{
	return wartosc_ < a.wartosc_;
}

bool Masa::operator<=( const Masa& a )const{
	return wartosc_ <= a.wartosc_;
}

bool Masa::operator>( const Masa& a )const{
	return wartosc_ > a.wartosc_;
}

bool Masa::operator>=( const Masa& a )const{
	return wartosc_ >= a.wartosc_;
}

Masa& Masa::operator=( const Masa& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

Masa& Masa::operator-=( const Masa& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

Masa& Masa::operator+=( const Masa& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

Masa Masa::operator-( const Masa& p )const{
	return Masa( wartosc_ - p.wartosc_ );
}

Masa Masa::operator+( const Masa& p )const{
	return Masa( wartosc_ + p.wartosc_ );
}

Masa Masa::operator*( const Fluktuacja& f )const{
	return Masa( wartosc_ * f() );
}

Masa& Masa::operator*=( const Fluktuacja& f ){
	wartosc_ *= f();
	return *this;
}

Masa Masa::operator*( const Ilosc& f )const{
	return Masa( wartosc_ * f() );
}

Masa& Masa::operator*=( const Ilosc& f ){
	wartosc_ *= f();
	return *this;
}


string Masa::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Masa),wartosc_);
} 