#include "PlanetaTest.h"

void PlanetaTest::tworzenieNiezaleznejPlanety(){
	std::shared_ptr<SpEx::Planeta> planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x5));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(1), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(2), STyp::Ilosc(600)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(3), STyp::Ilosc(700)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(4), STyp::Ilosc(800)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(5), STyp::Ilosc(900)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(6), STyp::Ilosc(400)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(7), STyp::Ilosc(300)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(8), STyp::Ilosc(200)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(9), STyp::Ilosc(100)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(10), STyp::Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(11), STyp::Ilosc(100000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(12), STyp::Ilosc(40000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(13), STyp::Ilosc(2500)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(14), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(15), STyp::Poziom(0)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(15), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(15), STyp::Poziom(2)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(15), STyp::Poziom(3)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(15), STyp::Poziom(4)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(15), STyp::Poziom(5)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(16), STyp::Poziom(0)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(16), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(16), STyp::Poziom(2)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(16), STyp::Poziom(3)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(17), STyp::Poziom(0)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(17), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(18), STyp::Poziom(0)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(18), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(18), STyp::Poziom(2)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(18), STyp::Poziom(3)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(18), STyp::Poziom(4)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(18), STyp::Poziom(5)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(18), STyp::Poziom(6)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(18), STyp::Poziom(7)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(19), STyp::Poziom(0)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(19), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(19), STyp::Poziom(2)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(19), STyp::Poziom(3)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(19), STyp::Poziom(4)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(19), STyp::Poziom(5)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(19), STyp::Poziom(6)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(20), STyp::Ilosc(5000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(21), STyp::Ilosc(6000)));
}

//REJESTRUJ_PACZKE_TESTOW(PlanetaTest);
