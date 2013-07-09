#include "MocSilnika.h"
#include "Logger.h"
#include "Stale.h"

MocSilnika::MocSilnika()
	: BaseInterface( Stale::mocSilnikaDomyslny )
{
}

MocSilnika::MocSilnika( const MocSilnika& a )
	: BaseInterface( a )
{
}

MocSilnika::MocSilnika( const type_name& f )
	: BaseInterface(f)
{
}

MocSilnika::~MocSilnika(){
}

bool MocSilnika::operator==( const MocSilnika& a)const{
	return wartosc_==a.wartosc_;
}

bool MocSilnika::operator!=( const MocSilnika& a)const{
	return wartosc_!=a.wartosc_;
}

bool MocSilnika::operator<( const MocSilnika& a )const{
	return wartosc_ < a.wartosc_;
}

bool MocSilnika::operator<=( const MocSilnika& a )const{
	return wartosc_ <= a.wartosc_;
}

bool MocSilnika::operator>( const MocSilnika& a )const{
	return wartosc_ > a.wartosc_;
}

bool MocSilnika::operator>=( const MocSilnika& a )const{
	return wartosc_ >= a.wartosc_;
}

MocSilnika& MocSilnika::operator=( const MocSilnika& p ){
	wartosc_ = p.wartosc_;
	return *this;
}

MocSilnika& MocSilnika::operator-=( const MocSilnika& p ){
	wartosc_ -= p.wartosc_;
	return *this;
}

MocSilnika& MocSilnika::operator+=( const MocSilnika& p ){
	wartosc_ += p.wartosc_;
	return *this;
}

MocSilnika MocSilnika::operator-( const MocSilnika& p )const{
	return MocSilnika( wartosc_ - p.wartosc_ );
}

MocSilnika MocSilnika::operator+( const MocSilnika& p )const{
	return MocSilnika( wartosc_ + p.wartosc_ );
}

MocSilnika::type_name MocSilnika::getMocSilnika() const{
	return wartosc_;
}

void MocSilnika::setMocSilnika( const type_name& f ){
	wartosc_ = f;
}

string MocSilnika::toString() const{
	return Logger::field(CLASSNAME(MocSilnika),wartosc_);
} 