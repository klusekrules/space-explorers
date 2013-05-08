#include "Predkosc.h"
#include "../Logger/Logger.h"
#include "Stale.h"

Predkosc::Predkosc()
	: predkosc( Stale::predkoscDOmyslny )
{
}

Predkosc::Predkosc( const Predkosc& a )
	: predkosc( a.predkosc )
{
}

Predkosc::Predkosc( const type_name& f )
	: predkosc(f)
{
}

Predkosc::~Predkosc(){
}

bool Predkosc::operator==( const Predkosc& a)const{
	return predkosc==a.predkosc;
}

bool Predkosc::operator!=( const Predkosc& a)const{
	return predkosc!=a.predkosc;
}

bool Predkosc::operator<( const Predkosc& a )const{
	return predkosc < a.predkosc;
}

bool Predkosc::operator<=( const Predkosc& a )const{
	return predkosc <= a.predkosc;
}

bool Predkosc::operator>( const Predkosc& a )const{
	return predkosc > a.predkosc;
}

bool Predkosc::operator>=( const Predkosc& a )const{
	return predkosc >= a.predkosc;
}

Predkosc& Predkosc::operator=( const Predkosc& p ){
	predkosc = p.predkosc;
	return *this;
}

Predkosc& Predkosc::operator-=( const Predkosc& p ){
	predkosc -= p.predkosc;
	return *this;
}

Predkosc& Predkosc::operator+=( const Predkosc& p ){
	predkosc += p.predkosc;
	return *this;
}

Predkosc Predkosc::operator-( const Predkosc& p )const{
	return Predkosc( predkosc - p.predkosc );
}

Predkosc Predkosc::operator+( const Predkosc& p )const{
	return Predkosc( predkosc + p.predkosc );
}

Predkosc::type_name Predkosc::getPredkosc() const{
	return predkosc;
}

void Predkosc::setPredkosc( const type_name& f ){
	predkosc = f;
}

Predkosc::type_name Predkosc::value() const{
	return getPredkosc();
}

string Predkosc::toString() const{
	return Logger::field(CLASSNAME(Predkosc),predkosc);
} 