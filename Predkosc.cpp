#include "Predkosc.h"
#include "Logger.h"
#include "Stale.h"

Predkosc::Predkosc()
	: PodstawowyInterfejs( Stale::predkoscDOmyslny )
{
}

Predkosc::Predkosc( const Predkosc& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

Predkosc::Predkosc( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Predkosc::~Predkosc(){
}

bool Predkosc::operator==( const Predkosc& wartosc)const{
	return wartosc_==wartosc.wartosc_;
}

bool Predkosc::operator!=( const Predkosc& wartosc)const{
	return wartosc_!=wartosc.wartosc_;
}

bool Predkosc::operator<( const Predkosc& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool Predkosc::operator<=( const Predkosc& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool Predkosc::operator>( const Predkosc& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool Predkosc::operator>=( const Predkosc& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

Predkosc& Predkosc::operator=( const Predkosc& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Predkosc& Predkosc::operator-=( const Predkosc& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

Predkosc& Predkosc::operator+=( const Predkosc& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

Predkosc Predkosc::operator-( const Predkosc& wartosc )const{
	return Predkosc( wartosc_ - wartosc.wartosc_ );
}

Predkosc Predkosc::operator+( const Predkosc& wartosc )const{
	return Predkosc( wartosc_ + wartosc.wartosc_ );
}

string Predkosc::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Predkosc),wartosc_);
}
