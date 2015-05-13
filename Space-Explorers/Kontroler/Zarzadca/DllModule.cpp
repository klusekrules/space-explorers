#include "DllModule.h"
#include "Logger\Log.h"

namespace SpEx{

	const std::string DllModule::NazwaTypu_ = "dll";

	DllModule::DllModule(const std::string& plik)
		: Zasob(plik), handle_(NULL)
	{
	}

	DllModule::~DllModule(){
		if (handle_)
			FreeLibrary(handle_);
	}

	bool DllModule::inicjalizuj(){
		if (!pobierzAdresPliku().empty()){
			handle_ = LoadLibrary(pobierzAdresPliku().c_str());
			if (!handle_) {
				std::stringstream ss;
				ss << "Nie udalo sie wczytac pliku: " << pobierzAdresPliku() << ". Error number: " << GetLastError() << std::endl;
#ifndef LOG_OFF_ALL
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, ss.str());
#endif
				return false;
			}
			return true;
		}
		return false;
	}
};
