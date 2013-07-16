#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class ObiektListTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(ObiektListTest);
		DODAJ_TEST(podstawowyTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void podstawowyTest();
	ObiektListTest(void);
	virtual ~ObiektListTest(void);
private:
	ObiektList<Statek> lista;
	ObiektList<Statek> listaDruga;
	
	Statek *a;
	Statek *b;
	Statek *c;
	Statek *d;
};

