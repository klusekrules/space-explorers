#include "LuaSkrypt.h"
#include "Logger\Log.h"

LuaSkrypt::LuaSkrypt( const std::string& plik )
	: plik_(plik), L(luaL_newstate())
{
	luaJIT_setmode(L, 0, LUAJIT_MODE_ENGINE|LUAJIT_MODE_ON);
	luaL_openlibs(L);
	odczytaj();
}

bool LuaSkrypt::zaladuj( const std::string& plik ){
	plik_=plik;
	return odczytaj();
}

bool LuaSkrypt::wykonaj( const std::string& funkcja ){
	if( !funkcja.empty() ){
		lua_getglobal(L, funkcja.c_str());
	}
	int status = lua_pcall(L, 0, LUA_MULTRET, 0);
	if (status) {
		std::stringstream ss;
		ss << "Nie udalo sie wywolac skryptu:" << lua_tostring(L, -1) << std::endl;
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, ss.str());
		return false;
	}
	return true;
}

bool LuaSkrypt::odczytaj(){
	if( !plik_.empty() ){
		int status = luaL_loadfile(L, plik_.c_str());
		if (status) {
			std::stringstream ss;
			ss << "Nie udalo sie wczytac pliku:" << lua_tostring(L, -1) << std::endl;
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, ss.str());
			return false;
		}
		return true;
	}
	return false;
}

LuaSkrypt::~LuaSkrypt(void){
	lua_close(L);
}
