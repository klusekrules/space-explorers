#include "LadowniaTest.h"


LadowniaTest::LadowniaTest(void)
{
}

void LadowniaTest::startTestow(){
	gra = &(Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	StatekInfo& statekInfo = gra->pobierzStatek(Identyfikator(0xB));
	SurowceInfo& surowceInfo3 = gra->pobierzSurowce(Identyfikator(0x6));
	SurowceInfo& surowceInfo = gra->pobierzSurowce(Identyfikator(0x1));
	SurowceInfo& surowceInfo2 = gra->pobierzSurowce(Identyfikator(0xA));
	statekTransportowy = shared_ptr<Statek> ( statekInfo.tworzEgzemplarz(Ilosc(10),Identyfikator(0)) );
	metal = shared_ptr<Surowce> ( surowceInfo.tworzEgzemplarz(Ilosc(10000),Identyfikator(0)) );
	energia = shared_ptr<Surowce> ( surowceInfo2.tworzEgzemplarz(Ilosc(10000),Identyfikator(0)) );
	krysztal = shared_ptr<Surowce> ( surowceInfo3.tworzEgzemplarz(Ilosc(1000),Identyfikator(0)) );
}

void LadowniaTest::podstawowyTest(){
	UNIT_TEST_ASSERT_FALSE(statekTransportowy->dodajObiektDoLadowni(*energia));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->dodajObiektDoLadowni(*metal));
	UNIT_TEST_ASSERT_FALSE(statekTransportowy->dodajObiektDoLadowni(*metal));
}

void LadowniaTest::oproznianieLadowni(){
	UNIT_TEST_ASSERT_NOTEQUAL(statekTransportowy->pobierzZajeteMiejsceLadowni(),Objetosc(0));
	statekTransportowy->oproznijLadownie();
	UNIT_TEST_ASSERT_EQUAL(statekTransportowy->pobierzZajeteMiejsceLadowni(),Objetosc(0));
}

void LadowniaTest::dzielenieLadowni(){
	UNIT_TEST_ASSERT_EQUAL(statekTransportowy->pobierzZajeteMiejsceLadowni(),Objetosc(0));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->dodajObiektDoLadowni(*metal));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->dodajObiektDoLadowni(*krysztal));
	Ladownia::Zbiornik tmp = statekTransportowy->podzielLadownie(Objetosc(10500),Objetosc(11000));
	UNIT_TEST_ASSERT_FALSE(tmp.pusty());
	UNIT_TEST_ASSERT_EQUAL(Ilosc(0),statekTransportowy->pobierzIloscObiektowLadowni(krysztal->ID()));
	UNIT_TEST_ASSERT_NOTEQUAL(Ilosc(0),statekTransportowy->pobierzIloscObiektowLadowni(metal->ID()));
}

LadowniaTest::~LadowniaTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(LadowniaTest);
