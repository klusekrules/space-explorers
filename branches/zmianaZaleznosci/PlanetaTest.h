#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class PlanetaTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(PlanetaTest);
		DODAJ_TEST(tworzenieNiezaleznejPlanety);
	TWORZ_PACZKE_TESTOW_END();
public:
	void tworzenieNiezaleznejPlanety();
	PlanetaTest(void);
	virtual ~PlanetaTest(void);
};

