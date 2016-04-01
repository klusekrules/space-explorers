#include "Aplikacja.h"
#include "Resource\resource.h"

namespace SpEx{
	void Aplikacja::logApInfo() const{
#ifndef LOG_OFF_ALL
		logger_.loguj(SLog::Log::Info, "Start aplikacji Space-Explorers.");

		logger_.loguj(SLog::Log::Info, VER_PRODUCTNAME_STR);
		logger_.loguj(SLog::Log::Info, VER_FILE_COMMENTS_STR);
		logger_.loguj(SLog::Log::Info, VER_COPYRIGHT_STR);
		logger_.loguj(SLog::Log::Info, VER_COMPANY_NAME_STR);
#endif
	}
}
