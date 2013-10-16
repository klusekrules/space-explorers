#include "WymaganiaTest.h"


WymaganiaTest::WymaganiaTest(){
}

void WymaganiaTest::startTestow(){
	planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(Identyfikator(0x1));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(11), Poziom(1)),Ilosc(8)) );
	a = &(planeta->pobierzStatek(Klucz(Identyfikator(11), Poziom(1))));
}

void WymaganiaTest::sprawdzenieKosztow(){
	auto tmp = a->pobierzKosztyRozbudowy();
	UNIT_TEST_ASSERT_EQUAL(3,tmp.size());
	UNIT_TEST_ASSERT_EQUAL( Ilosc(480000.0), tmp[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL( Ilosc(16000.0), tmp[1]->pobierzIlosc() );
	UNIT_TEST_ASSERT_EQUAL( Ilosc(8*2*10*5*200), tmp[2]->pobierzIlosc());
	auto w = a->pobierzWarunkiRozbudowy();
	UNIT_TEST_ASSERT_EQUAL(2,w.size());
	UNIT_TEST_ASSERT_EQUAL( Poziom(50), w[0]->pobierzPoziom() );
	UNIT_TEST_ASSERT_EQUAL( Poziom(10), w[1]->pobierzPoziom() );
}

void WymaganiaTest::czyMoznaWybudowacTest(){
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0xC), Poziom(1)),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(1), Poziom(1)),Ilosc(60000)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(4), Poziom(1)),Ilosc(60000)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(7), Poziom(1)),Ilosc(60000)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x13), Poziom(0)),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x10), Poziom(0)),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x13), Poziom(1)),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x10), Poziom(1)),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x13), Poziom(2)),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x10), Poziom(2)),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x13), Poziom(3)),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x10), Poziom(3)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x13), Poziom(4)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x10), Poziom(4)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x13), Poziom(5)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzObiekt(Klucz(Identyfikator(0xC), Poziom(1))).czyMoznaRozbudowac());

}

void WymaganiaTest::czasBudowy(){
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x12), Poziom(0)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x13), Poziom(6)),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Klucz(Identyfikator(0x13), Poziom(7)),Ilosc(1)));
	UNIT_TEST_ASSERT_EQUAL( Czas(4.875), planeta->pobierzObiekt(Klucz(Identyfikator(0x12), Poziom(1))).pobierzCzasRozbudowy() );
}

WymaganiaTest::~WymaganiaTest(){
}

REJESTRUJ_PACZKE_TESTOW(WymaganiaTest);
