#include "Powierzchnia.h"
#include "Logger.h"
#include "Stale.h"

Powierzchnia::Powierzchnia()
	: powierzchnia( Stale::powierzchniaDomyslny )
{
}

Powierzchnia::Powierzchnia( const Powierzchnia& a )
	: powierzchnia( a.powierzchnia )
{
}

Powierzchnia::Powierzchnia( const type_name& f )
	: powierzchnia(f)
{
}

Powierzchnia::~Powierzchnia(){
}

bool Powierzchnia::operator==( const Powierzchnia& a)const{
	return powierzchnia==a.powierzchnia;
}

bool Powierzchnia::operator!=( const Powierzchnia& a)const{
	return powierzchnia!=a.powierzchnia;
}

bool Powierzchnia::operator<( const Powierzchnia& a )const{
	return powierzchnia < a.powierzchnia;
}

bool Powierzchnia::operator<=( const Powierzchnia& a )const{
	return powierzchnia <= a.powierzchnia;
}

bool Powierzchnia::operator>( const Powierzchnia& a )const{
	return powierzchnia > a.powierzchnia;
}

bool Powierzchnia::operator>=( const Powierzchnia& a )const{
	return powierzchnia >= a.powierzchnia;
}

Powierzchnia& Powierzchnia::operator=( const Powierzchnia& p ){
	powierzchnia = p.powierzchnia;
	return *this;
}

Powierzchnia& Powierzchnia::operator-=( const Powierzchnia& p ){
	powierzchnia -= p.powierzchnia;
	return *this;
}

Powierzchnia& Powierzchnia::operator+=( const Powierzchnia& p ){
	powierzchnia += p.powierzchnia;
	return *this;
}

Powierzchnia Powierzchnia::operator-( const Powierzchnia& p )const{
	return Powierzchnia( powierzchnia - p.powierzchnia );
}

Powierzchnia Powierzchnia::operator+( const Powierzchnia& p )const{
	return Powierzchnia( powierzchnia + p.powierzchnia );
}

Powierzchnia Powierzchnia::operator*( const Fluktuacja& f )const{
	return Powierzchnia( powierzchnia * f.getFluktuacja() );
}

Powierzchnia& Powierzchnia::operator*=( const Fluktuacja& f ){
	powierzchnia *= f.getFluktuacja();
	return *this;
}
Powierzchnia Powierzchnia::operator*( const Ilosc& f )const{
	return Powierzchnia( powierzchnia * f.getIlosc() );
}

Powierzchnia& Powierzchnia::operator*=( const Ilosc& f ){
	powierzchnia *= f.getIlosc();
	return *this;
}
Powierzchnia::type_name Powierzchnia::getPowierzchnia() const{
	return powierzchnia;
}

void Powierzchnia::setPowierzchnia( const type_name& f ){
	powierzchnia = f;
}

Powierzchnia::type_name Powierzchnia::value() const{
	return getPowierzchnia();
}

string Powierzchnia::toString() const{
	return Logger::field(CLASSNAME(Powierzchnia),powierzchnia);
} 