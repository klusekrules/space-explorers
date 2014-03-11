#include "ObronaTest.h"

void ObronaTest::startTestow(){
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x6));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(14), STyp::Ilosc(2)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(15), STyp::Ilosc(1)));
	a = &(planeta->pobierzObrone(STyp::Identyfikator(14)));
	b = &(planeta->pobierzObrone(STyp::Identyfikator(15)));
}

void ObronaTest::Test1(){
	UNIT_TEST_ASSERT_EQUAL(STyp::Powierzchnia(2.31*2.0), a->pobierzPowierzchnie());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(90.0*2.0), a->pobierzAtak());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(120.0*2.0), a->pobierzPancerz());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(10.0*2.0), a->pobierzOslone());
	UNIT_TEST_ASSERT_EQUAL(STyp::Powierzchnia(4.62), b->pobierzPowierzchnie());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(80.0), b->pobierzAtak());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(60.0), b->pobierzPancerz());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(30.0), b->pobierzOslone());
}

void ObronaTest::Test2(){
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(1), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x1), STyp::Ilosc(1500)));
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(1), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x2), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(1), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x3), STyp::Ilosc(100)));
	UNIT_TEST_ASSERT_TRUE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(1), b->pobierzIdentyfikatorPlanety())));	
}

void ObronaTest::Test3(){
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(2), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x1), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(2), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x2), STyp::Ilosc(400)));
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(2), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x3), STyp::Ilosc(50)));
	UNIT_TEST_ASSERT_TRUE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(1), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(2), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x1), STyp::Ilosc(1500)));
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(2), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x2), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(2), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x3), STyp::Ilosc(100)));
	UNIT_TEST_ASSERT_TRUE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(2), b->pobierzIdentyfikatorPlanety())));
}

REJESTRUJ_PACZKE_TESTOW(ObronaTest);
