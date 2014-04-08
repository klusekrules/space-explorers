#pragma once
#include <Windows.h>
#include "Skrypt.h"
#include <memory>
#include "Parser\XmlBO.h"

#define XML_ATRYBUT_TYP_SKRYPT_DLL "dll"
namespace SpEx{
	class DllSkrypt
		: public Skrypt
	{
		friend class FabrykaSkryptow;
		friend class std::_Ref_count_obj<DllSkrypt>;
	public:
		static bool Rejestruj(FabrykaSkryptow &fabryka);
		bool zaladuj(const std::string&) override;
		bool wykonaj(const std::string& = std::string()) override;
		virtual ~DllSkrypt();
	private:
		static std::shared_ptr<Skrypt> Tworz(XmlBO::ElementWezla wezel);
		DllSkrypt(const std::string& = std::string());
		bool odczytaj();
		std::string plik_;
		HMODULE handle_;
	};
};
