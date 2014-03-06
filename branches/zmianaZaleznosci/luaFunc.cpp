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

	__declspec(dllexport) bool __cdecl pobierzZdarzenie( struct Zdarzenie_t& z )
	{
		return MaszynaStanow::pobierzInstancje().luaStan_.pobierzZdarzenie(z);
	}

	__declspec(dllexport) bool __cdecl pobierzPoprzedniStan( struct Stan_t& s )
	{
		return MaszynaStanow::pobierzInstancje().luaStan_.pobierzPoprzedniStan(s);
	}

	__declspec(dllexport) bool __cdecl pobierzAktualnyStan( struct Stan_t& s )
	{
		return MaszynaStanow::pobierzInstancje().luaStan_.pobierzAktualnyStan(s);
	}

	__declspec(dllexport) bool __cdecl pobierzNastepnyStan( struct Stan_t& s )
	{
		return MaszynaStanow::pobierzInstancje().luaStan_.pobierzNastepnyStan(s);
	}

	__declspec(dllexport) void __cdecl kolejkujZdarzenie( struct Zdarzenie_t& s )
	{
		Zdarzenie z;
		z.idStanu_( s.idStanu_);
		z.numer_ = s.numer_;
		z.idZdarzenia_( s.idZdarzenia_ );
		MaszynaStanow::pobierzInstancje().kolejkujZdarzenie(z);
	}

	__declspec(dllexport) void __cdecl wstawZdarzenie( struct Zdarzenie_t& s )
	{
		Zdarzenie z;
		z.idStanu_( s.idStanu_);
		z.numer_ = s.numer_;
		z.idZdarzenia_( s.idZdarzenia_ );
		MaszynaStanow::pobierzInstancje().wstawZdarzenie(z);
	}

	__declspec(dllexport) void __cdecl wyczyscListeOkien()
	{
		MaszynaStanow::pobierzInstancje().wyczyscKolejkeOkien();
	}

	__declspec(dllexport) void __cdecl testyJednostkowe()
	{
		TestyJednostkowe::pobierzInstancje().wykonajTesty();
	}

	
	__declspec(dllexport) void __cdecl zlecZadanie( const char *plik , const char *funkcja )
	{
		std::string luaPlik, luaFunkcja;

		if(plik){
			luaPlik.append(plik);
		}

		if(funkcja){
			luaFunkcja.append(funkcja);
		}

		MaszynaStanow::pobierzInstancje().dodajZadanie(Zadanie( std::function<void()>(
		[luaPlik, luaFunkcja](){ 
			LuaSkrypt luaSkrypt(luaPlik);
			luaSkrypt.wykonaj();
			luaSkrypt.wykonaj(luaFunkcja);
		}
			) ));
	}

	__declspec(dllexport) void __cdecl zamknijAplikacje()
	{
		MaszynaStanow::pobierzInstancje().inicjujZamykanie();
	}

	__declspec(dllexport) void __cdecl loguj(const char *komunikat )
	{
		if(komunikat)
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, komunikat);
	}
}

