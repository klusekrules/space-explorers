#include "Klucz.h"
#include "Logger.h"
#include <ostream>
using std::ostream;
ostream& operator<< (ostream& out, const Klucz::type_name& base){
	out << base.first.napis() << " " << base.second.napis() ;
	return out;
}

Klucz::Klucz()
	: PodstawowyInterfejs( std::make_pair< Identyfikator , Poziom >( Identyfikator() , Poziom() ) ) 
{
}

Klucz::Klucz( const Identyfikator& identyfikator , const Poziom& poziom )
	: PodstawowyInterfejs( std::make_pair<Identyfikator,Poziom>( Identyfikator(identyfikator) , Poziom(poziom) ) )
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

bool Klucz::operator==( const Klucz& wartosc )const{
	return wartosc_ == wartosc.wartosc_;
}

bool Klucz::operator!=( const Klucz& wartosc )const{
	return wartosc_ != wartosc.wartosc_;
}

bool Klucz::operator<( const Klucz& wartosc )const{
	return wartosc_.first != wartosc.wartosc_.first ? wartosc_.first < wartosc.wartosc_.first : wartosc_.second < wartosc.wartosc_.second;
}

string Klucz::napis()const{
	return Logger::tworzPole(NAZWAKLASY(Klucz),wartosc_.first,wartosc_.second);
}
