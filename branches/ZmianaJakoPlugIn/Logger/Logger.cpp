#include "Logger.h"

Logger::Logger()
{
	stos.push(true);
}

Logger::~Logger(){
}

Logger::Logger( const string& nazwa )
{
	stos.push(true);
	napis<<nazwa<<"[";
}

string Logger::toString() const{
	return napis.str() + " ]";
}

void Logger::addClass( const string& tekst ){
	testPierwszy();
	napis<<" "<<tekst;
}
