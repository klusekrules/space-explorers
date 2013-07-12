#include "Predkosc.h"
#include "Logger.h"
#include "Stale.h"

Predkosc::Predkosc()
	: PodstawowyInterfejs( Stale::predkoscDOmyslny )
{
}

Predkosc::Predkosc( const Predkosc& a )
	: PodstawowyInterfejs( a )
{
}

Predkosc::Predkosc( const type_name& f )
	: PodstawowyInterfejs(f)
{
}

Predkosc::~Predkosc(){
}

bool Predkosc::operator==( const Predkosc& a)const{
	return wartosc_==a.wartosc_;
}

bool Predkosc::operator!=( const Predkosc& a)const{
	return wartosc_!=a.wartosc_;
}

bool Predkosc::operator<( const Predkosc& a )const{
	return wartosc_ < a.wartosc_;
}

bool Predkosc::operator<=( const Predkosc& a )const{
	return wartosc_ <= a.wartosc_;
}

bool Predkosc::operator>( const Predkosc& a )const{
	return wartosc_ > a.wartosc_;
}

bool Predkosc::operator>=( const Predkosc& a )const{
	return wartosc_ >= a.wartosc_;
}

Predkosc& Predkosc::operator=( const Predkosc& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

Predkosc& Predkosc::operator-=( const Predkosc& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

Predkosc& Predkosc::operator+=( const Predkosc& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

Predkosc Predkosc::operator-( const Predkosc& p )const{
	return Predkosc( wartosc_ - p.wartosc_ );
}

Predkosc Predkosc::operator+( const Predkosc& p )const{
	return Predkosc( wartosc_ + p.wartosc_ );
}

string Predkosc::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Predkosc),wartosc_);
} 