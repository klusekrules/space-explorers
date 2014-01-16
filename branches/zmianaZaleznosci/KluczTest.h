#pragma once
#include "TestyJednostkowe.h"

class KluczTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(KluczTest);
		DODAJ_TEST(klucz);
	TWORZ_PACZKE_TESTOW_END();
public:
	void klucz();
	KluczTest(void);
	virtual ~KluczTest(void);
};

