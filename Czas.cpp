#include "Czas.h" 
#include "Logger.h"
#include "Stale.h"

Czas::Czas()
	: variable( Stale::czasDomyslny )
{
}

Czas::Czas(const Czas& b)
	: variable(b.variable)
{
}

Czas::Czas( const type_name& t )
	: variable(t)
{
}

Czas::~Czas()
{
}

bool Czas::operator==( const Czas& b )const{
	return variable == b.variable;
}

bool Czas::operator!=( const Czas& b )const{
	return variable != b.variable;
}

Czas& Czas::operator=( const Czas& b ){
	variable = b.variable;
	return *this;
}

Czas& Czas::operator+=( const Czas& b ){
	variable += b.variable;
	return *this;
}

Czas& Czas::operator=( const type_name& b ){
	variable = b;
	return *this;
}
	
Czas::type_name Czas::value() const{
	return variable;
}

string Czas::toString() const{
	return Logger::field(CLASSNAME(Czas),variable);
} 
