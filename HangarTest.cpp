#include "HangarTest.h"


HangarTest::HangarTest(void)
{
}

void HangarTest::startTestow(){
	gra = &(Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	StatekInfo& statekInfo = gra->pobierzStatek(Identyfikator(0xB));
	StatekInfo& statekInfo2 = gra->pobierzStatek(Identyfikator(0xE));
	StatekInfo& statekInfo3 = gra->pobierzStatek(Identyfikator(0xC));
	StatekInfo& statekInfo4 = gra->pobierzStatek(Identyfikator(0xD));
	statekTransportowy = shared_ptr<Statek> ( statekInfo.tworzEgzemplarz(Ilosc(25),Identyfikator(0)) );
	statekTransportowyDuzy = shared_ptr<Statek> ( statekInfo2.tworzEgzemplarz(Ilosc(1),Identyfikator(0)) );
	mysliwiec = shared_ptr<Statek> ( statekInfo3.tworzEgzemplarz(Ilosc(5),Identyfikator(0)) );
	mysliwiecDrugi = shared_ptr<Statek> ( statekInfo4.tworzEgzemplarz(Ilosc(50),Identyfikator(0)) );
}

void HangarTest::podstawowyTest(){
	UNIT_TEST_ASSERT_FALSE(statekTransportowyDuzy->dodajStatekDoHangaru(*mysliwiecDrugi));
	UNIT_TEST_ASSERT_TRUE(statekTransportowyDuzy->dodajStatekDoHangaru(*mysliwiec));
	UNIT_TEST_ASSERT_TRUE(statekTransportowyDuzy->dodajStatekDoHangaru(*statekTransportowy));
}

void HangarTest::oproznianieHangaru(){
	UNIT_TEST_ASSERT_NOTEQUAL(statekTransportowyDuzy->pobierzZajeteMiejsceHangaru(),Objetosc(0));
	statekTransportowyDuzy->oproznijHangar();
	UNIT_TEST_ASSERT_EQUAL(statekTransportowyDuzy->pobierzZajeteMiejsceHangaru(),Objetosc(0));
}

void HangarTest::dzielenieHangaru(){
	UNIT_TEST_ASSERT_EQUAL(statekTransportowyDuzy->pobierzZajeteMiejsceLadowni(),Objetosc(0));
	UNIT_TEST_ASSERT_TRUE(statekTransportowyDuzy->dodajStatekDoHangaru(*mysliwiec));
	UNIT_TEST_ASSERT_TRUE(statekTransportowyDuzy->dodajStatekDoHangaru(*statekTransportowy));
	Hangar::Zbiornik tmp = statekTransportowyDuzy->podzielHangar(Objetosc(1375),Objetosc(1390));
	UNIT_TEST_ASSERT_FALSE(tmp.pusty());
	UNIT_TEST_ASSERT_EQUAL(Ilosc(0),statekTransportowyDuzy->pobierzIloscStatkow(mysliwiec->ID()));
	UNIT_TEST_ASSERT_NOTEQUAL(Ilosc(0),statekTransportowyDuzy->pobierzIloscStatkow(statekTransportowy->ID()));
}

HangarTest::~HangarTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(HangarTest);
