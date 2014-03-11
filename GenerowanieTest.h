#pragma once
#include "TestyJednostkowe.h"

class GenerowanieTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(GenerowanieTest);
		DODAJ_TEST(generuj);
	TWORZ_PACZKE_TESTOW_END();
public:
	void generuj();
	GenerowanieTest(void) = default;
	virtual ~GenerowanieTest(void) = default;
};

