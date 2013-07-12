#include "Log.h"
#include <fstream>
#include <time.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std::chrono;
void Log::wyswietl( const string& p ) const{
	cout << p;
	for( auto f : outstream)
		(*f)<<p;
}

void Log::dodajGniazdoWyjsciowe(shared_ptr<ostream> &t){
	outstream.push_back(t);
}

Log::Log()
	:logiOdblokowane_(true), logiDebugOdblokowane_(true), logiInfoOdblokowane_(true),
	logiWarnOdblokowane_(true), logiErrorOdblokowane_(true),formatCzasu_("%Y-%m-%d %H:%M:%S")
{
}

void Log::ustawFormatCzasu( FormatCzasu format ){
	switch (format)
	{
	case Log::Data: formatCzasu_="%Y-%m-%d";
		break;
	case Log::Czas: formatCzasu_="%H:%M:%S";
		break;
	case Log::DataCzas: formatCzasu_="%Y-%m-%d %H:%M:%S";
		break;
	default:
		break;
	}
}

Log& Log::pobierzInstancje(){
	static Log log;
	return log;
}

bool Log::czyLogiOdblokowane()const{
	return logiOdblokowane_;
}

bool Log::czyLogiDebugOdblokowane()const{
	return logiOdblokowane_ ? logiDebugOdblokowane_ : false;
}

bool Log::czyLogiInfoOdblokowane()const{
	return logiOdblokowane_ ? logiInfoOdblokowane_ : false;
}

bool Log::czyLogiWarnOdblokowane()const{
	return logiOdblokowane_ ? logiWarnOdblokowane_ : false;
}

bool Log::czyLogiErrorOdblokowane()const{
	return logiOdblokowane_ ? logiErrorOdblokowane_ : false;
}

void Log::odblokujLogi(){
	logiOdblokowane_ = true;
}

void Log::zablokujLogi(){
	logiOdblokowane_ = false;
}

void Log::odblokujLogiDebug(){
	logiDebugOdblokowane_ = true;
}

void Log::zablokujLogiDebug(){
	logiDebugOdblokowane_ = false;
}

void Log::odblokujLogiInfo(){
	logiInfoOdblokowane_ = true;
}

void Log::zablokujLogiInfo(){
	logiInfoOdblokowane_ = false;
}

void Log::odblokujLogiWarn(){
	logiWarnOdblokowane_ = true;
}

void Log::zablokujLogiWarn(){
	logiWarnOdblokowane_ = false;
}

void Log::odblokujLogiError(){
	logiErrorOdblokowane_ = true;
}

void Log::zablokujLogiError(){
	logiErrorOdblokowane_ = false;
}

void Log::info( const string& komunikat ){
	if(logiOdblokowane_ && logiInfoOdblokowane_){
		wyswietl( pobierzDateCzas() + " [INFO] " + komunikat + "\n" );
	}
}

void Log::info( const LoggerInterface& komunikat ){
	if(logiOdblokowane_ && logiInfoOdblokowane_){
		wyswietl( pobierzDateCzas() + " [INFO] " + komunikat.napis() + "\n" );
	}
}

void Log::warn( const string& komunikat ){
	if(logiOdblokowane_ && logiWarnOdblokowane_){
		wyswietl( pobierzDateCzas() + " [WARN] " + komunikat + "\n" );
	}
}

void Log::warn( const LoggerInterface& komunikat ){
	if(logiOdblokowane_ && logiWarnOdblokowane_){
		wyswietl( pobierzDateCzas() + " [WARN] " + komunikat.napis() + "\n" );
	}
}

void Log::error( const string& komunikat ){
	if(logiOdblokowane_ && logiErrorOdblokowane_){
		wyswietl( pobierzDateCzas() + " [ERROR] " + komunikat + "\n" );
	}
}

void Log::error( const LoggerInterface& komunikat ){
	if(logiOdblokowane_ && logiErrorOdblokowane_){
		wyswietl( pobierzDateCzas() + " [ERROR] " + komunikat.napis() + "\n" );
	}
}

void Log::debug( const string& komunikat ){
	if(logiOdblokowane_ && logiDebugOdblokowane_){
		wyswietl( pobierzDateCzas() + " [DEBUG] " + komunikat + "\n" );
	}
}

void Log::debug( const LoggerInterface& komunikat ){
	if(logiOdblokowane_ && logiDebugOdblokowane_){
		wyswietl( pobierzDateCzas() + " [DEBUG] " + komunikat.napis() + "\n" );
	}
}

string Log::pobierzDateCzas() const{
	steady_clock::time_point t1 = steady_clock::now();
	steady_clock::duration dtn = t1.time_since_epoch();
	time_t pSekundy = dtn.count() * steady_clock::period::num / steady_clock::period::den;
	struct tm timeinfo;
	localtime_s(&timeinfo,&pSekundy);
	short unsigned int pMilisekundy = static_cast<long long>( dtn.count() * ( static_cast<long double>(steady_clock::period::num) / static_cast<long double>(steady_clock::period::den) ) * 1000 ) % 1000;
	char s[20];
	strftime(s,20,formatCzasu_.c_str(),&timeinfo);
	stringstream str;
	str << s << "." << setw (3) << setfill ('0') << pMilisekundy;
	return str.str();
}
