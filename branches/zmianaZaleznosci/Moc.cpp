#include "Moc.h"
#include "Logger.h"
#include "Stale.h"

Moc::Moc()
	: PodstawowyInterfejs( Stale::mocSilnikaDomyslny )
{
}

Moc::Moc( const Moc& wartosc )
	: PodstawowyInterfejs( wartosc )
{
}

Moc::Moc( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Moc::~Moc(){
}

bool Moc::operator==( const Moc& wartosc)const{
	return wartosc_==wartosc.wartosc_;
}

bool Moc::operator!=( const Moc& wartosc)const{
	return wartosc_!=wartosc.wartosc_;
}

bool Moc::operator<( const Moc& wartosc )const{
	return wartosc_ < wartosc.wartosc_;
}

bool Moc::operator<=( const Moc& wartosc )const{
	return wartosc_ <= wartosc.wartosc_;
}

bool Moc::operator>( const Moc& wartosc )const{
	return wartosc_ > wartosc.wartosc_;
}

bool Moc::operator>=( const Moc& wartosc )const{
	return wartosc_ >= wartosc.wartosc_;
}

Moc& Moc::operator=( const Moc& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Moc& Moc::operator-=( const Moc& wartosc ){
	wartosc_ -= wartosc.wartosc_;
	return *this;
}

Moc& Moc::operator+=( const Moc& wartosc ){
	wartosc_ += wartosc.wartosc_;
	return *this;
}

Moc Moc::operator-( const Moc& wartosc )const{
	return Moc( wartosc_ - wartosc.wartosc_ );
}

Moc Moc::operator+( const Moc& wartosc )const{
	return Moc( wartosc_ + wartosc.wartosc_ );
}

std::string Moc::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Moc),wartosc_);
} 
