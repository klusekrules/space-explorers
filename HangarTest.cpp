#include "HangarTest.h"

void HangarTest::startTestow(){
	gra = &(SpEx::Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	auto& statekInfo = gra->pobierzObiekt<SpEx::StatekInfo>(STyp::Identyfikator(5));
	auto& statekInfo2 = gra->pobierzObiekt<SpEx::StatekInfo>(STyp::Identyfikator(6));
	auto& statekInfo3 = gra->pobierzObiekt<SpEx::StatekInfo>(STyp::Identyfikator(7));
	auto& statekInfo4 = gra->pobierzObiekt<SpEx::StatekInfo>(STyp::Identyfikator(8));
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
