#include "DllSkrypt.h"
#include "Logger\Log.h"
#include "Fabrykator.h"
#include "definicjeWezlowXML.h"
#include "Aplikacja.h"

namespace SpEx{
	DllSkrypt::DllSkrypt(DllModule::SharedPtr ptr)
		: modul_(ptr)
	{
	}

	bool DllSkrypt::wykonaj(const std::string& funkcja){
		if (!funkcja.empty()){
			auto procedura = GetProcAddress((*modul_)(), funkcja.c_str());
			if (procedura()) {
				std::stringstream ss;
				ss << "Nie udalo sie wywolac skryptu: " << funkcja << " z pliku :  " << modul_->pobierzPlik() << std::endl;
#ifndef LOG_OFF_ALL
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, ss.str());
#endif
				return false;
			}
			return true;
		}
		return false;
	}

	bool DllSkrypt::Rejestruj(Fabrykator &fabryka){
		return fabryka.rejestracjaSkryptu(Fabrykator::IdentyfikatorSkryptu(XML_ATRYBUT_TYP_SKRYPT_DLL), DllSkrypt::Tworz);
	}

	std::shared_ptr<Skrypt> DllSkrypt::Tworz(XmlBO::ElementWezla wezel){
		std::string dllFile = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_SKRYPT_FILE, std::string());
		if (dllFile.empty())
			return nullptr;
		DllModule::SharedPtr uchwyt = SpEx::Aplikacja::pobierzInstancje().zarzadcaZasobow_.pobierzZasob<DllModule>(dllFile, true);
		if (uchwyt == nullptr)
			return nullptr;
		return std::make_shared<DllSkrypt>(uchwyt);
	}
}