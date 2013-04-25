#include "Tekst.h"
#include "Logger.h"
#include "Stale.h"

Tekst::Tekst()
	: tekst( Stale::tekstDomyslny )
{
}

Tekst::Tekst( const type_name& tekst )
	: tekst(tekst)
{
}

Tekst::Tekst( const Tekst& tekst)
	: tekst(tekst.tekst)
{
}

Tekst::~Tekst(){
}
bool Tekst::isEmpty() const{
	return tekst.size() == 0;
}

Tekst Tekst::operator+( const Tekst& a ) const{
	return Tekst( tekst + a.tekst );
}

Tekst& Tekst::operator+=( const Tekst& a ){
	tekst+=a.tekst;
	return *this;
}

Tekst& Tekst::operator=( const Tekst& a ){
	tekst = a.tekst;
	return *this;
}

bool Tekst::operator==( const Tekst& a ) const{
	return tekst == a.tekst;
}

bool Tekst::operator!=( const Tekst& a ) const{
	return tekst != a.tekst;
}
	
	
Tekst::type_name Tekst::getTekst()const{
	return tekst;
}

void Tekst::setTekst( const type_name & tekst ){
	this->tekst = tekst;
}

Tekst::type_name Tekst::value()const{
	return getTekst();
}

string Tekst::toString()const {
	return Logger::field(CLASSNAME(Tekst),dodajCudzyslow());
}


Tekst::type_name Tekst::dodajCudzyslow() const {
	string s("\"");
	s.append(tekst);
	s.append("\"");
	return s;
}