#include "Ilosc.h"
#include "Logger.h"
#include "Stale.h"

Ilosc::Ilosc()
	: BaseInterface( Stale::iloscJednostekDomyslny )
{
}

Ilosc::Ilosc( const type_name& ilosc )
	: BaseInterface(ilosc)
{
}

Ilosc::Ilosc( const Ilosc& ilosc )
	: BaseInterface(ilosc)
{
}

Ilosc::~Ilosc(){
}

bool Ilosc::operator<( const Ilosc& i ) const{
	return wartosc_ < i.wartosc_;
}

bool Ilosc::operator>( const Ilosc& i ) const{
	return wartosc_ > i.wartosc_;
}

bool Ilosc::operator==( const Ilosc& i ) const{
	return wartosc_ == i.wartosc_;
}

bool Ilosc::operator!=( const Ilosc& i ) const{
	return wartosc_ != i.wartosc_;
}

bool Ilosc::operator<=( const Ilosc& i) const{
	return wartosc_ <= i.wartosc_;
}

bool Ilosc::operator>=( const Ilosc& i) const{
	return wartosc_ >= i.wartosc_;
}

Ilosc Ilosc::operator+( const Ilosc& i ) const{
	return Ilosc( wartosc_ + i.wartosc_ );
}

Ilosc Ilosc::operator-( const Ilosc& i ) const{
	return Ilosc( wartosc_ - i.wartosc_ );
}

Ilosc Ilosc::operator*( const Ilosc& i ) const{
	return Ilosc( wartosc_ - i.wartosc_ );
}

Ilosc& Ilosc::operator+=( const Ilosc& i ){
	wartosc_+=i.wartosc_;
	return *this;
}

Ilosc& Ilosc::operator++( ){
	++wartosc_;
	return (*this);
}

Ilosc Ilosc::operator++( int ){
	Ilosc t(*this);
	++wartosc_;
	return t;
}

Ilosc& Ilosc::operator-=( const Ilosc& i ){
	wartosc_-=i.wartosc_;
	return *this;
}

Ilosc& Ilosc::operator=( const Ilosc& i ){
	wartosc_=i.wartosc_;
	return *this;
}

string Ilosc::toString() const{
	return Logger::field(CLASSNAME(Ilosc),wartosc_);
}

