#include "MaszynaStanow.h"
#include "TestyJednostkowe.h"
#include "Aplikacja.h"
#include "LuaSkrypt.h"

extern "C"{ 
	__declspec(dllexport) int __cdecl barfunc(int foo)
	{
		return foo + 1;
	}

	__declspec(dllexport) bool __cdecl ustawOkno(int id)
	{
		return SpEx::MaszynaStanow::pobierzInstancje().kolejkujOkno(id);
	}

	__declspec(dllexport) bool __cdecl pobierzZdarzenie( struct Zdarzenie_t& z )
	{
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzZdarzenie(z);
	}

	__declspec(dllexport) bool __cdecl pobierzPoprzedniStan( struct Stan_t& s )
	{
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzPoprzedniStan(s);
	}

	__declspec(dllexport) bool __cdecl pobierzAktualnyStan( struct Stan_t& s )
	{
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzAktualnyStan(s);
	}

	__declspec(dllexport) bool __cdecl pobierzNastepnyStan( struct Stan_t& s )
	{
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzNastepnyStan(s);
	}

	__declspec(dllexport) void __cdecl kolejkujZdarzenie( struct Zdarzenie_t& s )
	{
		SpEx::Zdarzenie z;
		z.idStanu_( s.idStanu_);
		z.numer_ = s.numer_;
		z.idZdarzenia_( s.idZdarzenia_ );
		SpEx::MaszynaStanow::pobierzInstancje().kolejkujZdarzenie(z);
	}

	__declspec(dllexport) void __cdecl wstawZdarzenie( struct Zdarzenie_t& s )
	{
		SpEx::Zdarzenie z;
		z.idStanu_( s.idStanu_);
		z.numer_ = s.numer_;
		z.idZdarzenia_( s.idZdarzenia_ );
		SpEx::MaszynaStanow::pobierzInstancje().wstawZdarzenie(z);
	}

	__declspec(dllexport) void __cdecl wyczyscListeOkien()
	{
		SpEx::MaszynaStanow::pobierzInstancje().wyczyscKolejkeOkien();
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

		SpEx::MaszynaStanow::pobierzInstancje().dodajZadanie(SpEx::Zadanie(std::function<void()>(
		[luaPlik, luaFunkcja](){ 
			std::shared_ptr<SpEx::Skrypt> luaSkrypt = SpEx::Aplikacja::pobierzInstancje().pobierzZarzadce().TworzSkrypt(
				SpEx::FabrykaSkryptow::Identyfikator(XML_ATRYBUT_TYP_SKRYPT_LUA), nullptr);
			if (luaSkrypt){
				luaSkrypt->zaladuj(luaPlik);
				luaSkrypt->wykonaj();
				luaSkrypt->wykonaj(luaFunkcja);
			}
		}
			) ));
	}

	__declspec(dllexport) void __cdecl zamknijAplikacje()
	{
		SpEx::MaszynaStanow::pobierzInstancje().inicjujZamykanie();
	}

	__declspec(dllexport) void __cdecl loguj(const char *komunikat )
	{
		if(komunikat)
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, komunikat);
	}
}

