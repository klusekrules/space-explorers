#pragma once
#include "TestyJednostkowe.h"

class LogowanieTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(LogowanieTest);
		DODAJ_TEST(zaloguj);
	TWORZ_PACZKE_TESTOW_END();
public:
	void zaloguj();
	LogowanieTest(void);
	virtual ~LogowanieTest(void);
};

