#include "Dystans.h"
#include "Logger.h"
#include "Stale.h"

Dystans::Dystans()
	: PodstawowyInterfejs( Stale::dystansDomyslny )
{
}

Dystans::Dystans( const Dystans& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Dystans::Dystans( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Dystans::~Dystans(){
}

bool Dystans::operator==( const Dystans& wartosc)const{
	return wartosc_==wartosc.wartosc_;
}

bool Dystans::operator!=( const Dystans& wartosc)const{
	return wartosc_!=wartosc.wartosc_;
}

bool Dystans::operator<( const Dystans& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool Dystans::operator<=( const Dystans& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool Dystans::operator>( const Dystans& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool Dystans::operator>=( const Dystans& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

Dystans& Dystans::operator=( const Dystans& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Dystans& Dystans::operator-=( const Dystans& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

Dystans& Dystans::operator+=( const Dystans& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

Dystans Dystans::operator-( const Dystans& wartosc )const{
	return Dystans( wartosc_ - wartosc.wartosc_ );
}

Dystans Dystans::operator+( const Dystans& wartosc )const{
	return Dystans( wartosc_ + wartosc.wartosc_ );
}

Dystans Dystans::operator/( const type_name& wartosc )const{
	return Dystans( wartosc_ / wartosc );
}

std::string Dystans::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Dystans),wartosc_);
}
