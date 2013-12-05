#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class CzyszczenieDanychTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(CzyszczenieDanychTest);
		DODAJ_TEST(czysc);
	TWORZ_PACZKE_TESTOW_END();
public:
	CzyszczenieDanychTest(void);
	void czysc();
	virtual ~CzyszczenieDanychTest(void);
};

