#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class LadowniaTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(LadowniaTest);
		DODAJ_TEST(podstawowyTest);
		DODAJ_TEST(oproznianieLadowni);
		DODAJ_TEST(dodawanieStatkow);
		DODAJ_TEST(dzielenieLadowni);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void podstawowyTest();
	void oproznianieLadowni();
	void dodawanieStatkow();
	void dzielenieLadowni();
	LadowniaTest(void);
	virtual ~LadowniaTest(void);

private:
	Gra* gra;
	shared_ptr<Statek> statekTransportowy;
	shared_ptr<Statek> statekTransportowyDuzy;
	shared_ptr<Surowce> metal;
	shared_ptr<Surowce> energia;
	shared_ptr<Statek> mysliwiec;
};

