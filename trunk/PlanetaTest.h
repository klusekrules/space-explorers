#pragma once
#include "TestyJednostkowe.h"

class PlanetaTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(PlanetaTest);
		DODAJ_TEST(tworzenieNiezaleznejPlanety);
	TWORZ_PACZKE_TESTOW_END();
public:
	void tworzenieNiezaleznejPlanety();
	PlanetaTest(void) = default;
	virtual ~PlanetaTest(void) = default;
};

