#include "DllModule.h"
#include "Logger\Log.h"

namespace SpEx{
	DllModule::DllModule(const std::string& plik)
		: plik_(plik), handle_(NULL)
	{
	}

	DllModule::~DllModule(){
		if (handle_)
			FreeLibrary(handle_);
	}

	Zasob::SharedPtr DllModule::Tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache){
		return std::make_shared<DllModule>(parametr);
	}

	bool DllModule::Rejestruj(ZarzadcaZasobow &fabryka){
		return fabryka.rejestrujInicjalizator(XML_ATRYBUT_TYP_ZASOBU_DLL, DllModule::Tworz);
	}

	bool DllModule::inicjalizuj(){
		if (!plik_.empty()){
			handle_ = LoadLibrary(plik_.c_str());
			if (!handle_) {
				std::stringstream ss;
				ss << "Nie udalo sie wczytac pliku: " << plik_ << std::endl;
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, ss.str());
				return false;
			}
			return true;
		}
		return false;
	}
};
