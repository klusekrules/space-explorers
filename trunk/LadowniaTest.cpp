#include "LadowniaTest.h"


LadowniaTest::LadowniaTest(void)
{
}

void LadowniaTest::startTestow(){
	gra = &(Aplikacja::getInstance().getGra());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	StatekInfo& statekInfo = gra->pobierzStatek(Identyfikator(0xB));
	StatekInfo& statekInfo2 = gra->pobierzStatek(Identyfikator(0xC));
	StatekInfo& statekInfo3 = gra->pobierzStatek(Identyfikator(0xE));
	SurowceInfo& surowceInfo = gra->pobierzSurowce(Identyfikator(0x1));
	SurowceInfo& surowceInfo2 = gra->pobierzSurowce(Identyfikator(0xA));
	statekTransportowy = shared_ptr<Statek> ( statekInfo.tworzEgzemplarz(Ilosc(10),Identyfikator(0)) );
	statekTransportowyDuzy = shared_ptr<Statek> ( statekInfo3.tworzEgzemplarz(Ilosc(1),Identyfikator(0)) );
	metal = shared_ptr<Surowce> ( surowceInfo.tworzEgzemplarz(Ilosc(10000),Identyfikator(0)) );
	energia = shared_ptr<Surowce> ( surowceInfo2.tworzEgzemplarz(Ilosc(10000),Identyfikator(0)) );
	mysliwiec = shared_ptr<Statek> ( statekInfo2.tworzEgzemplarz(Ilosc(10),Identyfikator(0)) );
}

void LadowniaTest::podstawowyTest(){
	UNIT_TEST_ASSERT_FALSE(statekTransportowy->dodajObiektDoLadowni(*energia));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->dodajObiektDoLadowni(*metal));
	UNIT_TEST_ASSERT_FALSE(statekTransportowy->dodajObiektDoLadowni(*metal));
}

void LadowniaTest::oproznianieLadowni(){
	UNIT_TEST_ASSERT_NOTEQUAL(statekTransportowy->pobierzZajeteMiejsce(),Objetosc(0));
	statekTransportowy->oproznijLadownie();
	UNIT_TEST_ASSERT_EQUAL(statekTransportowy->pobierzZajeteMiejsce(),Objetosc(0));
}

void LadowniaTest::dodawanieStatkow(){
	UNIT_TEST_ASSERT_FALSE(statekTransportowy->dodajObiektDoLadowni(*statekTransportowyDuzy));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->dodajObiektDoLadowni(*mysliwiec));
	statekTransportowy->oproznijLadownie();
}

void LadowniaTest::dzielenieLadowni(){
	UNIT_TEST_ASSERT_EQUAL(statekTransportowy->pobierzZajeteMiejsce(),Objetosc(0));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->dodajObiektDoLadowni(*metal));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->dodajObiektDoLadowni(*mysliwiec));
	Ladownia::Zbiornik tmp = statekTransportowy->podzielLadownie(Objetosc(10500),Objetosc(11000));
	UNIT_TEST_ASSERT_FALSE(tmp.pusty());
}

LadowniaTest::~LadowniaTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(LadowniaTest);
