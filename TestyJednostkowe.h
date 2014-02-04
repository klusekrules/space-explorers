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
	
	unsigned int bledy = 0;
	unsigned int bledyKrytyczne = 0;
	unsigned int pominieteTesty = 0;
	unsigned int poprawneTesty = 0;

	std::vector< PaczkaTestow* > inicjalizacja_;
	std::vector< PaczkaTestow* > zbiorTestow_;
	std::vector< PaczkaTestow* > czyszczenie_;

	void podsumowanie();

	TestyJednostkowe() = default;
	TestyJednostkowe( const TestyJednostkowe& obiekt ) = delete;
	TestyJednostkowe& operator=( const TestyJednostkowe& obiekt ) = delete;
};
