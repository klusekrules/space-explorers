#include "Klucz.h"
#include "Logger.h"
#include <ostream>
using std::ostream;
/*
ostream& operator<< (ostream& out, const Klucz::type_name& base){
	out << base << " ";
	return out;
}*/

Klucz::Klucz()
	: PodstawowyInterfejs( 0 ) 
{
}

Klucz::Klucz( const Identyfikator& identyfikator , const Poziom& poziom )
	: PodstawowyInterfejs( ( static_cast<Klucz::type_name>( identyfikator() & 0xFFFFFFFF ) << 32 ) | ( poziom() & 0xFFFFFFFF ) )
{
}

Klucz::Klucz( const type_name& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

Klucz::Klucz( const Klucz& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

Klucz::~Klucz(){
}

Identyfikator Klucz::pobierzIdentyfikator() const{
	return Identyfikator( (wartosc_ >> 32) & 0xFFFFFFFF );
}

Poziom Klucz::pobierzPoziom() const{
	return Poziom( wartosc_ & 0xFFFFFFFF );
}

bool Klucz::operator==( const Klucz& wartosc )const{
	return wartosc_ == wartosc.wartosc_;
}

bool Klucz::operator!=( const Klucz& wartosc )const{
	return wartosc_ != wartosc.wartosc_;
}

bool Klucz::operator<( const Klucz& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

std::string Klucz::napis()const{
	return Logger::tworzPole(NAZWAKLASY(Klucz),wartosc_);
}
