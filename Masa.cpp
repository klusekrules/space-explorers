#include "Masa.h"
#include "Logger.h"
#include "Stale.h"

Masa::Masa()
	: masa( Stale::masaDomyslny )
{
}

Masa::Masa( const Masa& a )
	: masa( a.masa )
{
}

Masa::Masa( const type_name& f )
	: masa(f)
{
}

Masa::~Masa(){
}

bool Masa::operator==( const Masa& a)const{
	return masa==a.masa;
}

bool Masa::operator!=( const Masa& a)const{
	return masa!=a.masa;
}

bool Masa::operator<( const Masa& a )const{
	return masa < a.masa;
}

bool Masa::operator<=( const Masa& a )const{
	return masa <= a.masa;
}

bool Masa::operator>( const Masa& a )const{
	return masa > a.masa;
}

bool Masa::operator>=( const Masa& a )const{
	return masa >= a.masa;
}

Masa& Masa::operator=( const Masa& p ){
	masa = p.masa;
	return *this;
}

Masa& Masa::operator-=( const Masa& p ){
	masa -= p.masa;
	return *this;
}

Masa& Masa::operator+=( const Masa& p ){
	masa += p.masa;
	return *this;
}

Masa Masa::operator-( const Masa& p )const{
	return Masa( masa - p.masa );
}

Masa Masa::operator+( const Masa& p )const{
	return Masa( masa + p.masa );
}

Masa Masa::operator*( const Fluktuacja& f )const{
	return Masa( masa * f.getFluktuacja() );
}

Masa& Masa::operator*=( const Fluktuacja& f ){
	masa *= f.getFluktuacja();
	return *this;
}

Masa Masa::operator*( const Ilosc& f )const{
	return Masa( masa * f.getIlosc() );
}

Masa& Masa::operator*=( const Ilosc& f ){
	masa *= f.getIlosc();
	return *this;
}

Masa::type_name Masa::getMasa() const{
	return masa;
}

void Masa::setMasa( const type_name& f ){
	masa = f;
}

Masa::type_name Masa::value() const{
	return getMasa();
}

string Masa::toString() const{
	return Logger::field(className(),masa);
} 