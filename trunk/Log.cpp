#include "Log.h"

bool Log::blogEnable = true;
bool Log::blogDebugEnable = true;
bool Log::blogInfoEnable = true;
bool Log::blogWarnEnable = true;
bool Log::blogErrorEnable = true;

void Log::print( const string p ){
	cout << p;
}