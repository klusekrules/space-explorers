#include "Aplikacja.h"
#include "version.h"

void Aplikacja::logApInfo() const{
	logger_.info(VER_PRODUCTNAME_STR);
	logger_.info(VER_FILE_DESCRIPTION_STR);
	logger_.info(VER_COPYRIGHT_STR);
	logger_.info(VER_COMPANY_NAME_STR);
}
