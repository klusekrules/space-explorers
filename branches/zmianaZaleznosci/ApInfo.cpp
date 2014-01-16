#include "Aplikacja.h"
#include "version.h"

void Aplikacja::logApInfo() const{
	logger_.loguj(Log::Info,VER_PRODUCTNAME_STR);
	logger_.loguj(Log::Info,VER_FILE_DESCRIPTION_STR);
	logger_.loguj(Log::Info,VER_COPYRIGHT_STR);
	logger_.loguj(Log::Info,VER_COMPANY_NAME_STR);
}
