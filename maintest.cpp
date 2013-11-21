#include "Main.h"
#include "Biblioteki.h"
#include "Aplikacja.h"
#include <SFML/Graphics.hpp>
#include "MaszynaStanow.h"
#include "lua.hpp"

#ifdef TESTS
#include "TestyJednostkowe.h"
#include <atomic>

std::atomic<bool> atom = true;

extern "C"{ 
	__declspec(dllexport) int __cdecl barfunc(int foo)
	{
		return foo + 1;
	}

	__declspec(dllexport) void __cdecl loguj(const char *komunikat )
	{
		if(komunikat)
			Log::pobierzInstancje().loguj(Log::Info, komunikat);
	}
}

void run(){
	while(atom){
		std::this_thread::yield();
	}
	ExitThread(0);
}

void main( int argv , char* argc[] ){

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
		
	Aplikacja::iloscArgumentow = argv;
	Aplikacja::argumenty = argc;
	Aplikacja::pobierzInstancje();

	std::thread t(run);
	std::thread d(run);
	atom = false;
	t.join();
	d.join();

	int status, result;
    lua_State *L = luaL_newstate();
	//luaJIT_setmode(L,0,LUAJIT_MODE_TRACE|LUAJIT_MODE_ENGINE);
    luaL_openlibs(L);

    /* Load the file containing the script we are going to run */
    status = luaL_loadfile(L, "resource\\test.lua");
    if (status) {
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        exit(1);
    }

	result = lua_pcall(L, 0, LUA_MULTRET, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

	lua_getglobal(L, "f");

    /* Ask Lua to run our little script */
    result = lua_pcall(L, 0, LUA_MULTRET, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    lua_close(L);   /* Cya, Lua */


	MaszynaStanow::pobierzInstancje().start();

}

#endif