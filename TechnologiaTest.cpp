#include "TechnologiaTest.h"


TechnologiaTest::TechnologiaTest(void)
{
}

void TechnologiaTest::startTestow(){
	planeta = Aplikacja::getInstance().getGra().stworzPlanete();
	UNIT_TEST_ASSERT_TRUE(Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(15),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(16),Ilosc(20)) );
	a = &(planeta->pobierzTechnologie(Identyfikator(15)));
	b = &(planeta->pobierzTechnologie(Identyfikator(16)));
}

void TechnologiaTest::podstawowyTest(){
	UNIT_TEST_ASSERT_EQUAL(Ilosc(1),a->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(Ilosc(1),b->pobierzIlosc());
}

TechnologiaTest::~TechnologiaTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(TechnologiaTest);
