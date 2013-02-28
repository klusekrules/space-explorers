#include "MocSilnika.h"
#include "Logger.h"

MocSilnika::MocSilnika()
	: mocSilnika( 0.0f )
{
}

MocSilnika::MocSilnika( const MocSilnika& a )
	: mocSilnika( a.mocSilnika )
{
}

MocSilnika::MocSilnika( const type_name& f )
	: mocSilnika(f)
{
}

MocSilnika::~MocSilnika(){
}

bool MocSilnika::operator==( const MocSilnika& a)const{
	return mocSilnika==a.mocSilnika;
}

bool MocSilnika::operator!=( const MocSilnika& a)const{
	return mocSilnika!=a.mocSilnika;
}

bool MocSilnika::operator<( const MocSilnika& a )const{
	return mocSilnika < a.mocSilnika;
}

bool MocSilnika::operator<=( const MocSilnika& a )const{
	return mocSilnika <= a.mocSilnika;
}

bool MocSilnika::operator>( const MocSilnika& a )const{
	return mocSilnika > a.mocSilnika;
}

bool MocSilnika::operator>=( const MocSilnika& a )const{
	return mocSilnika >= a.mocSilnika;
}

MocSilnika& MocSilnika::operator=( const MocSilnika& p ){
	mocSilnika = p.mocSilnika;
	return *this;
}

MocSilnika& MocSilnika::operator-=( const MocSilnika& p ){
	mocSilnika -= p.mocSilnika;
	return *this;
}

MocSilnika& MocSilnika::operator+=( const MocSilnika& p ){
	mocSilnika += p.mocSilnika;
	return *this;
}

MocSilnika MocSilnika::operator-( const MocSilnika& p )const{
	return MocSilnika( mocSilnika - p.mocSilnika );
}

MocSilnika MocSilnika::operator+( const MocSilnika& p )const{
	return MocSilnika( mocSilnika + p.mocSilnika );
}

MocSilnika::type_name MocSilnika::getMocSilnika() const{
	return mocSilnika;
}

void MocSilnika::setMocSilnika( const type_name& f ){
	mocSilnika = f;
}

MocSilnika::type_name MocSilnika::value() const{
	return getMocSilnika();
}

string MocSilnika::toString() const{
	return Logger::field(className(),mocSilnika);
} 