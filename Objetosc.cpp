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
	return Objetosc( wartosc_ * f.getIlosc() );
}

Objetosc& Objetosc::operator*=( const Ilosc& f ){
	wartosc_ *= f.getIlosc();
	return *this; 
}

Objetosc Objetosc::operator*( const Fluktuacja& f )const{
	return Objetosc( wartosc_ * f.getFluktuacja() );
}

Objetosc& Objetosc::operator*=( const Fluktuacja& f ){
	wartosc_ *= f.getFluktuacja();
	return *this; 
}

Fluktuacja Objetosc::operator/( const Objetosc& o )const{
	return Fluktuacja( static_cast<const float>(wartosc_ / o.wartosc_) );
}

Objetosc::type_name Objetosc::getObjetosc() const{
	return wartosc_;
}

void Objetosc::setObjetosc( const type_name& f ){
	wartosc_ = f;
}

string Objetosc::toString() const{
	stringstream str;
	str.precision(25);
	str<<fixed<< wartosc_;
	return str.str();
} 