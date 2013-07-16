#include "Klucz.h"
#include "Logger.h"

ostream& operator<< (ostream& out, const Klucz::type_name& base){
	out << base.first.napis() << " " << base.second.napis() ;
	return out;
}

Klucz::Klucz()
	: PodstawowyInterfejs( make_pair< Identyfikator , Poziom >( Identyfikator() , Poziom() ) ) 
{
}

Klucz::Klucz( const Identyfikator& id , const Poziom& poziom )
	: PodstawowyInterfejs( make_pair<Identyfikator,Poziom>( Identyfikator(id) , Poziom(poziom) ) )
{
}

Klucz::Klucz( const type_name& pair )
	: PodstawowyInterfejs( pair )
{
}

Klucz::Klucz( const Klucz& klucz )
	: PodstawowyInterfejs( klucz )
{
}

Klucz::~Klucz(){
}

bool Klucz::operator==( const Klucz& a )const{
	return wartosc_ == a.wartosc_;
}

bool Klucz::operator!=( const Klucz& a )const{
	return wartosc_ != a.wartosc_;
}

bool Klucz::operator<( const Klucz& a )const{
	return wartosc_.first != a.wartosc_.first ? wartosc_.first < a.wartosc_.first : wartosc_.second < a.wartosc_.second;
}

string Klucz::napis()const{
	return Logger::tworzPole(NAZWAKLASY(Klucz),wartosc_.first,wartosc_.second);
}
