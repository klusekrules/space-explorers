#include "Objetosc.h"
#include "Logger.h"
#include "Stale.h"

Objetosc::Objetosc()
	: PodstawowyInterfejs( Stale::objetoscDomyslny )
{
}

Objetosc::Objetosc( const Objetosc& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

Objetosc::Objetosc( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Objetosc::~Objetosc(){
}

bool Objetosc::operator==( const Objetosc& wartosc)const{
	return wartosc_==wartosc.wartosc_;
}

bool Objetosc::operator!=( const Objetosc& wartosc)const{
	return wartosc_!=wartosc.wartosc_;
}

bool Objetosc::operator<( const Objetosc& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool Objetosc::operator<=( const Objetosc& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool Objetosc::operator>( const Objetosc& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool Objetosc::operator>=( const Objetosc& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

Objetosc& Objetosc::operator=( const Objetosc& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Objetosc& Objetosc::operator-=( const Objetosc& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

Objetosc& Objetosc::operator+=( const Objetosc& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

Objetosc Objetosc::operator-( const Objetosc& wartosc )const{
	return Objetosc( wartosc_ - wartosc.wartosc_ );
}

Objetosc Objetosc::operator+( const Objetosc& wartosc )const{
	return Objetosc( wartosc_ + wartosc.wartosc_ );
}

Objetosc Objetosc::operator*( const Ilosc& wartosc )const{
	return Objetosc( wartosc_ * wartosc() );
}

Objetosc& Objetosc::operator*=( const Ilosc& wartosc ){
	wartosc_ *= wartosc();
	return *this; 
}

Objetosc Objetosc::operator*( const Fluktuacja& wartosc )const{
	return Objetosc( wartosc_ * wartosc() );
}

Objetosc& Objetosc::operator*=( const Fluktuacja& wartosc ){
	wartosc_ *= wartosc();
	return *this; 
}
Objetosc Objetosc::operator/( const Ilosc& wartosc )const{
	return Objetosc( wartosc_ / static_cast<type_name>(wartosc()) );
}

Fluktuacja Objetosc::operator/( const Objetosc& wartosc )const{
	return Fluktuacja( static_cast<Fluktuacja::type_name>(wartosc_ / wartosc.wartosc_) );
}

string Objetosc::napis() const{
	stringstream str;
	str.precision(25);
	str<<std::fixed<< wartosc_;
	return str.str();
}
