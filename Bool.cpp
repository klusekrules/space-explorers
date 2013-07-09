#include "Bool.h"
#include "Logger.h"
#include "Stale.h"

Bool::Bool()
	: BaseInterface( Stale::boolDomyslny )
{
}

Bool::Bool( const Bool& b )
	: BaseInterface(b)
{
}

Bool::Bool( const type_name& t )
	: BaseInterface(t)
{
}

Bool::~Bool(){
}

bool Bool::operator==( const Bool& b )const{
	return wartosc_ == b.wartosc_;
}

bool Bool::operator!=( const Bool& b )const{
	return wartosc_ != b.wartosc_;
}

Bool& Bool::operator=( const Bool& b ){
	wartosc_ = b.wartosc_;
	return *this;
}

Bool& Bool::operator=( const type_name& b ){
	wartosc_ = b;
	return *this;
}

string Bool::toString() const{
	stringstream str;
	str << boolalpha << wartosc_;
	return str.str();
} 