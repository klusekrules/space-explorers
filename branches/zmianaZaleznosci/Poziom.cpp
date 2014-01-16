#include "Poziom.h"
#include "Logger.h"
#include "Stale.h"

Poziom::Poziom()
	: PodstawowyInterfejs(Stale::poziomDomyslny)
{
}

Poziom::Poziom( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Poziom::Poziom( const Poziom& wartosc )
	: PodstawowyInterfejs( wartosc )
{	
}

Poziom::~Poziom(){
}

bool Poziom::operator==( const Poziom& wartosc)const{
	return wartosc_==wartosc.wartosc_;
}

bool Poziom::operator!=( const Poziom& wartosc)const{
	return wartosc_!=wartosc.wartosc_;
}

bool Poziom::operator<( const Poziom& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool Poziom::operator<=( const Poziom& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool Poziom::operator>( const Poziom& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool Poziom::operator>=( const Poziom& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

Poziom& Poziom::operator=( const Poziom& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Poziom& Poziom::operator-=( const Poziom& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

Poziom& Poziom::operator+=( const Poziom& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

Poziom Poziom::operator-( const Poziom& wartosc )const{
	return Poziom( wartosc_ - wartosc.wartosc_ );
}

Poziom Poziom::operator+( const Poziom& wartosc )const{
	return Poziom( wartosc_ + wartosc.wartosc_ );
}

Poziom& Poziom::operator++( ){
	++wartosc_;
	return (*this);
}

Poziom Poziom::operator++( int ){
	Poziom t(*this);
	++wartosc_;
	return t;
}

Poziom::operator size_t () const{
	return (size_t)wartosc_;
}

std::string Poziom::napis() const {
	return Logger::tworzPole(NAZWAKLASY(Poziom),wartosc_);
}
