#include "Temperatura.h" 
#include "Logger.h"

Temperatura::Temperatura()
	: PodstawowyInterfejs( 0 )
{
}

Temperatura::Temperatura(const Temperatura& wartosc)
	: PodstawowyInterfejs( wartosc )
{
}

Temperatura::Temperatura( const type_name& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

Temperatura::~Temperatura()
{
}

bool Temperatura::operator==( const Temperatura& wartosc )const{
	return wartosc_ == wartosc.wartosc_;
}

bool Temperatura::operator!=( const Temperatura& wartosc )const{
	return wartosc_ != wartosc.wartosc_;
}

Temperatura& Temperatura::operator=( const Temperatura& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

std::string Temperatura::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Temperatura),wartosc_);
}
