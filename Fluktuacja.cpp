#include "Fluktuacja.h"
#include "Logger.h"
#include "Stale.h"

Fluktuacja::Fluktuacja()
	: PodstawowyInterfejs( Stale::fluktuacjaDomyslny )
{
}

Fluktuacja::Fluktuacja( const Fluktuacja& a )
	: PodstawowyInterfejs(a)
{
}

Fluktuacja::Fluktuacja( const type_name& f )
	: PodstawowyInterfejs(f)
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

string Fluktuacja::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Fluktuacja),wartosc_);
}
