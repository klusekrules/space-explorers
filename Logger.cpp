#include "Logger.h"

Logger::Logger()
{
	stos_.push(true);
}

Logger::~Logger(){
}

Logger::Logger( const string& nazwa )
{
	stos_.push(true);
	napis_<<nazwa<<"[";
}

string Logger::napis() const{
	return napis_.str() + " ]";
}

void Logger::dodajKlase( const string& opisKlasy ){
	testPierwszegoPola();
	napis_<<" "<<opisKlasy;
}

string Logger::tworzPole( const string& nazwa, const LoggerInterface& obiektPierwszy, const LoggerInterface& obiektDrugi ){
	stringstream str;
	str << nazwa << " { " << obiektPierwszy.napis() << " , " << obiektDrugi.napis() <<" }";
	return str.str();
}

string Logger::tworzKlase( const string& nazwaKlasy, const string& opisKlasy ){
	return string( nazwaKlasy + "[ " + opisKlasy + " ]" );
}

void Logger::dodajPole( const string& nazwa, const LoggerInterface& obiekt ){
	dodajPole( nazwa, obiekt.napis() );
}

void Logger::dodajPole( const string& nazwa, const shared_ptr<LoggerInterface> obiekt ){
	if(obiekt)
		dodajPole( nazwa, obiekt->napis() );
}

void Logger::dodajPole( const string& nazwa, const string& opisPola ){
	testPierwszegoPola();
	napis_ << " "  << nazwa << "=" << opisPola;
}

void Logger::dodajPole( const string& nazwa, const LoggerInterface& obiektPierwszy, const LoggerInterface& obiektDrugi ){
	testPierwszegoPola();
	napis_ << nazwa << " { " << obiektPierwszy.napis() << " , " << obiektDrugi.napis() <<" }";
}

void Logger::rozpocznijPodKlase( const string& nazwa ){
	testPierwszegoPola();
	napis_ << nazwa << "[ ";
	stos_.push(true);
}

void Logger::zakonczPodKlase(){
	stos_.pop();
	napis_ << " ]";
}

void Logger::testPierwszegoPola( ){
	if(!stos_.top())
		napis_<<", ";
	else
		stos_.top() = false;
}
