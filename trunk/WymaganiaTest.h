#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class WymaganiaTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(WymaganiaTest);
		DODAJ_TEST(sprawdzenieKosztow);
		DODAJ_TEST(czyMoznaWybudowacTest);
		DODAJ_TEST(czasBudowy);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void sprawdzenieKosztow();
	void czyMoznaWybudowacTest();
	void czasBudowy();
	WymaganiaTest(void);
	virtual ~WymaganiaTest(void);
private:
	const Statek* a;
	Planeta* planeta;
};

