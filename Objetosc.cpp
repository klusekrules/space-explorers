#include "Objetosc.h"
#include "Logger.h"
#include "Stale.h"

Objetosc::Objetosc()
	: BaseInterface( Stale::objetoscDomyslny )
{
}

Objetosc::Objetosc( const Objetosc& a )
	: BaseInterface( a )
{
}

Objetosc::Objetosc( const type_name& f )
	: BaseInterface(f)
{
}

Objetosc::~Objetosc(){
}

bool Objetosc::operator==( const Objetosc& a)const{
	return wartosc_==a.wartosc_;
}

bool Objetosc::operator!=( const Objetosc& a)const{
	return wartosc_!=a.wartosc_;
}

bool Objetosc::operator<( const Objetosc& a )const{
	return wartosc_ < a.wartosc_;
}

bool Objetosc::operator<=( const Objetosc& a )const{
	return wartosc_ <= a.wartosc_;
}

bool Objetosc::operator>( const Objetosc& a )const{
	return wartosc_ > a.wartosc_;
}

bool Objetosc::operator>=( const Objetosc& a )const{
	return wartosc_ >= a.wartosc_;
}

Objetosc& Objetosc::operator=( const Objetosc& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

Objetosc& Objetosc::operator-=( const Objetosc& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

Objetosc& Objetosc::operator+=( const Objetosc& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

Objetosc Objetosc::operator-( const Objetosc& p )const{
	return Objetosc( wartosc_ - p.wartosc_ );
}

Objetosc Objetosc::operator+( const Objetosc& p )const{
	return Objetosc( wartosc_ + p.wartosc_ );
}

Objetosc Objetosc::operator*( const Ilosc& f )const{
	return Objetosc( wartosc_ * f() );
}

Objetosc& Objetosc::operator*=( const Ilosc& f ){
	wartosc_ *= f();
	return *this; 
}

Objetosc Objetosc::operator*( const Fluktuacja& f )const{
	return Objetosc( wartosc_ * f() );
}

Objetosc& Objetosc::operator*=( const Fluktuacja& f ){
	wartosc_ *= f();
	return *this; 
}

Fluktuacja Objetosc::operator/( const Objetosc& o )const{
	return Fluktuacja( static_cast<const float>(wartosc_ / o.wartosc_) );
}

string Objetosc::toString() const{
	stringstream str;
	str.precision(25);
	str<<fixed<< wartosc_;
	return str.str();
} 