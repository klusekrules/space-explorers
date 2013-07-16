#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class BudynekTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(BudynekTest);
		DODAJ_TEST(podstawowyTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void podstawowyTest();
	BudynekTest(void);
	virtual ~BudynekTest(void);
private:
	const Budynek* a;
	const Budynek* b;
	const Budynek* c;
	Planeta* planeta;
};

