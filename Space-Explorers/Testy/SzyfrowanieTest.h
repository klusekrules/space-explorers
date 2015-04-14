#pragma once
#include "Szkielet\TestyJednostkowe.h"
#include "Kontroler\Aplikacja.h"

class SzyfrowanieTest :
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(SzyfrowanieTest);
		DODAJ_TEST(szyfrowanieTest);
		DODAJ_TEST(kompresjaTest);
		DODAJ_TEST(kompresjaOrazSzyfrowanieTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	SzyfrowanieTest() = default;
	void szyfrowanieTest();
	void kompresjaTest();
	void kompresjaOrazSzyfrowanieTest();
	virtual ~SzyfrowanieTest() = default;
};

