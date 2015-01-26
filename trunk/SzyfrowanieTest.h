#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class SzyfrowanieTest :
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(SzyfrowanieTest);
		DODAJ_TEST(szyfrowanieTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	SzyfrowanieTest() = default;
	void szyfrowanieTest();
	virtual ~SzyfrowanieTest() = default;
};

