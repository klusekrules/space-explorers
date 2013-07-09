#include "Czas.h" 
#include "Logger.h"
#include "Stale.h"

Czas::Czas()
	: BaseInterface( Stale::czasDomyslny )
{
}

Czas::Czas(const Czas& b)
	: BaseInterface(b)
{
}

Czas::Czas( const type_name& t )
	: BaseInterface(t)
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

string Czas::toString() const{
	return Logger::field(CLASSNAME(Czas),wartosc_);
} 
