#include "MocSilnika.h"
#include "Logger.h"
#include "Stale.h"

MocSilnika::MocSilnika()
	: PodstawowyInterfejs( Stale::mocSilnikaDomyslny )
{
}

MocSilnika::MocSilnika( const MocSilnika& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

MocSilnika::MocSilnika( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

MocSilnika::~MocSilnika(){
}

bool MocSilnika::operator==( const MocSilnika& wartosc)const{
	return wartosc_==wartosc.wartosc_;
}

bool MocSilnika::operator!=( const MocSilnika& wartosc)const{
	return wartosc_!=wartosc.wartosc_;
}

bool MocSilnika::operator<( const MocSilnika& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool MocSilnika::operator<=( const MocSilnika& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool MocSilnika::operator>( const MocSilnika& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool MocSilnika::operator>=( const MocSilnika& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

MocSilnika& MocSilnika::operator=( const MocSilnika& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

MocSilnika& MocSilnika::operator-=( const MocSilnika& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

MocSilnika& MocSilnika::operator+=( const MocSilnika& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

MocSilnika MocSilnika::operator-( const MocSilnika& wartosc )const{
	return MocSilnika( wartosc_ - wartosc.wartosc_ );
}

MocSilnika MocSilnika::operator+( const MocSilnika& wartosc )const{
	return MocSilnika( wartosc_ + wartosc.wartosc_ );
}

string MocSilnika::napis() const{
	return Logger::tworzPole(NAZWAKLASY(MocSilnika),wartosc_);
} 
