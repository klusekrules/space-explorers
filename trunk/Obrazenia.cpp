#include "Obrazenia.h"
#include "Logger.h"
#include "Stale.h"

Obrazenia::Obrazenia()
	: PodstawowyInterfejs( Stale::obrazeniaDomyslny )
{
}

Obrazenia::Obrazenia( const Obrazenia& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Obrazenia::Obrazenia( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Obrazenia::~Obrazenia(){
}

bool Obrazenia::operator==( const Obrazenia& wartosc)const{
	return wartosc_==wartosc.wartosc_;
}

bool Obrazenia::operator!=( const Obrazenia& wartosc)const{
	return wartosc_!=wartosc.wartosc_;
}

bool Obrazenia::operator<( const Obrazenia& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool Obrazenia::operator<=( const Obrazenia& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool Obrazenia::operator>( const Obrazenia& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool Obrazenia::operator>=( const Obrazenia& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

Obrazenia& Obrazenia::operator=( const Obrazenia& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Obrazenia& Obrazenia::operator-=( const Obrazenia& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

Obrazenia& Obrazenia::operator+=( const Obrazenia& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

Obrazenia Obrazenia::operator-( const Obrazenia& wartosc )const{
	return Obrazenia( wartosc_ - wartosc.wartosc_ );
}

Obrazenia Obrazenia::operator+( const Obrazenia& wartosc )const{
	return Obrazenia( wartosc_ + wartosc.wartosc_ );
}

std::string Obrazenia::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Obrazenia),wartosc_);
}
