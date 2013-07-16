#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class ZapisStanuGryTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(ZapisStanuGryTest);
		DODAJ_TEST(zapis);
		DODAJ_TEST(odczyt);
	TWORZ_PACZKE_TESTOW_END();
public:
	void zapis();
	void odczyt();
	ZapisStanuGryTest(void);
	virtual ~ZapisStanuGryTest(void);
private:
	Planeta p_a;
	int ptr_a;
};

