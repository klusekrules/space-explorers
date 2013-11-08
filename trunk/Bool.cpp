#include "Bool.h"
#include "Logger.h"
#include "Stale.h"
#include <iomanip>

Bool::Bool()
	: PodstawowyInterfejs( Stale::boolDomyslny )
{
}

Bool::Bool( const Bool& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Bool::Bool( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Bool::~Bool(){
}

bool Bool::operator==( const Bool& wartosc )const{
	return wartosc_ == wartosc.wartosc_;
}

bool Bool::operator!=( const Bool& wartosc )const{
	return wartosc_ != wartosc.wartosc_;
}

Bool& Bool::operator=( const Bool& wartosc ){
	wartosc_ = wartosc.wartosc_;
	return *this;
}

Bool& Bool::operator=( const type_name& wartosc ){
	wartosc_ = wartosc;
	return *this;
}

std::string Bool::napis() const{
	std::stringstream str;
	str << std::boolalpha << wartosc_;
	return str.str();
} 
