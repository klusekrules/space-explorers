#include "Dystans.h"
#include "Logger.h"
#include "Stale.h"

Dystans::Dystans()
	: dystans( Stale::dystansDomyslny )
{
}

Dystans::Dystans( const Dystans& a )
	: dystans( a.dystans )
{
}

Dystans::Dystans( const type_name& f )
	: dystans(f)
{
}

Dystans::~Dystans(){
}

bool Dystans::operator==( const Dystans& a)const{
	return dystans==a.dystans;
}

bool Dystans::operator!=( const Dystans& a)const{
	return dystans!=a.dystans;
}

bool Dystans::operator<( const Dystans& a )const{
	return dystans < a.dystans;
}

bool Dystans::operator<=( const Dystans& a )const{
	return dystans <= a.dystans;
}

bool Dystans::operator>( const Dystans& a )const{
	return dystans > a.dystans;
}

bool Dystans::operator>=( const Dystans& a )const{
	return dystans >= a.dystans;
}

Dystans& Dystans::operator=( const Dystans& p ){
	dystans = p.dystans;
	return *this;
}

Dystans& Dystans::operator-=( const Dystans& p ){
	dystans -= p.dystans;
	return *this;
}

Dystans& Dystans::operator+=( const Dystans& p ){
	dystans += p.dystans;
	return *this;
}

Dystans Dystans::operator-( const Dystans& p )const{
	return Dystans( dystans - p.dystans );
}

Dystans Dystans::operator+( const Dystans& p )const{
	return Dystans( dystans + p.dystans );
}

Dystans::type_name Dystans::getDystans() const{
	return dystans;
}

void Dystans::setDystans( const type_name& f ){
	dystans = f;
}

Dystans::type_name Dystans::value() const{
	return getDystans();
}

string Dystans::toString() const{
	return Logger::field(CLASSNAME(Dystans),dystans);
} 