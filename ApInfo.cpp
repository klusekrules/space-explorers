#include "Aplikacja.h"
#include "version.h"

namespace SpEx{
	void Aplikacja::logApInfo() const{
#ifndef LOG_OFF_ALL
		logger_.loguj(SLog::Log::Info, VER_PRODUCTNAME_STR);
		logger_.loguj(SLog::Log::Info, VER_FILE_DESCRIPTION_STR);
		logger_.loguj(SLog::Log::Info, VER_COPYRIGHT_STR);
		logger_.loguj(SLog::Log::Info, VER_COMPANY_NAME_STR);
#endif
	}
}
