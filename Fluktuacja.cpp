#include "Fluktuacja.h"
#include "Logger.h"
#include "Stale.h"

Fluktuacja::Fluktuacja()
	: fluktuacja( Stale::fluktuacjaDomyslny )
{
}

Fluktuacja::Fluktuacja( const Fluktuacja& a )
	: fluktuacja( a.fluktuacja )
{
}

Fluktuacja::Fluktuacja( const type_name& f )
	: fluktuacja(f)
{
}

Fluktuacja::~Fluktuacja(){
}

bool Fluktuacja::operator==( const Fluktuacja& a)const{
	return fluktuacja==a.fluktuacja;
}

bool Fluktuacja::operator!=( const Fluktuacja& a)const{
	return fluktuacja!=a.fluktuacja;
}

bool Fluktuacja::operator<( const Fluktuacja& a )const{
	return fluktuacja < a.fluktuacja;
}

bool Fluktuacja::operator>( const Fluktuacja& a)const{
	return fluktuacja > a.fluktuacja;
}

bool Fluktuacja::operator<=( const Fluktuacja& a)const{
	return fluktuacja <= a.fluktuacja;
}

bool Fluktuacja::operator>=( const Fluktuacja& a)const{
	return fluktuacja >= a.fluktuacja;
}

Fluktuacja& Fluktuacja::operator=( const Fluktuacja& p ){
	fluktuacja = p.fluktuacja;
	return *this;
}

Fluktuacja& Fluktuacja::operator-=( const Fluktuacja& p ){
	fluktuacja -= p.fluktuacja;
	return *this;
}

Fluktuacja& Fluktuacja::operator+=( const Fluktuacja& p ){
	fluktuacja += p.fluktuacja;
	return *this;
}

Fluktuacja Fluktuacja::operator-( const Fluktuacja& p )const{
	return Fluktuacja( fluktuacja - p.fluktuacja );
}

Fluktuacja Fluktuacja::operator+( const Fluktuacja& p )const{
	return Fluktuacja( fluktuacja + p.fluktuacja );
}

Fluktuacja::type_name Fluktuacja::getFluktuacja() const{
	return fluktuacja;
}

void Fluktuacja::setFluktuacja( const type_name& f ){
	fluktuacja = f;
}

Fluktuacja::type_name Fluktuacja::value() const{
	return getFluktuacja();
}

string Fluktuacja::toString() const{
	return Logger::field(className(),fluktuacja);
} 