#include "HangarTest.h"

void HangarTest::startTestow(){
	gra = &(SpEx::Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	SpEx::StatekInfo& statekInfo = gra->pobierzStatek(STyp::Identyfikator(0xB));
	SpEx::StatekInfo& statekInfo2 = gra->pobierzStatek(STyp::Identyfikator(0xE));
	SpEx::StatekInfo& statekInfo3 = gra->pobierzStatek(STyp::Identyfikator(0xC));
	SpEx::StatekInfo& statekInfo4 = gra->pobierzStatek(STyp::Identyfikator(0xD));
	statekTransportowy = std::shared_ptr<SpEx::Statek>(statekInfo.tworzEgzemplarz(STyp::Ilosc(25)));
	statekTransportowyDuzy = std::shared_ptr<SpEx::Statek>(statekInfo2.tworzEgzemplarz(STyp::Ilosc(1)));
	mysliwiec = std::shared_ptr<SpEx::Statek>(statekInfo3.tworzEgzemplarz(STyp::Ilosc(5)));
	mysliwiecDrugi = std::shared_ptr<SpEx::Statek>(statekInfo4.tworzEgzemplarz(STyp::Ilosc(50)));
}

void HangarTest::podstawowyTest(){
	UNIT_TEST_ASSERT_FALSE(statekTransportowyDuzy->dodajStatekDoHangaru(*mysliwiecDrugi));
	UNIT_TEST_ASSERT_TRUE(statekTransportowyDuzy->dodajStatekDoHangaru(*mysliwiec));
	UNIT_TEST_ASSERT_TRUE(statekTransportowyDuzy->dodajStatekDoHangaru(*statekTransportowy));
}

void HangarTest::oproznianieHangaru(){
	UNIT_TEST_ASSERT_NOTEQUAL(statekTransportowyDuzy->pobierzZajeteMiejsceHangaru(), STyp::Objetosc(0));
	statekTransportowyDuzy->oproznijHangar();
	UNIT_TEST_ASSERT_EQUAL(statekTransportowyDuzy->pobierzZajeteMiejsceHangaru(), STyp::Objetosc(0));
}

void HangarTest::dzielenieHangaru(){
	UNIT_TEST_ASSERT_EQUAL(statekTransportowyDuzy->pobierzZajeteMiejsceLadowni(), STyp::Objetosc(0));
	UNIT_TEST_ASSERT_TRUE(statekTransportowyDuzy->dodajStatekDoHangaru(*mysliwiec));
	UNIT_TEST_ASSERT_TRUE(statekTransportowyDuzy->dodajStatekDoHangaru(*statekTransportowy));
	SpEx::Hangar::Zbiornik tmp = statekTransportowyDuzy->podzielHangar(STyp::Objetosc(1375), STyp::Objetosc(1390));
	UNIT_TEST_ASSERT_FALSE(tmp.pusty());
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(0), statekTransportowyDuzy->pobierzIloscStatkow(mysliwiec->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_NOTEQUAL(STyp::Ilosc(0), statekTransportowyDuzy->pobierzIloscStatkow(statekTransportowy->pobierzIdentyfikator()));
}

//REJESTRUJ_PACZKE_TESTOW(HangarTest);
