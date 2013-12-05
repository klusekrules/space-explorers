#include "MaszynaStanow.h"
#include "TestyJednostkowe.h"

extern "C"{ 
	__declspec(dllexport) int __cdecl barfunc(int foo)
	{
		return foo + 1;
	}

	__declspec(dllexport) bool __cdecl ustawOkno(int id)
	{
		return MaszynaStanow::pobierzInstancje().kolejkujOkno(id);
	}

	__declspec(dllexport) struct Zdarzenie_t __cdecl pobierzZdarzenie(  )
	{
		struct Zdarzenie_t t;
		t.idStanu_ = 1;
		t.numer_ = 2;
		t.idZdarzenia_ = 3;
		return t;
	}

	__declspec(dllexport) void __cdecl wyczyscListeOkien()
	{
		MaszynaStanow::pobierzInstancje().wyczyscKolejkeOkien();
	}

	__declspec(dllexport) void __cdecl testyJednostkowe()
	{
		TestyJednostkowe::pobierzInstancje().wykonajTesty();
	}

	__declspec(dllexport) void __cdecl zamknijAplikacje()
	{
		MaszynaStanow::pobierzInstancje().inicjujZamykanie();
	}

	__declspec(dllexport) void __cdecl loguj(const char *komunikat )
	{
		if(komunikat)
			Log::pobierzInstancje().loguj(Log::Info, komunikat);
	}
}

