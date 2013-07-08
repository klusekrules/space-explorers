#include "Objetosc.h"
#include "Logger.h"
#include "Stale.h"

Objetosc::Objetosc()
	: objetosc( Stale::objetoscDomyslny )
{
}

Objetosc::Objetosc( const Objetosc& a )
	: objetosc( a.objetosc )
{
}

Objetosc::Objetosc( const type_name& f )
	: objetosc(f)
{
}

Objetosc::~Objetosc(){
}

bool Objetosc::operator==( const Objetosc& a)const{
	return objetosc==a.objetosc;
}

bool Objetosc::operator!=( const Objetosc& a)const{
	return objetosc!=a.objetosc;
}

bool Objetosc::operator<( const Objetosc& a )const{
	return objetosc < a.objetosc;
}

bool Objetosc::operator<=( const Objetosc& a )const{
	return objetosc <= a.objetosc;
}

bool Objetosc::operator>( const Objetosc& a )const{
	return objetosc > a.objetosc;
}

bool Objetosc::operator>=( const Objetosc& a )const{
	return objetosc >= a.objetosc;
}

Objetosc& Objetosc::operator=( const Objetosc& p ){
	objetosc = p.objetosc;
	return *this;
}

Objetosc& Objetosc::operator-=( const Objetosc& p ){
	objetosc -= p.objetosc;
	return *this;
}

Objetosc& Objetosc::operator+=( const Objetosc& p ){
	objetosc += p.objetosc;
	return *this;
}

Objetosc Objetosc::operator-( const Objetosc& p )const{
	return Objetosc( objetosc - p.objetosc );
}

Objetosc Objetosc::operator+( const Objetosc& p )const{
	return Objetosc( objetosc + p.objetosc );
}

Objetosc Objetosc::operator*( const Ilosc& f )const{
	return Objetosc( objetosc * f.getIlosc() );
}

Objetosc& Objetosc::operator*=( const Ilosc& f ){
	objetosc *= f.getIlosc();
	return *this; 
}

Objetosc Objetosc::operator*( const Fluktuacja& f )const{
	return Objetosc( objetosc * f.getFluktuacja() );
}

Objetosc& Objetosc::operator*=( const Fluktuacja& f ){
	objetosc *= f.getFluktuacja();
	return *this; 
}

Fluktuacja Objetosc::operator/( const Objetosc& o )const{
	return Fluktuacja( static_cast<const float>(objetosc / o.objetosc) );
}

Objetosc::type_name Objetosc::getObjetosc() const{
	return objetosc;
}

void Objetosc::setObjetosc( const type_name& f ){
	objetosc = f;
}

Objetosc::type_name Objetosc::value() const{
	return getObjetosc();
}

string Objetosc::toString() const{
	stringstream str;
	str.precision(25);
	str<<fixed<< objetosc;
	return str.str();
} 