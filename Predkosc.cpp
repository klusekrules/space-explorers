#include "Predkosc.h"
#include "Logger.h"
#include "Stale.h"

Predkosc::Predkosc()
	: BaseInterface( Stale::predkoscDOmyslny )
{
}

Predkosc::Predkosc( const Predkosc& a )
	: BaseInterface( a )
{
}

Predkosc::Predkosc( const type_name& f )
	: BaseInterface(f)
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

Predkosc::type_name Predkosc::getPredkosc() const{
	return wartosc_;
}

void Predkosc::setPredkosc( const type_name& f ){
	wartosc_ = f;
}

string Predkosc::toString() const{
	return Logger::field(CLASSNAME(Predkosc),wartosc_);
} 