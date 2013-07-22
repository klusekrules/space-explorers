#include "LadowniaTest.h"


LadowniaTest::LadowniaTest(void)
{
}

void LadowniaTest::startTestow(){
	gra = &(Aplikacja::getInstance().getGra());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	StatekInfo& statekInfo = gra->getStatek(Identyfikator(0xB));
	StatekInfo& statekInfo2 = gra->getStatek(Identyfikator(0xC));
	StatekInfo& statekInfo3 = gra->getStatek(Identyfikator(0xE));
	SurowceInfo& surowceInfo = gra->getSurowce(Identyfikator(0x1));
	SurowceInfo& surowceInfo2 = gra->getSurowce(Identyfikator(0xA));
	statekTransportowy = shared_ptr<Statek> ( statekInfo.tworzEgzemplarz(Ilosc(10),Identyfikator(0)) );
	statekTransportowyDuzy = shared_ptr<Statek> ( statekInfo3.tworzEgzemplarz(Ilosc(1),Identyfikator(0)) );
	metal = shared_ptr<Surowce> ( surowceInfo.tworzEgzemplarz(Ilosc(10000),Identyfikator(0)) );
	energia = shared_ptr<Surowce> ( surowceInfo2.tworzEgzemplarz(Ilosc(10000),Identyfikator(0)) );
	mysliwiec = shared_ptr<Statek> ( statekInfo2.tworzEgzemplarz(Ilosc(10),Identyfikator(0)) );
}

void LadowniaTest::podstawowyTest(){
	UNIT_TEST_ASSERT_FALSE(statekTransportowy->DodajObiektDoLadowni(*energia));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->DodajObiektDoLadowni(*metal));
	UNIT_TEST_ASSERT_FALSE(statekTransportowy->DodajObiektDoLadowni(*metal));
}

void LadowniaTest::oproznianieLadowni(){
	UNIT_TEST_ASSERT_NOTEQUAL(statekTransportowy->getZajeteMiejsce(),Objetosc(0));
	statekTransportowy->OproznijLadownie();
	UNIT_TEST_ASSERT_EQUAL(statekTransportowy->getZajeteMiejsce(),Objetosc(0));
}

void LadowniaTest::dodawanieStatkow(){
	UNIT_TEST_ASSERT_FALSE(statekTransportowy->DodajObiektDoLadowni(*statekTransportowyDuzy));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->DodajObiektDoLadowni(*mysliwiec));
}

void LadowniaTest::dzielenieLadowni(){
	statekTransportowy->OproznijLadownie();
	UNIT_TEST_ASSERT_EQUAL(statekTransportowy->getZajeteMiejsce(),Objetosc(0));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->DodajObiektDoLadowni(*metal));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->DodajObiektDoLadowni(*mysliwiec));
	Ladownia::Zbiornik* tmp = statekTransportowy->PodzielLadownie(Objetosc(11000),Objetosc(10500));
	UNIT_TEST_ASSERT_NOTNULL(tmp);
	delete tmp;
}

LadowniaTest::~LadowniaTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(LadowniaTest);
