#include "Bool.h"
#include "../Logger/Logger.h"
#include "Stale.h"

Bool::Bool()
	: bBool( Stale::boolDomyslny	)
{
}

Bool::Bool(const Bool& b)
	: bBool(b.bBool)
{
}

Bool::Bool( const type_name& t )
	: bBool(t)
{
}


Bool::~Bool()
{
}


bool Bool::operator==( const Bool& b )const{
	return bBool == b.bBool;
}
bool Bool::operator!=( const Bool& b )const{
	return bBool != b.bBool;
}

Bool& Bool::operator=( const Bool& b ){
	bBool = b.bBool;
	return *this;
}

Bool& Bool::operator=( const type_name& b ){
	bBool = b;
	return *this;
}
	
Bool::type_name Bool::value() const{
	return bBool;
}

string Bool::toString() const{
	stringstream str;
	str << boolalpha << bBool;
	return str.str();
} 