#include "DllModule.h"
#include "Logger\Log.h"

namespace SpEx{

	const std::string DllModule::NazwaTypu_ = "dll";

	DllModule::DllModule(const std::string& plik)
		: plik_(plik), handle_(NULL)
	{
	}

	DllModule::~DllModule(){
		if (handle_)
			FreeLibrary(handle_);
	}

	bool DllModule::inicjalizuj(){
		if (!plik_.empty()){
			handle_ = LoadLibrary(plik_.c_str());
			if (!handle_) {
				std::stringstream ss;
				ss << "Nie udalo sie wczytac pliku: " << plik_ << std::endl;
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
