#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class TechnologiaTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(TechnologiaTest);
		DODAJ_TEST(podstawowyTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void podstawowyTest();
	TechnologiaTest(void);
	virtual ~TechnologiaTest(void);
private:
	const Technologia* a;
	const Technologia* b;
	shared_ptr<Planeta> planeta;
};

