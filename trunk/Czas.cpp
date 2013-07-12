#include "Czas.h" 
#include "Logger.h"
#include "Stale.h"

Czas::Czas()
	: PodstawowyInterfejs( Stale::czasDomyslny )
{
}

Czas::Czas(const Czas& b)
	: PodstawowyInterfejs(b)
{
}

Czas::Czas( const type_name& t )
	: PodstawowyInterfejs(t)
{
}

Czas::~Czas(){
}

bool Czas::operator==( const Czas& b )const{
	return wartosc_ == b.wartosc_;
}

bool Czas::operator!=( const Czas& b )const{
	return wartosc_ != b.wartosc_;
}

Czas& Czas::operator=( const Czas& b ){
	wartosc_ = b.wartosc_;
	return *this;
}

Czas& Czas::operator+=( const Czas& b ){
	wartosc_ += b.wartosc_;
	return *this;
}

Czas& Czas::operator=( const type_name& b ){
	wartosc_ = b;
	return *this;
}

string Czas::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Czas),wartosc_);
} 
