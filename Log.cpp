#include "Log.h"
#include <fstream>
#include <time.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std::chrono;
void Log::print( const string& p ){
	cout << p;
	for( auto f : outstream)
		(*f)<<p;
}

void Log::dodajGniazdoWyjsciowe(shared_ptr<ostream> &t){
	outstream.push_back(t);
}

Log::Log()
	:blogEnable(true), blogDebugEnable(true), blogInfoEnable(true), blogWarnEnable(true), blogErrorEnable(true)
{
}

Log& Log::getInstance(){
	static Log log;
	return log;
}

bool Log::isLogEnable()const{
	return blogEnable;
}

bool Log::isLogDebugEnable()const{
	return blogEnable ? blogDebugEnable : false;
}

	
bool Log::isLogInfoEnable()const{
	return blogEnable ? blogInfoEnable : false;
}

bool Log::isLogWarnEnable()const{
	return blogEnable ? blogWarnEnable : false;
}

	
bool Log::isLogErrorEnable()const{
	return blogEnable ? blogErrorEnable : false;
}

	
void Log::logEnable(){
	blogEnable = true;
}
	
	
void Log::logDisable(){
	blogEnable = false;
}

	
void Log::logDebugEnable(){
	blogDebugEnable = true;
}
	
void Log::logDebugDisable(){
	blogDebugEnable = false;
}

	
void Log::logInfoEnable(){
	blogInfoEnable = true;
}
	
	
void Log::logInfoDisable(){
	blogInfoEnable = false;
}

void Log::logWarnEnable(){
	blogWarnEnable = true;
}
	
void Log::logWarnDisable(){
	blogWarnEnable = false;
}


void Log::logErrorEnable(){
	blogErrorEnable = true;
}
	
	
void Log::logErrorDisable(){
	blogErrorEnable = false;
}

	
void Log::info( const string& p ){
	if(blogEnable && blogInfoEnable){
		print(getTimeStamp());
		print(" [INFO] ");
		print(p);
		print("\n");
	}
}

	
void Log::info( const LoggerInterface& p ){
	if(blogEnable && blogInfoEnable){
		print(getTimeStamp());
		print(" [INFO] ");
		print(p.toString());
		print("\n");
	}
}

void Log::warn( const string& p ){
	if(blogEnable && blogWarnEnable){
		print(getTimeStamp());
		print(" [WARN] ");
		print(p);
		print("\n");
	}
}

void Log::warn( const LoggerInterface& p ){
	if(blogEnable && blogWarnEnable){
		print(getTimeStamp());
		print(" [WARN] ");
		print(p.toString());
		print("\n");
	}
}

void Log::error( const string& p ){
	if(blogEnable && blogErrorEnable){
		print(getTimeStamp());
		print(" [ERROR] ");
		print(p);
		print("\n");
	}
}

void Log::error( const LoggerInterface& p ){
	if(blogEnable && blogErrorEnable){
		print(getTimeStamp());
		print(" [ERROR] ");
		print(p.toString());
		print("\n");
	}
}

	
void Log::debug( const string& p ){
	if(blogEnable && blogDebugEnable){
		print(getTimeStamp());
		print(" [DEBUG] ");
		print(p);
		print("\n");
	}
}

	
void Log::debug( const LoggerInterface& p ){
	if(blogEnable && blogDebugEnable){
		print(getTimeStamp());
		print(" [DEBUG] ");
		print(p.toString());
		print("\n");
	}
}

string Log::getTimeStamp(){
	steady_clock::time_point t1 = steady_clock::now();
	steady_clock::duration dtn = t1.time_since_epoch();
	time_t pSekundy = dtn.count() * steady_clock::period::num / steady_clock::period::den;
	struct tm timeinfo;
	localtime_s(&timeinfo,&pSekundy);
	short unsigned int pMilisekundy = static_cast<long long>( dtn.count() * ( static_cast<long double>(steady_clock::period::num) / static_cast<long double>(steady_clock::period::den) ) * 1000 ) % 1000;
	char s[20];
	strftime(s,20,"%Y-%m-%d %H:%M:%S",&timeinfo);
	stringstream str;
	str << s << "." << setw (3) << setfill ('0') << pMilisekundy;
	return str.str();
}