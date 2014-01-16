#include "PlanetaTest.h"


PlanetaTest::PlanetaTest(void)
{
}

void PlanetaTest::tworzenieNiezaleznejPlanety(){
	shared_ptr<Planeta> planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(Identyfikator(0x5));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(1),Poziom(1)),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(2),Poziom(1)),Ilosc(600)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(3),Poziom(1)),Ilosc(700)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(4),Poziom(1)),Ilosc(800)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(5),Poziom(1)),Ilosc(900)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(6),Poziom(1)),Ilosc(400)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(7),Poziom(1)),Ilosc(300)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(8),Poziom(1)),Ilosc(200)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(9),Poziom(1)),Ilosc(100)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(10),Poziom(1)),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(11),Poziom(1)),Ilosc(100000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(12),Poziom(1)),Ilosc(40000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(13),Poziom(4)),Ilosc(2500)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(14),Poziom(2)),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(15),Poziom(0)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(15),Poziom(1)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(15),Poziom(2)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(15),Poziom(3)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(15),Poziom(4)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(15),Poziom(5)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(16),Poziom(0)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(16),Poziom(1)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(16),Poziom(2)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(16),Poziom(3)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(17),Poziom(0)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(17),Poziom(1)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(18),Poziom(0)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(18),Poziom(1)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(18),Poziom(2)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(18),Poziom(3)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(18),Poziom(4)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(18),Poziom(5)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(18),Poziom(6)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(18),Poziom(7)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(19),Poziom(0)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(19),Poziom(1)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(19),Poziom(2)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(19),Poziom(3)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(19),Poziom(4)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(19),Poziom(5)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(19),Poziom(6)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(20),Poziom(1)),Ilosc(5000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(21),Poziom(1)),Ilosc(6000)));
}

PlanetaTest::~PlanetaTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(PlanetaTest);
