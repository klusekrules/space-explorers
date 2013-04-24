#include "Aplikacja.h"
#include "version.h"

void Aplikacja::LogApInfo(){
	Log::getInstance().info(VER_PRODUCTNAME_STR);
	Log::getInstance().info(VER_FILE_DESCRIPTION_STR);
	Log::getInstance().info(VER_COPYRIGHT_STR);
	Log::getInstance().info(VER_COMPANY_NAME_STR);
}