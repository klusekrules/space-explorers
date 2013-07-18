#include "Masa.h"
#include "Logger.h"
#include "Stale.h"

Masa::Masa()
	: PodstawowyInterfejs( Stale::masaDomyslny )
{
}

Masa::Masa( const Masa& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

Masa::Masa( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Masa::~Masa(){
}

bool Masa::operator==( const Masa& wartosc)const{
	return wartosc_==wartosc.wartosc_;
}

bool Masa::operator!=( const Masa& wartosc)const{
	return wartosc_!=wartosc.wartosc_;
}

bool Masa::operator<( const Masa& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool Masa::operator<=( const Masa& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool Masa::operator>( const Masa& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool Masa::operator>=( const Masa& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

Masa& Masa::operator=( const Masa& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Masa& Masa::operator-=( const Masa& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

Masa& Masa::operator+=( const Masa& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

Masa Masa::operator-( const Masa& wartosc )const{
	return Masa( wartosc_ - wartosc.wartosc_ );
}

Masa Masa::operator+( const Masa& wartosc )const{
	return Masa( wartosc_ + wartosc.wartosc_ );
}

Masa Masa::operator*( const Fluktuacja& wartosc )const{
	return Masa( wartosc_ * wartosc() );
}

Masa& Masa::operator*=( const Fluktuacja& wartosc ){
	wartosc_ *= wartosc();
	return *this;
}

Masa Masa::operator*( const Ilosc& wartosc )const{
	return Masa( wartosc_ * wartosc() );
}

Masa& Masa::operator*=( const Ilosc& wartosc ){
	wartosc_ *= wartosc();
	return *this;
}

string Masa::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Masa),wartosc_);
} 
