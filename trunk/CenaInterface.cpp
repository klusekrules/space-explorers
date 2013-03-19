#include "CenaInterfejs.h"
#include "Logger.h"

CenaInterfejs::~CenaInterfejs(){
}

string CenaInterfejs::toString()const{
	Logger str(LogCenaInterface::className());
	return str.toString();
}