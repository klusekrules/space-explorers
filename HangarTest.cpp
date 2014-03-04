#include "HangarTest.h"

void HangarTest::startTestow(){
	gra = &(SpEx::Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	SpEx::StatekInfo& statekInfo = gra->pobierzStatek(STyp::Identyfikator(5));
	SpEx::StatekInfo& statekInfo2 = gra->pobierzStatek(STyp::Identyfikator(6));
	SpEx::StatekInfo& statekInfo3 = gra->pobierzStatek(STyp::Identyfikator(7));
	SpEx::StatekInfo& statekInfo4 = gra->pobierzStatek(STyp::Identyfikator(8));
	statekTransportowy = std::shared_ptr<SpEx::Statek>(statekInfo.tworzEgzemplarz(STyp::Ilosc(25)));
	statekTransportowyDuzy = std::shared_ptr<SpEx::Statek>(statekInfo2.tworzEgzemplarz(STyp::Ilosc(50)));
	mysliwiec = std::shared_ptr<SpEx::Statek>(statekInfo3.tworzEgzemplarz(STyp::Ilosc(5)));
	transporter = std::shared_ptr<SpEx::Statek>(statekInfo4.tworzEgzemplarz(STyp::Ilosc(1)));
}

void HangarTest::podstawowyTest(){
	UNIT_TEST_ASSERT_FALSE(transporter->dodajStatekDoHangaru(*transporter));
	UNIT_TEST_ASSERT_TRUE(transporter->dodajStatekDoHangaru(*mysliwiec));
	UNIT_TEST_ASSERT_TRUE(transporter->dodajStatekDoHangaru(*statekTransportowy));
}

void HangarTest::oproznianieHangaru(){
	UNIT_TEST_ASSERT_NOTEQUAL(transporter->pobierzZajeteMiejsceHangaru(), STyp::Powierzchnia(0));
	transporter->oproznijHangar();
	UNIT_TEST_ASSERT_EQUAL(transporter->pobierzZajeteMiejsceHangaru(), STyp::Powierzchnia(0));
}

void HangarTest::dzielenieHangaru(){
	UNIT_TEST_ASSERT_EQUAL(transporter->pobierzZajeteMiejsceLadowni(), STyp::Powierzchnia(0));
	UNIT_TEST_ASSERT_TRUE(transporter->dodajStatekDoHangaru(*mysliwiec));
	UNIT_TEST_ASSERT_TRUE(transporter->dodajStatekDoHangaru(*statekTransportowyDuzy));
	SpEx::Hangar::Zbiornik tmp = transporter->podzielHangar(STyp::Powierzchnia(15500), STyp::Powierzchnia(15600));
	UNIT_TEST_ASSERT_FALSE(tmp.pusty());
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(0), transporter->pobierzIloscStatkow(statekTransportowyDuzy->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_NOTEQUAL(STyp::Ilosc(0), transporter->pobierzIloscStatkow(mysliwiec->pobierzIdentyfikator()));
}

REJESTRUJ_PACZKE_TESTOW(HangarTest);
