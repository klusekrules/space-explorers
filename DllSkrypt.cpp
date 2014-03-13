#include "DllSkrypt.h"
#include "Logger\Log.h"
#include "FabrykaSkryptow.h"

namespace SpEx{
	DllSkrypt::DllSkrypt(const std::string& plik)
		: plik_(plik), handle_(nullptr)
	{
		odczytaj();
	}

	bool DllSkrypt::zaladuj(const std::string& plik){
		plik_ = plik;
		return odczytaj();
	}

	bool DllSkrypt::wykonaj(const std::string& funkcja){
		if (!funkcja.empty()){
			auto procedura = GetProcAddress(handle_, funkcja.c_str());
			int status = procedura();
			if (status) {
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

	bool DllSkrypt::Rejestruj(FabrykaSkryptow &fabryka){
		return fabryka.rejestracjaSkryptu(FabrykaSkryptow::Identyfikator(XML_ATRYBUT_TYP_SKRYPT_DLL), DllSkrypt::Tworz);
	}

	std::shared_ptr<Skrypt> DllSkrypt::Tworz(XmlBO::ElementWezla wezel){
		return std::make_shared<DllSkrypt>();
	}
}