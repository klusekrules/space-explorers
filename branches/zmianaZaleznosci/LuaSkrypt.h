#pragma once
#include "lua.hpp"
#include "Skrypt.h"
#include <memory>
#include "Parser\XmlBO.h"

#define XML_ATRYBUT_TYP_SKRYPT_LUA "lua"

namespace SpEx{
	class LuaSkrypt
		: public Skrypt
	{
		friend class FabrykaSkryptow;
		friend class std::_Ref_count_obj<LuaSkrypt>;
	public:
		static bool Rejestruj(FabrykaSkryptow &fabryka);
		bool zaladuj(const std::string&) override;
		bool wykonaj(const std::string& = std::string()) override;
		virtual ~LuaSkrypt();
	private:
		static std::shared_ptr<Skrypt> Tworz(XmlBO::ElementWezla wezel);
		LuaSkrypt(const std::string& = std::string());
		bool odczytaj();
		std::string plik_;
		lua_State *L;
	};
};
