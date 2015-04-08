#include "PlanetaTest.h"
#include "Model\Planeta.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Gra.h"

void PlanetaTest::tworzenieNiezaleznejPlanety(){
	std::shared_ptr<SpEx::Planeta> planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x5));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->odepnijPlanete();
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(1), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(2), STyp::Ilosc(600)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(3), STyp::Ilosc(700)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(4), STyp::Ilosc(800)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(5), STyp::Ilosc(900)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(6), STyp::Ilosc(400)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(7), STyp::Ilosc(300)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(8), STyp::Ilosc(200)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(9), STyp::Poziom(3)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(10), STyp::Poziom(3)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(11), STyp::Poziom(2)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(12), STyp::Poziom(2)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(13), STyp::Poziom(2)));
}

REJESTRUJ_PACZKE_TESTOW(PlanetaTest);
