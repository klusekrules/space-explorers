#include "Masa.h"
#include "Logger.h"
#include "Stale.h"

Masa::Masa()
	: BaseInterface( Stale::masaDomyslny )
{
}

Masa::Masa( const Masa& a )
	: BaseInterface( a )
{
}

Masa::Masa( const type_name& f )
	: BaseInterface(f)
{
}

Masa::~Masa(){
}

bool Masa::operator==( const Masa& a)const{
	return wartosc_==a.wartosc_;
}

bool Masa::operator!=( const Masa& a)const{
	return wartosc_!=a.wartosc_;
}

bool Masa::operator<( const Masa& a )const{
	return wartosc_ < a.wartosc_;
}

bool Masa::operator<=( const Masa& a )const{
	return wartosc_ <= a.wartosc_;
}

bool Masa::operator>( const Masa& a )const{
	return wartosc_ > a.wartosc_;
}

bool Masa::operator>=( const Masa& a )const{
	return wartosc_ >= a.wartosc_;
}

Masa& Masa::operator=( const Masa& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

Masa& Masa::operator-=( const Masa& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

Masa& Masa::operator+=( const Masa& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

Masa Masa::operator-( const Masa& p )const{
	return Masa( wartosc_ - p.wartosc_ );
}

Masa Masa::operator+( const Masa& p )const{
	return Masa( wartosc_ + p.wartosc_ );
}

Masa Masa::operator*( const Fluktuacja& f )const{
	return Masa( wartosc_ * f.getFluktuacja() );
}

Masa& Masa::operator*=( const Fluktuacja& f ){
	wartosc_ *= f.getFluktuacja();
	return *this;
}

Masa Masa::operator*( const Ilosc& f )const{
	return Masa( wartosc_ * f.getIlosc() );
}

Masa& Masa::operator*=( const Ilosc& f ){
	wartosc_ *= f.getIlosc();
	return *this;
}

Masa::type_name Masa::getMasa() const{
	return wartosc_;
}

void Masa::setMasa( const type_name& f ){
	wartosc_ = f;
}

string Masa::toString() const{
	return Logger::field(CLASSNAME(Masa),wartosc_);
} 