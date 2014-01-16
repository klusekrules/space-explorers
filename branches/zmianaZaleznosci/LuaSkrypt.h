#pragma once
#include <string>
#include "lua.hpp"

class LuaSkrypt
{
public:
	LuaSkrypt( const std::string& = std::string() );
	bool zaladuj( const std::string& );
	bool wykonaj( const std::string& = std::string() );
	~LuaSkrypt(void);
private:
	bool odczytaj();
	std::string plik_;
	lua_State *L;
};

