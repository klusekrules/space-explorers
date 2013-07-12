#include "ZuzyciePaliwa.h"
#include "Logger.h"
#include "Stale.h"

ZuzyciePaliwa::ZuzyciePaliwa()
	: PodstawowyInterfejs( Stale::zuzyciePaliwaDomyslny )
{
}

ZuzyciePaliwa::ZuzyciePaliwa( const ZuzyciePaliwa& a )
	: PodstawowyInterfejs( a )
{
}

ZuzyciePaliwa::ZuzyciePaliwa( const type_name& f )
	: PodstawowyInterfejs(f)
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

string ZuzyciePaliwa::napis() const{
	return Logger::tworzPole(NAZWAKLASY(ZuzyciePaliwa),wartosc_);
} 