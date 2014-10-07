#include "TechnologiaTest.h"

void TechnologiaTest::startTestow(){
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x3));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->odepnijPlanete();
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(9), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(10), STyp::Poziom(2)));
	a = &(planeta->pobierzObiekt<SpEx::Technologia>(STyp::Identyfikator(9)));
	b = &(planeta->pobierzObiekt<SpEx::Technologia>(STyp::Identyfikator(10)));
}

void TechnologiaTest::podstawowyTest(){
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(1), a->pobierzPoziom());
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(2), b->pobierzPoziom());
}

REJESTRUJ_PACZKE_TESTOW(TechnologiaTest);
