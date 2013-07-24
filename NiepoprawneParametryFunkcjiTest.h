#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"
#include "NiepoprawneParametryFunkcji.h"

class NiepoprawneParametryFunkcjiTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(NiepoprawneParametryFunkcjiTest);
		DODAJ_TEST(tworzenieWyjatku);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void tworzenieWyjatku();
	NiepoprawneParametryFunkcjiTest(void);
	virtual ~NiepoprawneParametryFunkcjiTest(void);

private:
	Planeta * planeta;
};

