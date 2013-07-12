#include "MocSilnika.h"
#include "Logger.h"
#include "Stale.h"

MocSilnika::MocSilnika()
	: PodstawowyInterfejs( Stale::mocSilnikaDomyslny )
{
}

MocSilnika::MocSilnika( const MocSilnika& a )
	: PodstawowyInterfejs( a )
{
}

MocSilnika::MocSilnika( const type_name& f )
	: PodstawowyInterfejs(f)
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

string MocSilnika::napis() const{
	return Logger::tworzPole(NAZWAKLASY(MocSilnika),wartosc_);
} 