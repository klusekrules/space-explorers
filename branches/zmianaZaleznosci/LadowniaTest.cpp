#include "LadowniaTest.h"

void LadowniaTest::startTestow(){
	gra = &(SpEx::Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	SpEx::StatekInfo& statekInfo = gra->pobierzStatek(STyp::Identyfikator(0x6));
	SpEx::SurowceInfo& surowceInfo3 = gra->pobierzSurowce(STyp::Identyfikator(0x2));
	SpEx::SurowceInfo& surowceInfo = gra->pobierzSurowce(STyp::Identyfikator(0x1));
	SpEx::SurowceInfo& surowceInfo2 = gra->pobierzSurowce(STyp::Identyfikator(0x4));
	statekTransportowy = std::shared_ptr<SpEx::Statek>(statekInfo.tworzEgzemplarz(STyp::Ilosc(5)));
	metal = std::shared_ptr<SpEx::Surowce>(surowceInfo.tworzEgzemplarz(STyp::Ilosc(10000)));
	energia = std::shared_ptr<SpEx::Surowce>(surowceInfo2.tworzEgzemplarz(STyp::Ilosc(10000)));
	krysztal = std::shared_ptr<SpEx::Surowce>(surowceInfo3.tworzEgzemplarz(STyp::Ilosc(1000)));
}

void LadowniaTest::podstawowyTest(){
	UNIT_TEST_ASSERT_FALSE(statekTransportowy->dodajObiektDoLadowni(*energia));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->dodajObiektDoLadowni(*metal));
	UNIT_TEST_ASSERT_FALSE(statekTransportowy->dodajObiektDoLadowni(*metal));
}

void LadowniaTest::oproznianieLadowni(){
	UNIT_TEST_ASSERT_NOTEQUAL(statekTransportowy->pobierzZajeteMiejsceLadowni(), STyp::Objetosc(0));
	statekTransportowy->oproznijLadownie();
	UNIT_TEST_ASSERT_EQUAL(statekTransportowy->pobierzZajeteMiejsceLadowni(), STyp::Objetosc(0));
}

void LadowniaTest::dzielenieLadowni(){
	UNIT_TEST_ASSERT_EQUAL(statekTransportowy->pobierzZajeteMiejsceLadowni(), STyp::Objetosc(0));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->dodajObiektDoLadowni(*metal));
	UNIT_TEST_ASSERT_TRUE(statekTransportowy->dodajObiektDoLadowni(*krysztal));
	SpEx::Ladownia::Zbiornik tmp = statekTransportowy->podzielLadownie(STyp::Objetosc(10500), STyp::Objetosc(11000));
	UNIT_TEST_ASSERT_FALSE(tmp.pusty());
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(0), statekTransportowy->pobierzIloscObiektowLadowni(krysztal->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_NOTEQUAL(STyp::Ilosc(0), statekTransportowy->pobierzIloscObiektowLadowni(metal->pobierzIdentyfikator()));
}

REJESTRUJ_PACZKE_TESTOW(LadowniaTest);
