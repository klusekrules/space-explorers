#include "ZuzyciePaliwa.h"
#include "Logger.h"
#include "Stale.h"

ZuzyciePaliwa::ZuzyciePaliwa()
	: PodstawowyInterfejs( Stale::zuzyciePaliwaDomyslny )
{
}

ZuzyciePaliwa::ZuzyciePaliwa( const ZuzyciePaliwa& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

ZuzyciePaliwa::ZuzyciePaliwa( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

ZuzyciePaliwa::~ZuzyciePaliwa(){
}

bool ZuzyciePaliwa::operator==( const ZuzyciePaliwa& wartosc)const{
	return wartosc_==wartosc.wartosc_;
}

bool ZuzyciePaliwa::operator!=( const ZuzyciePaliwa& wartosc)const{
	return wartosc_!=wartosc.wartosc_;
}

bool ZuzyciePaliwa::operator<( const ZuzyciePaliwa& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool ZuzyciePaliwa::operator<=( const ZuzyciePaliwa& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool ZuzyciePaliwa::operator>( const ZuzyciePaliwa& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool ZuzyciePaliwa::operator>=( const ZuzyciePaliwa& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

ZuzyciePaliwa& ZuzyciePaliwa::operator=( const ZuzyciePaliwa& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

ZuzyciePaliwa& ZuzyciePaliwa::operator-=( const ZuzyciePaliwa& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

ZuzyciePaliwa& ZuzyciePaliwa::operator+=( const ZuzyciePaliwa& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

ZuzyciePaliwa ZuzyciePaliwa::operator-( const ZuzyciePaliwa& wartosc )const{
	return ZuzyciePaliwa( wartosc_ - wartosc.wartosc_ );
}

ZuzyciePaliwa ZuzyciePaliwa::operator+( const ZuzyciePaliwa& wartosc )const{
	return ZuzyciePaliwa( wartosc_ + wartosc.wartosc_ );
}

string ZuzyciePaliwa::napis() const{
	return Logger::tworzPole(NAZWAKLASY(ZuzyciePaliwa),wartosc_);
}
