#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class ZleceniaTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(ZleceniaTest);
		DODAJ_TEST(tranzakcja_poprawna);
		DODAJ_TEST(tranzakcja_cofnieta);
		DODAJ_TEST(tranzakcja_throw);
		DODAJ_TEST(tranzakcja_throw2);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;

	void tranzakcja_poprawna();
	void tranzakcja_cofnieta();
	void tranzakcja_throw();
	void tranzakcja_throw2();

	ZleceniaTest(void);
	virtual ~ZleceniaTest(void);
private:
	Gra *gra;
};
