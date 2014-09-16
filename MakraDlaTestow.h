#pragma once

#define NAPIS(s) #s

#define GENERUJ_NAPIS(s) NAPIS(s)

#define MIEJSCE_WYJATKU std::string(__FILE__) , int(__LINE__)

#define REJESTRUJ_PACZKE_TESTOW( paczka ) paczka::Rejestrator paczka::rejestrator( TestyJednostkowe::Rejestracja::Ogolna )

#define REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA( paczka ) paczka::Rejestrator paczka::rejestrator( TestyJednostkowe::Rejestracja::Inicjalizacja )

#define REJESTRUJ_PACZKE_TESTOW_JAKO_CZYSZCZENIE( paczka ) paczka::Rejestrator paczka::rejestrator( TestyJednostkowe::Rejestracja::Czyszczenie )

#define TWORZ_PACZKE_TESTOW( paczka ) \
class Rejestrator{ \
public: \
	typedef paczka RodzicRejestratora;\
	Rejestrator( TestyJednostkowe::Rejestracja typ ){ \
		RodzicRejestratora* wskaznik = new RodzicRejestratora(); \
		wskaznik->ustawNazwe( #paczka )

#define TWORZ_PACZKE_TESTOW_END( ) \
	if(typ == TestyJednostkowe::Rejestracja::Ogolna ) \
		TestyJednostkowe::pobierzInstancje().dodajPaczke(wskaznik); \
	if(typ == TestyJednostkowe::Rejestracja::Inicjalizacja ) \
		TestyJednostkowe::pobierzInstancje().inicjalizacjaDanych(wskaznik); \
	if(typ == TestyJednostkowe::Rejestracja::Czyszczenie ) \
		TestyJednostkowe::pobierzInstancje().czyszczenieDanych(wskaznik); \
	} \
}; \
private: \
static Rejestrator rejestrator

#define DODAJ_TEST( test ) wskaznik->dodajTest(#test,std::bind(&RodzicRejestratora::test, wskaznik))

#define UNIT_TEST_ASSERT_EQUAL(oczekiwane , otrzymane) \
	if( oczekiwane != otrzymane ) \
		throw WyjatekSprawdzeniaWarunku(MIEJSCE_WYJATKU,GENERUJ_NAPIS(oczekiwane),GENERUJ_NAPIS(otrzymane))

#define UNIT_TEST_ASSERT_NOTEQUAL( oczekiwane , otrzymane ) \
	if( oczekiwane == otrzymane ) \
		throw WyjatekSprawdzeniaWarunku(MIEJSCE_WYJATKU,GENERUJ_NAPIS(oczekiwane),GENERUJ_NAPIS(otrzymane))

#define UNIT_TEST_ASSERT_NULL( otrzymane ) \
	if( nullptr != otrzymane ) \
		throw WyjatekSprawdzeniaWarunku(MIEJSCE_WYJATKU,"nullptr",GENERUJ_NAPIS(otrzymane))

#define UNIT_TEST_ASSERT_NOTNULL( otrzymane ) \
	if( nullptr == otrzymane ) \
		throw WyjatekSprawdzeniaWarunku(MIEJSCE_WYJATKU,"not nullptr",GENERUJ_NAPIS(otrzymane))

#define UNIT_TEST_ASSERT_TRUE( otrzymane ) \
	if( !otrzymane ) \
		throw WyjatekSprawdzeniaWarunku(MIEJSCE_WYJATKU,"true",GENERUJ_NAPIS(otrzymane))

#define UNIT_TEST_ASSERT_FALSE( otrzymane ) \
	if( otrzymane ) \
		throw WyjatekSprawdzeniaWarunku(MIEJSCE_WYJATKU,"false",GENERUJ_NAPIS(otrzymane))

#define UNIT_TEST_ASSERT_THROW( otrzymane , typ) \
	{ \
	bool r = true; \
	try{ \
		otrzymane; \
	} \
	catch(typ){ \
		r = false; \
	} \
	if(r) \
		throw WyjatekSprawdzeniaWarunku(MIEJSCE_WYJATKU,"false",GENERUJ_NAPIS(otrzymane)); \
	}


