#include "Czas.h" 
#include "Logger.h"
#include "Stale.h"

Czas::Czas()
	: PodstawowyInterfejs( Stale::czasDomyslny )
{
}

Czas::Czas(const Czas& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

Czas::Czas( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Czas::~Czas(){
}

bool Czas::operator==( const Czas& wartosc )const{
	return wartosc_ == wartosc.wartosc_;
}

bool Czas::operator!=( const Czas& wartosc )const{
	return wartosc_ != wartosc.wartosc_;
}

Czas& Czas::operator=( const Czas& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Czas& Czas::operator+=( const Czas& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

Czas& Czas::operator=( const type_name& wartosc ){
	wartosc_ = wartosc;
	return *this;
}

std::string Czas::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Czas),wartosc_);
} 
