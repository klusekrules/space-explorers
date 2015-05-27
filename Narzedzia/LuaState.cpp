#include "LuaState.h"
#include "Logger\Log.h"

namespace SpEx{

	const std::string LuaState::NazwaTypu_ = "lua";

	LuaState::LuaState(const std::string& plik)
		: Zasob(plik), L(luaL_newstate())
	{
		luaJIT_setmode(L, 0, LUAJIT_MODE_ENGINE | LUAJIT_MODE_ON);
		luaL_openlibs(L);
	}
	
	LuaState::~LuaState(){
		lua_close(L);
	}

	bool LuaState::inicjalizuj(){
		if (!pobierzAdresPliku().empty()){
			int status = luaL_loadfile(L, pobierzAdresPliku().c_str());
			if (status) {
				std::stringstream ss;
				ss << "Nie udalo sie wczytac pliku:" << lua_tostring(L, -1) << std::endl;
#ifndef LOG_OFF_ALL
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, ss.str());
#endif
				return false;
			}
			status = lua_pcall(L, 0, LUA_MULTRET, 0);
			if (status) {
				std::stringstream ss;
				ss << "Nie udalo sie zaladowac skryptu:" << lua_tostring(L, -1) << std::endl;
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
