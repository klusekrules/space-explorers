#include "ZuzyciePaliwa.h"
#include "Logger.h"
#include "Stale.h"

ZuzyciePaliwa::ZuzyciePaliwa()
	: BaseInterface( Stale::zuzyciePaliwaDomyslny )
{
}

ZuzyciePaliwa::ZuzyciePaliwa( const ZuzyciePaliwa& a )
	: BaseInterface( a )
{
}

ZuzyciePaliwa::ZuzyciePaliwa( const type_name& f )
	: BaseInterface(f)
{
}

ZuzyciePaliwa::~ZuzyciePaliwa(){
}

bool ZuzyciePaliwa::operator==( const ZuzyciePaliwa& a)const{
	return wartosc_==a.wartosc_;
}

bool ZuzyciePaliwa::operator!=( const ZuzyciePaliwa& a)const{
	return wartosc_!=a.wartosc_;
}

bool ZuzyciePaliwa::operator<( const ZuzyciePaliwa& a )const{
	return wartosc_ < a.wartosc_;
}

bool ZuzyciePaliwa::operator<=( const ZuzyciePaliwa& a )const{
	return wartosc_ <= a.wartosc_;
}

bool ZuzyciePaliwa::operator>( const ZuzyciePaliwa& a )const{
	return wartosc_ > a.wartosc_;
}

bool ZuzyciePaliwa::operator>=( const ZuzyciePaliwa& a )const{
	return wartosc_ >= a.wartosc_;
}

ZuzyciePaliwa& ZuzyciePaliwa::operator=( const ZuzyciePaliwa& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

ZuzyciePaliwa& ZuzyciePaliwa::operator-=( const ZuzyciePaliwa& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

ZuzyciePaliwa& ZuzyciePaliwa::operator+=( const ZuzyciePaliwa& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

ZuzyciePaliwa ZuzyciePaliwa::operator-( const ZuzyciePaliwa& p )const{
	return ZuzyciePaliwa( wartosc_ - p.wartosc_ );
}

ZuzyciePaliwa ZuzyciePaliwa::operator+( const ZuzyciePaliwa& p )const{
	return ZuzyciePaliwa( wartosc_ + p.wartosc_ );
}

ZuzyciePaliwa::type_name ZuzyciePaliwa::getZuzyciePaliwa() const{
	return wartosc_;
}

void ZuzyciePaliwa::setZuzyciePaliwa( const type_name& f ){
	wartosc_ = f;
}

string ZuzyciePaliwa::toString() const{
	return Logger::field(CLASSNAME(ZuzyciePaliwa),wartosc_);
} 