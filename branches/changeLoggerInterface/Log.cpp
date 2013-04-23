#include "Log.h"
#include <fstream>
bool Log::blogEnable = true;
bool Log::blogDebugEnable = true;
bool Log::blogInfoEnable = true;
bool Log::blogWarnEnable = true;
bool Log::blogErrorEnable = true;

void Log::print( const string& p ){
	static fstream file("file.log",ios_base::app);
	cout << p;
	file << p;
}