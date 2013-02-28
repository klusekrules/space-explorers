#include "ZuzyciePaliwa.h"
#include "Logger.h"

ZuzyciePaliwa::ZuzyciePaliwa()
	: zuzyciePaliwa( 0.0f )
{
}

ZuzyciePaliwa::ZuzyciePaliwa( const ZuzyciePaliwa& a )
	: zuzyciePaliwa( a.zuzyciePaliwa )
{
}

ZuzyciePaliwa::ZuzyciePaliwa( const type_name& f )
	: zuzyciePaliwa(f)
{
}

ZuzyciePaliwa::~ZuzyciePaliwa(){
}

bool ZuzyciePaliwa::operator==( const ZuzyciePaliwa& a)const{
	return zuzyciePaliwa==a.zuzyciePaliwa;
}

bool ZuzyciePaliwa::operator!=( const ZuzyciePaliwa& a)const{
	return zuzyciePaliwa!=a.zuzyciePaliwa;
}

bool ZuzyciePaliwa::operator<( const ZuzyciePaliwa& a )const{
	return zuzyciePaliwa < a.zuzyciePaliwa;
}

bool ZuzyciePaliwa::operator<=( const ZuzyciePaliwa& a )const{
	return zuzyciePaliwa <= a.zuzyciePaliwa;
}

bool ZuzyciePaliwa::operator>( const ZuzyciePaliwa& a )const{
	return zuzyciePaliwa > a.zuzyciePaliwa;
}

bool ZuzyciePaliwa::operator>=( const ZuzyciePaliwa& a )const{
	return zuzyciePaliwa >= a.zuzyciePaliwa;
}

ZuzyciePaliwa& ZuzyciePaliwa::operator=( const ZuzyciePaliwa& p ){
	zuzyciePaliwa = p.zuzyciePaliwa;
	return *this;
}

ZuzyciePaliwa& ZuzyciePaliwa::operator-=( const ZuzyciePaliwa& p ){
	zuzyciePaliwa -= p.zuzyciePaliwa;
	return *this;
}

ZuzyciePaliwa& ZuzyciePaliwa::operator+=( const ZuzyciePaliwa& p ){
	zuzyciePaliwa += p.zuzyciePaliwa;
	return *this;
}

ZuzyciePaliwa ZuzyciePaliwa::operator-( const ZuzyciePaliwa& p )const{
	return ZuzyciePaliwa( zuzyciePaliwa - p.zuzyciePaliwa );
}

ZuzyciePaliwa ZuzyciePaliwa::operator+( const ZuzyciePaliwa& p )const{
	return ZuzyciePaliwa( zuzyciePaliwa + p.zuzyciePaliwa );
}

ZuzyciePaliwa::type_name ZuzyciePaliwa::getZuzyciePaliwa() const{
	return zuzyciePaliwa;
}

void ZuzyciePaliwa::setZuzyciePaliwa( const type_name& f ){
	zuzyciePaliwa = f;
}

ZuzyciePaliwa::type_name ZuzyciePaliwa::value() const{
	return getZuzyciePaliwa();
}

string ZuzyciePaliwa::toString() const{
	return Logger::field(className(),zuzyciePaliwa);
} 