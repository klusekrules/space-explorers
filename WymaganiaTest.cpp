#include "WymaganiaTest.h"

void WymaganiaTest::startTestow(){
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x1));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE( SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(11), STyp::Ilosc(8)));
	a = &(planeta->pobierzStatek(STyp::Identyfikator(11)));
}

void WymaganiaTest::sprawdzenieKosztow(){
	auto w = a->pobierzKryteriaRozbudowy();
	UNIT_TEST_ASSERT_EQUAL(3,w.size());
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(480000.0), w[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(16000.0), w[1]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(8 * 2 * 10 * 5 * 200), w[2]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(50), w[0]->pobierzPoziom());
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(10), w[1]->pobierzPoziom());
}

void WymaganiaTest::czyMoznaWybudowacTest(){
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0xC), STyp::Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(1), STyp::Ilosc(60000)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(4), STyp::Ilosc(60000)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(7), STyp::Ilosc(60000)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x13), STyp::Poziom(0)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x10), STyp::Poziom(0)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x13), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x10), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x13), STyp::Poziom(2)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x10), STyp::Poziom(2)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x13), STyp::Poziom(3)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x10), STyp::Poziom(3)));
	UNIT_TEST_ASSERT_TRUE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x13), STyp::Poziom(4)));
	UNIT_TEST_ASSERT_TRUE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x10), STyp::Poziom(4)));
	UNIT_TEST_ASSERT_TRUE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x13), STyp::Poziom(5)));
	UNIT_TEST_ASSERT_TRUE(planeta->pobierzObiekt(STyp::Identyfikator(0xC)).czyMoznaRozbudowac());
}

void WymaganiaTest::czasBudowy(){
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x12), STyp::Poziom(0)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x13), STyp::Poziom(6)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x13), STyp::Poziom(7)));
	//UNIT_TEST_ASSERT_EQUAL(STyp::Czas(4.875), planeta->pobierzObiekt(STyp::Identyfikator(0x12)).po());
}

REJESTRUJ_PACZKE_TESTOW(WymaganiaTest);
