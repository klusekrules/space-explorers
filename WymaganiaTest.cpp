#include "WymaganiaTest.h"
#include "Aplikacja.h"
#include "Gra.h"

void WymaganiaTest::startTestow(){
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x1));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->odepnijPlanete();
	UNIT_TEST_ASSERT_TRUE( SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(5), STyp::Ilosc(8)));
	a = &(planeta->pobierzObiekt<SpEx::Statek>(STyp::Identyfikator(5)));
}

void WymaganiaTest::sprawdzenieKosztow(){
	auto w = a->pobierzKryteriaRozbudowy();
	UNIT_TEST_ASSERT_EQUAL(3, w.size());
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(1), w[0]->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(2000), w[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(2), w[1]->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(2000), w[1]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(9), w[2]->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(3), w[2]->pobierzPoziom());
}

void WymaganiaTest::czyMoznaWybudowacTest(){
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(6), STyp::Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(1), STyp::Ilosc(6000)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(2), STyp::Ilosc(6000)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(9), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(9), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(9), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(10), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(10), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(10), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(10), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_FALSE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(10), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(10), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(9), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(1), STyp::Ilosc(6000)));
	UNIT_TEST_ASSERT_TRUE(planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(6)).czyMoznaRozbudowac());
}

void WymaganiaTest::czasBudowy(){
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(1), STyp::Ilosc(3000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(2), STyp::Ilosc(600)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(3), STyp::Ilosc(70)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(12), STyp::Poziom(1)));
	UNIT_TEST_ASSERT_EQUAL(STyp::Czas(132), planeta->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(12)).pobierzCzasRozbudowy());
}

REJESTRUJ_PACZKE_TESTOW(WymaganiaTest);
