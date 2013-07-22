#include "WymaganiaTest.h"


WymaganiaTest::WymaganiaTest(){
}

void WymaganiaTest::startTestow(){
	auto idPlanety = Aplikacja::getInstance().getGra().generujPlanete();
	UNIT_TEST_ASSERT_TRUE(Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(idPlanety));
	planeta = &(Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(idPlanety));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(11),Ilosc(8)) );
	a = &(planeta->pobierzStatek(Identyfikator(11)));
}

void WymaganiaTest::sprawdzenieKosztow(){
	auto tmp = a->PobierzKoszty();
	UNIT_TEST_ASSERT_EQUAL(3,tmp.size());
	UNIT_TEST_ASSERT_EQUAL( Ilosc(120000.0), tmp[0]->getIlosc());
	UNIT_TEST_ASSERT_EQUAL( Ilosc(4000.0), tmp[1]->getIlosc() );
	UNIT_TEST_ASSERT_EQUAL( Ilosc(8*1*10*5*200), tmp[2]->getIlosc());
	auto w = a->PobierzWarunki();
	UNIT_TEST_ASSERT_EQUAL(2,w.size());
	UNIT_TEST_ASSERT_EQUAL( Poziom(25), w[0]->pobierzPoziom() );
	UNIT_TEST_ASSERT_EQUAL( Poziom(5), w[1]->pobierzPoziom() );
}

void WymaganiaTest::czyMoznaWybudowacTest(){
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0xC),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x1),Ilosc(20000)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x4),Ilosc(20000)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x7),Ilosc(20000)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x13),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x10),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x13),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x10),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x13),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x10),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
}

void WymaganiaTest::czasBudowy(){
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x12),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x13),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x13),Ilosc(1)));
	UNIT_TEST_ASSERT_EQUAL( Czas(39), planeta->pobierzObiekt(Identyfikator(0x12)).pobierzCzasRozbudowy());
}

WymaganiaTest::~WymaganiaTest(){
}

REJESTRUJ_PACZKE_TESTOW(WymaganiaTest);
