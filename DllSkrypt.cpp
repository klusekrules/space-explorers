#include "DllSkrypt.h"
#include "Logger\Log.h"
#include "Fabrykator.h"

namespace SpEx{
	DllSkrypt::DllSkrypt(const std::string& plik)
		: plik_(plik), handle_(nullptr)
	{
		odczytaj();
	}

	bool DllSkrypt::wykonaj(const std::string& funkcja){
		if (!funkcja.empty()){
			auto procedura = GetProcAddress(handle_, funkcja.c_str());
			if (procedura()) {
				std::stringstream ss;
				ss << "Nie udalo sie wywolac skryptu: " << funkcja << " z pliku :  " << plik_ << std::endl;
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, ss.str());
				return false;
			}
			return true;
		}
		return false;
	}

	bool DllSkrypt::odczytaj(){
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

	DllSkrypt::~DllSkrypt(void){
		if (handle_)
			FreeLibrary(handle_);
	}

	bool DllSkrypt::Rejestruj(Fabrykator &fabryka){
		return fabryka.rejestracjaSkryptu(Fabrykator::IdentyfikatorSkryptu(XML_ATRYBUT_TYP_SKRYPT_DLL), DllSkrypt::Tworz);
	}

	std::shared_ptr<Skrypt> DllSkrypt::Tworz(XmlBO::ElementWezla wezel){
		return std::make_shared<DllSkrypt>();
	}
}