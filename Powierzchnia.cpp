#include "Powierzchnia.h"
#include "Logger.h"
#include "Stale.h"

Powierzchnia::Powierzchnia()
	: PodstawowyInterfejs( Stale::powierzchniaDomyslny )
{
}

Powierzchnia::Powierzchnia( const Powierzchnia& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

Powierzchnia::Powierzchnia( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Powierzchnia::~Powierzchnia(){
}

bool Powierzchnia::operator==( const Powierzchnia& wartosc)const{
	return wartosc_==wartosc.wartosc_;
}

bool Powierzchnia::operator!=( const Powierzchnia& wartosc)const{
	return wartosc_!=wartosc.wartosc_;
}

bool Powierzchnia::operator<( const Powierzchnia& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool Powierzchnia::operator<=( const Powierzchnia& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool Powierzchnia::operator>( const Powierzchnia& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool Powierzchnia::operator>=( const Powierzchnia& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

Powierzchnia& Powierzchnia::operator=( const Powierzchnia& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Powierzchnia& Powierzchnia::operator-=( const Powierzchnia& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

Powierzchnia& Powierzchnia::operator+=( const Powierzchnia& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

Powierzchnia Powierzchnia::operator-( const Powierzchnia& wartosc )const{
	return Powierzchnia( wartosc_ - wartosc.wartosc_ );
}

Powierzchnia Powierzchnia::operator+( const Powierzchnia& wartosc )const{
	return Powierzchnia( wartosc_ + wartosc.wartosc_ );
}

Powierzchnia Powierzchnia::operator*( const Fluktuacja& wartosc )const{
	return Powierzchnia( wartosc_ * wartosc() );
}

Powierzchnia& Powierzchnia::operator*=( const Fluktuacja& wartosc ){
	wartosc_ *= wartosc();
	return *this;
}
Powierzchnia Powierzchnia::operator*( const Ilosc& wartosc )const{
	return Powierzchnia( wartosc_ * wartosc() );
}

Powierzchnia& Powierzchnia::operator*=( const Ilosc& wartosc ){
	wartosc_ *= wartosc();
	return *this;
}

std::string Powierzchnia::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Powierzchnia),wartosc_);
}
