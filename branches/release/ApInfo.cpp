#include "Aplikacja.h"
#include "version.h"

void Aplikacja::LogApInfo(){
	log.info(VER_PRODUCTNAME_STR);
	log.info(VER_FILE_DESCRIPTION_STR);
	log.info(VER_COPYRIGHT_STR);
	log.info(VER_COMPANY_NAME_STR);
}