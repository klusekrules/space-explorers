#include "LuaSkrypt.h"
#include "Logger\Log.h"
#include "definicjeWezlowXML.h"
#include "Aplikacja.h"
#include "BladStukturyStanu.h"

#define KOMUNIAKT_BLAD_WYKONYWANIA STyp::Tekst("Dla zdarzenia o ww id nie uda³o siê wykonaæ inicjalizacji skryptu.")

namespace SpEx{
	LuaSkrypt::LuaSkrypt(LuaState::SharedPtr ptr)
		: L(ptr)
	{}
	
	bool LuaSkrypt::wykonaj(const std::string& funkcja){
		if (!funkcja.empty()){
			lua_getglobal((*L)(), funkcja.c_str());
		}
		int status = lua_pcall((*L)(), 0, LUA_MULTRET, 0);
		if (status) {
			std::stringstream ss;
			ss << "Nie udalo sie wywolac skryptu:" << lua_tostring((*L)(), -1) << std::endl;
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, ss.str());
			return false;
		}
		return true;
	}

	bool LuaSkrypt::Rejestruj(Fabrykator &fabryka){
		return fabryka.rejestracjaSkryptu(Fabrykator::IdentyfikatorSkryptu(XML_ATRYBUT_TYP_SKRYPT_LUA), LuaSkrypt::Tworz);
	}

	std::shared_ptr<Skrypt> LuaSkrypt::Tworz(XmlBO::ElementWezla wezel){
		std::string luaFile = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_SKRYPT_FILE, std::string());
		if (luaFile.empty())
			return nullptr;

		std::string instancja = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_SKRYPT_INSTANCE, std::string());
		if (!instancja.empty()){
			STyp::Identyfikator id;
			std::string temp(XML_ATRYBUT_TYP_SKRYPT_LUA);
			temp.push_back('_');
			temp += instancja;
			SpEx::Aplikacja::pobierzInstancje().zarzadcaZasobow_.mapujIdentyfikator(temp, id);
			LuaState::SharedPtr uchwyt = SpEx::Aplikacja::pobierzInstancje().zarzadcaZasobow_.pobierzZasob<LuaState>(id, luaFile, !instancja.empty());
			if (uchwyt == nullptr)
				return nullptr;
			return std::make_shared<LuaSkrypt>(uchwyt);
		}else{
			LuaState::SharedPtr uchwyt = SpEx::Aplikacja::pobierzInstancje().zarzadcaZasobow_.pobierzUnikalnyZasob<LuaState>(luaFile);
			if (uchwyt == nullptr)
				return nullptr;
			return std::make_shared<LuaSkrypt>(uchwyt);
		}
	}
};
