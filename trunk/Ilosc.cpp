#include "Ilosc.h"
#include "Logger.h"

Ilosc::Ilosc()
	: ilosc( iloscDomyslny )
{
}

Ilosc::Ilosc( const type_name& ilosc )
	: ilosc(ilosc)
{
}

Ilosc::Ilosc( const Ilosc& ilosc )
	: ilosc(ilosc.ilosc)
{
}

Ilosc::~Ilosc(){
}

bool Ilosc::operator<( const Ilosc& i ) const{
	return ilosc < i.ilosc;
}

bool Ilosc::operator>( const Ilosc& i ) const{
	return ilosc > i.ilosc;
}

bool Ilosc::operator==( const Ilosc& i ) const{
	return ilosc == i.ilosc;
}

bool Ilosc::operator!=( const Ilosc& i ) const{
	return ilosc != i.ilosc;
}

bool Ilosc::operator<=( const Ilosc& i) const{
	return ilosc <= i.ilosc;
}

bool Ilosc::operator>=( const Ilosc& i) const{
	return ilosc >= i.ilosc;
}

Ilosc Ilosc::operator+( const Ilosc& i ) const{
	return Ilosc( ilosc + i.ilosc );
}

Ilosc Ilosc::operator-( const Ilosc& i ) const{
	return Ilosc( ilosc - i.ilosc );
}

Ilosc& Ilosc::operator+=( const Ilosc& i ){
	ilosc+=i.ilosc;
	return *this;
}

Ilosc& Ilosc::operator-=( const Ilosc& i ){
	ilosc-=i.ilosc;
	return *this;
}

Ilosc& Ilosc::operator=( const Ilosc& i ){
	ilosc=i.ilosc;
	return *this;
}

Ilosc::type_name Ilosc::getIlosc()const{
	return ilosc;
}

void Ilosc::setIlosc( const type_name& ilosc ){
	this->ilosc = ilosc;
}

Ilosc::type_name Ilosc::value() const{
	return getIlosc();
}

string Ilosc::toString() const{
	return Logger::field(className(),ilosc);
}

