#include "TechnologiaTest.h"


TechnologiaTest::TechnologiaTest(void)
{
}

void TechnologiaTest::startTestow(){
	planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(Identyfikator(0x3));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(15),Poziom(1)),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(16),Poziom(1)),Ilosc(20)) );
	a = &(planeta->pobierzTechnologie(Planeta::Indeks(Identyfikator(15),Poziom(1))));
	b = &(planeta->pobierzTechnologie(Planeta::Indeks(Identyfikator(16),Poziom(1))));
}

void TechnologiaTest::podstawowyTest(){
	UNIT_TEST_ASSERT_EQUAL(Ilosc(1),a->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(Ilosc(1),b->pobierzIlosc());
}

TechnologiaTest::~TechnologiaTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(TechnologiaTest);
