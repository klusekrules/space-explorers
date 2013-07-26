#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class StatekTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(StatekTest);
		DODAJ_TEST(Issue42Test);
		DODAJ_TEST(Issue52Test);
		DODAJ_TEST(FlotaTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void Issue42Test();
	void Issue52Test();
	void FlotaTest();
	StatekTest(void);
	virtual ~StatekTest(void);
private:
	const Statek* a;
	const Statek* b;
	const Statek* c;
	const Statek* d;
	shared_ptr<Planeta> planeta;
};

