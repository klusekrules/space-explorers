#include "TechnologiaTest.h"

void TechnologiaTest::startTestow(){
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x3));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(15), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(16), STyp::Poziom(1)));
	a = &(planeta->pobierzTechnologie(STyp::Identyfikator(15)));
	b = &(planeta->pobierzTechnologie(STyp::Identyfikator(16)));
}

void TechnologiaTest::podstawowyTest(){
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(1), a->pobierzPoziom());
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(1), b->pobierzPoziom());
}

REJESTRUJ_PACZKE_TESTOW(TechnologiaTest);
