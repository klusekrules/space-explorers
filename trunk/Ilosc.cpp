#include "Ilosc.h"
#include "Logger.h"
#include "Stale.h"

Ilosc::Ilosc()
	: PodstawowyInterfejs( Stale::iloscJednostekDomyslny )
{
}

Ilosc::Ilosc( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Ilosc::Ilosc( const Ilosc& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Ilosc::~Ilosc(){
}

bool Ilosc::operator<( const Ilosc& wartosc ) const{
	return wartosc_ < wartosc.wartosc_;
}

bool Ilosc::operator>( const Ilosc& wartosc ) const{
	return wartosc_ > wartosc.wartosc_;
}

bool Ilosc::operator==( const Ilosc& wartosc ) const{
	return wartosc_ == wartosc.wartosc_;
}

bool Ilosc::operator!=( const Ilosc& wartosc ) const{
	return wartosc_ != wartosc.wartosc_;
}

bool Ilosc::operator<=( const Ilosc& wartosc) const{
	return wartosc_ <= wartosc.wartosc_;
}

bool Ilosc::operator>=( const Ilosc& wartosc) const{
	return wartosc_ >= wartosc.wartosc_;
}

Ilosc Ilosc::operator+( const Ilosc& wartosc ) const{
	return Ilosc( wartosc_ + wartosc.wartosc_ );
}

Ilosc Ilosc::operator-( const Ilosc& wartosc ) const{
	return Ilosc( wartosc_ - wartosc.wartosc_ );
}

Ilosc Ilosc::operator*( const Ilosc& wartosc ) const{
	return Ilosc( wartosc_ * wartosc.wartosc_ );
}

Ilosc Ilosc::operator/( const Ilosc& wartosc ) const{
	return Ilosc( wartosc_ / wartosc.wartosc_ );
}

Ilosc& Ilosc::operator+=( const Ilosc& wartosc ){
	wartosc_+=wartosc.wartosc_;
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

Ilosc& Ilosc::operator-=( const Ilosc& wartosc ){
	wartosc_-=wartosc.wartosc_;
	return *this;
}

Ilosc& Ilosc::operator=( const Ilosc& wartosc ){
	wartosc_=wartosc.wartosc_;
	return *this;
}

string Ilosc::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Ilosc),wartosc_);
}
