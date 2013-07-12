#include "Tekst.h"
#include "Logger.h"
#include "Stale.h"

Tekst::Tekst()
	: PodstawowyInterfejs( Stale::tekstDomyslny )
{
}

Tekst::Tekst( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Tekst::Tekst( const Tekst& wartosc)
	: PodstawowyInterfejs(wartosc)
{
}

Tekst::~Tekst(){
}

bool Tekst::isEmpty() const{
	return wartosc_.size() == 0;
}

Tekst Tekst::operator+( const Tekst& a ) const{
	return Tekst( wartosc_ + a.wartosc_ );
}

Tekst& Tekst::operator+=( const Tekst& a ){
	wartosc_+=a.wartosc_;
	return *this;
}

Tekst& Tekst::operator=( const Tekst& a ){
	wartosc_ = a.wartosc_;
	return *this;
}

bool Tekst::operator==( const Tekst& a ) const{
	return wartosc_ == a.wartosc_;
}

bool Tekst::operator!=( const Tekst& a ) const{
	return wartosc_ != a.wartosc_;
}

string Tekst::napis()const {
	return Logger::tworzPole(NAZWAKLASY(Tekst),dodajCudzyslow());
}

Tekst::type_name Tekst::dodajCudzyslow() const {
	string s("\"");
	s.append(wartosc_);
	s.append("\"");
	return s;
}