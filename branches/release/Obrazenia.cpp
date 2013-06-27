#include "Obrazenia.h"
#include "Logger.h"
#include "Stale.h"

Obrazenia::Obrazenia()
	: obrazenia( Stale::obrazeniaDomyslny )
{
}

Obrazenia::Obrazenia( const Obrazenia& a )
	: obrazenia( a.obrazenia )
{
}

Obrazenia::Obrazenia( const type_name& f )
	: obrazenia(f)
{
}

Obrazenia::~Obrazenia(){
}

bool Obrazenia::operator==( const Obrazenia& a)const{
	return obrazenia==a.obrazenia;
}

bool Obrazenia::operator!=( const Obrazenia& a)const{
	return obrazenia!=a.obrazenia;
}

bool Obrazenia::operator<( const Obrazenia& a )const{
	return obrazenia < a.obrazenia;
}

bool Obrazenia::operator<=( const Obrazenia& a )const{
	return obrazenia <= a.obrazenia;
}

bool Obrazenia::operator>( const Obrazenia& a )const{
	return obrazenia > a.obrazenia;
}

bool Obrazenia::operator>=( const Obrazenia& a )const{
	return obrazenia >= a.obrazenia;
}

Obrazenia& Obrazenia::operator=( const Obrazenia& p ){
	obrazenia = p.obrazenia;
	return *this;
}

Obrazenia& Obrazenia::operator-=( const Obrazenia& p ){
	obrazenia -= p.obrazenia;
	return *this;
}

Obrazenia& Obrazenia::operator+=( const Obrazenia& p ){
	obrazenia += p.obrazenia;
	return *this;
}

Obrazenia Obrazenia::operator-( const Obrazenia& p )const{
	return Obrazenia( obrazenia - p.obrazenia );
}

Obrazenia Obrazenia::operator+( const Obrazenia& p )const{
	return Obrazenia( obrazenia + p.obrazenia );
}

Obrazenia::type_name Obrazenia::getObrazenia() const{
	return obrazenia;
}

void Obrazenia::setObrazenia( const type_name& f ){
	obrazenia = f;
}

Obrazenia::type_name Obrazenia::value() const{
	return getObrazenia();
}

string Obrazenia::toString() const{
	return Logger::field(CLASSNAME(Obrazenia),obrazenia);
} 