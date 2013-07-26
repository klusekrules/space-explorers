#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class TworzenieObiektowTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(TworzenieObiektowTest);
		DODAJ_TEST(tworzenieObiektow);
		DODAJ_TEST(falszyweObiekty);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;

	void tworzenieObiektow();
	void falszyweObiekty();

	TworzenieObiektowTest();
	virtual ~TworzenieObiektowTest();
private:
	Gra *gra;
	Identyfikator id;
	shared_ptr<Planeta> planeta;
};

