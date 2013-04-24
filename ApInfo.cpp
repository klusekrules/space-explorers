#include "Aplikacja.h"
#include "version.h"

void Aplikacja::LogApInfo(){
	Log::info(VER_PRODUCTNAME_STR);
	Log::info(VER_FILE_DESCRIPTION_STR);
	Log::info(VER_COPYRIGHT_STR);
	Log::info(VER_COMPANY_NAME_STR);
}