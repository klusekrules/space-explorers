#include "Poziom.h"
#include "Logger.h"
#include "Stale.h"

Poziom::Poziom()
	: pPoziom(Stale::poziomDomyslny)
{
}

Poziom::Poziom( const type_name& poziom )
	: pPoziom(poziom)
{
}

Poziom::Poziom( const Poziom& poziom )
	: pPoziom( poziom.pPoziom )
{	
}

Poziom::~Poziom(){
}

bool Poziom::operator==( const Poziom& a)const{
	return pPoziom==a.pPoziom;
}

bool Poziom::operator!=( const Poziom& a)const{
	return pPoziom!=a.pPoziom;
}

bool Poziom::operator<( const Poziom& a )const{
	return pPoziom < a.pPoziom;
}

bool Poziom::operator<=( const Poziom& a )const{
	return pPoziom <= a.pPoziom;
}

bool Poziom::operator>( const Poziom& a )const{
	return pPoziom > a.pPoziom;
}

bool Poziom::operator>=( const Poziom& a )const{
	return pPoziom >= a.pPoziom;
}

Poziom& Poziom::operator=( const Poziom& p ){
	pPoziom = p.pPoziom;
	return *this;
}

Poziom& Poziom::operator-=( const Poziom& p ){
	pPoziom -= p.pPoziom;
	return *this;
}

Poziom& Poziom::operator+=( const Poziom& p ){
	pPoziom += p.pPoziom;
	return *this;
}

Poziom Poziom::operator-( const Poziom& p )const{
	return Poziom( pPoziom - p.pPoziom );
}

Poziom Poziom::operator+( const Poziom& p )const{
	return Poziom( pPoziom + p.pPoziom );
}

Poziom::operator size_t () const{
	return (size_t)pPoziom;
}

Poziom::type_name Poziom::getPoziom()const{
	return pPoziom;
}

void Poziom::setPoziom( const type_name& poziom ){
	pPoziom = poziom;
}

Poziom::type_name Poziom::value() const {
	return getPoziom();
}

string Poziom::toString() const {
	return Logger::field(className(),pPoziom);
}