#include "ZmianaInterfejs.h"
#include "Logger.h"

ZmianaInterfejs::ZmianaInterfejs(){
}

ZmianaInterfejs::~ZmianaInterfejs(){
}

string ZmianaInterfejs::toString() const{
	Logger str(LogZmianaInterfejs::className());
	return str.toString();
}