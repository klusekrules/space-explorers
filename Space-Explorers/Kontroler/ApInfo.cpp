#include "Aplikacja.h"
#include "Resource\resource.h"

namespace SpEx{
	void Aplikacja::logApInfo() const{
#ifndef LOG_OFF_ALL
		logger_.loguj(SLog::Log::Info, "Start aplikacji Space-Explorers.");

		logger_.loguj(SLog::Log::Info, VER_PRODUCTNAME_STR);
		logger_.loguj(SLog::Log::Info, VER_FILE_DESCRIPTION_STR);
		logger_.loguj(SLog::Log::Info, VER_COPYRIGHT_STR);
		logger_.loguj(SLog::Log::Info, VER_COMPANY_NAME_STR);

		if (uchwyt_){
			if (czyZainicjalizowanaBiblioteka_){
				logger_.loguj(SLog::Log::Info, "Za³adowano biblioteke Dbghelp.dll");
			} else{
				logger_.loguj(SLog::Log::Warning, "Nie zanaleziono funkcji SymInitialize i/lub SymFromAddr.");
			}
		} else{
			logger_.loguj(SLog::Log::Warning, "Nie za³adowano biblioteki Dbghelp.dll");
		}
#endif
	}
}
