#pragma once
#include "MakraDlaTestow.h"
#include "PaczkaTestow.h"
#include "WyjatekSprawdzeniaWarunku.h"

class TestyJednostkowe
{
public:
	enum Rejestracja{
		Ogolna,
		Inicjalizacja,
		Czyszczenie
	};

	static TestyJednostkowe& pobierzInstancje();
	
	void inicjalizacjaDanych( PaczkaTestow* paczka );
	void czyszczenieDanych( PaczkaTestow* paczka );
	void dodajPaczke( PaczkaTestow* paczka );
	void wykonajTesty();

	~TestyJednostkowe();

private:

	vector< PaczkaTestow* > inicjalizacja_;
	vector< PaczkaTestow* > zbiorTestow_;
	vector< PaczkaTestow* > czyszczenie_;

	TestyJednostkowe();
	TestyJednostkowe( const TestyJednostkowe& obiekt );
	TestyJednostkowe& operator=( const TestyJednostkowe& obiekt );
};
