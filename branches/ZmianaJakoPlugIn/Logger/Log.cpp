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
	:blogEnable(true), blogDebugEnable(true), blogInfoEnable(true), blogWarnEnable(true), blogErrorEnable(true),formatCzasu("%Y-%m-%d %H:%M:%S")
{

	//Ladowanie potrzebnych bibliotek
	hLibrary = LoadLibrary("Dbghelp.dll");
	if(hLibrary){
		Log::getInstance().info("Za³adowano biblioteke Dbghelp.dll");
		symInitialize = (SymInitializeS)GetProcAddress(hLibrary,"SymInitialize");
		symFromAddr = (SymFromAddrS)GetProcAddress(hLibrary,"SymFromAddr");
		if(symFromAddr && symInitialize){
			isDbgHelpInit = true;
		}else{
			Log::getInstance().warn("Nie zanaleziono funkcji SymInitialize i/lub SymFromAddr.");
		}
	}else{
		Log::getInstance().warn("Nie za³adowano biblioteki Dbghelp.dll");
	}
}

string Log::getStackTrace() const{
	stringstream stackTrace;	
	if( isDbgHelpInit )
	{
		void *stack[150];
		unsigned short frames;
		SYMBOL_INFO *symbol;
		HANDLE hProcess;
		locale l("C");
		stackTrace.imbue(l);
		hProcess = GetCurrentProcess ();
		symInitialize (hProcess, nullptr, true );
		frames = CaptureStackBackTrace( 0, 150, stack, nullptr );
		symbol = (SYMBOL_INFO *) calloc (sizeof (SYMBOL_INFO) + 256 * sizeof (char), 1);
		symbol->MaxNameLen = 255;
		symbol->SizeOfStruct = sizeof (SYMBOL_INFO);
		if(frames>0){

			time_t rawtime;
			char buf [30];
			time(&rawtime);
			ctime_s(buf,30,&rawtime);
			stackTrace << buf;
			// i = 1 - Pominiêcie wywo³ania funkcji getStackTrace
			// i = 0 - W³¹cznie do wyœwietlanego wyniku wywo³ania funkcji getStackTrace
			for (unsigned int i = 1 ;i < frames; i++)
			{
				symFromAddr (hProcess, (DWORD_PTR) (stack[i]), 0, symbol);
				stackTrace << dec << (unsigned short)(frames - i - 1) << ": 0x" << setfill('0')<<setw(8)<<stack[i] << " " << (char*)(symbol->Name) << " = 0x" << setfill('0')<<setw(8) << hex <<symbol->Address << endl;
				//fprintf_s (fp,"%u: %p %s = 0x%Ix\n", frames - i - 1, stack[i], symbol->Name, symbol->Address);
			}
		}
		free (symbol);
	}
	return stackTrace.str();
}



void Log::ustawFormatCzasu( FormatCzasu format ){
	switch (format)
	{
	case Log::Data: formatCzasu="%Y-%m-%d";
		break;
	case Log::Czas: formatCzasu="%H:%M:%S";
		break;
	case Log::DataCzas: formatCzasu="%Y-%m-%d %H:%M:%S";
		break;
	default:
		break;
	}
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

string Log::getTimeStamp() const{
	steady_clock::time_point t1 = steady_clock::now();
	steady_clock::duration dtn = t1.time_since_epoch();
	time_t pSekundy = dtn.count() * steady_clock::period::num / steady_clock::period::den;
	struct tm timeinfo;
	localtime_s(&timeinfo,&pSekundy);
	short unsigned int pMilisekundy = static_cast<long long>( dtn.count() * ( static_cast<long double>(steady_clock::period::num) / static_cast<long double>(steady_clock::period::den) ) * 1000 ) % 1000;
	char s[20];
	strftime(s,20,formatCzasu.c_str(),&timeinfo);
	stringstream str;
	str << s << "." << setw (3) << setfill ('0') << pMilisekundy;
	return str.str();
}