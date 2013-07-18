#include "Fluktuacja.h"
#include "Logger.h"
#include "Stale.h"

Fluktuacja::Fluktuacja()
	: PodstawowyInterfejs( Stale::fluktuacjaDomyslny )
{
}

Fluktuacja::Fluktuacja( const Fluktuacja& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Fluktuacja::Fluktuacja( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Fluktuacja::~Fluktuacja(){
}

bool Fluktuacja::operator==( const Fluktuacja& wartosc )const{
	return wartosc_==wartosc.wartosc_;
}

bool Fluktuacja::operator!=( const Fluktuacja& wartosc )const{
	return wartosc_!=wartosc.wartosc_;
}

bool Fluktuacja::operator<( const Fluktuacja& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool Fluktuacja::operator>( const Fluktuacja& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool Fluktuacja::operator<=( const Fluktuacja& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool Fluktuacja::operator>=( const Fluktuacja& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

Fluktuacja& Fluktuacja::operator=( const Fluktuacja& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Fluktuacja& Fluktuacja::operator-=( const Fluktuacja& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

Fluktuacja& Fluktuacja::operator+=( const Fluktuacja& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

Fluktuacja Fluktuacja::operator-( const Fluktuacja& wartosc )const{
	return Fluktuacja( wartosc_ - wartosc.wartosc_ );
}

Fluktuacja Fluktuacja::operator+( const Fluktuacja& wartosc )const{
	return Fluktuacja( wartosc_ + wartosc.wartosc_ );
}

string Fluktuacja::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Fluktuacja),wartosc_);
}
