#include "ObronaTest.h"

void ObronaTest::startTestow(){
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x6));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x14), STyp::Ilosc(2)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x15), STyp::Ilosc(0)));
	a = &(planeta->pobierzObrone(STyp::Identyfikator(0x14)));
	b = const_cast<SpEx::Obrona*>(&(planeta->pobierzObrone(STyp::Identyfikator(0x15))));
}

void ObronaTest::Test1(){
	//UNIT_TEST_ASSERT_EQUAL(STyp::Masa(900.0*2.0), a->pobierzMase());
	//UNIT_TEST_ASSERT_EQUAL(STyp::Objetosc(50.0*2.0), a->pobierzObjetosc());
	//UNIT_TEST_ASSERT_EQUAL(STyp::Powierzchnia(10.0*2.0), a->pobierzPowierzchnie());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(90.0*2.0), a->pobierzAtak());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(60.0*2.0), a->pobierzPancerz());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(0), a->pobierzOslone());
}

void ObronaTest::Test2(){
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x1), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x4), STyp::Ilosc(200)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x7), STyp::Ilosc(150)));
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania( SpEx::PodstawoweParametry(STyp::Ilosc(1), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0xF), STyp::Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(1), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0xF), STyp::Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(1), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x15), STyp::Ilosc(1)));
	//UNIT_TEST_ASSERT_EQUAL(STyp::Masa(60.0), b->pobierzMase());
	//UNIT_TEST_ASSERT_EQUAL(STyp::Objetosc(40.0 * 0.9), b->pobierzObjetosc());
	//UNIT_TEST_ASSERT_EQUAL(STyp::Powierzchnia(30.0 * 0.8), b->pobierzPowierzchnie());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(0.0), b->pobierzAtak());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(60.0*4.0), b->pobierzPancerz());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(2500.0*2.0), b->pobierzOslone());
	
}

void ObronaTest::Test3(){
	//b->wzrostPoziomu();
	UNIT_TEST_ASSERT_FALSE( b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(1),b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x1), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x4), STyp::Ilosc(200)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x7), STyp::Ilosc(150)));
	UNIT_TEST_ASSERT_TRUE(b->pobierzObronaInfo().czySpelniaWymagania(SpEx::PodstawoweParametry(STyp::Ilosc(1), b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x15), STyp::Ilosc(1)));
	//UNIT_TEST_ASSERT_EQUAL(STyp::Masa(60.0*4.0 * 2.0), b->pobierzMase());
	//UNIT_TEST_ASSERT_EQUAL(STyp::Objetosc(40.0 * 0.9 * 2.0 * 2.0), b->pobierzObjetosc());
	//UNIT_TEST_ASSERT_EQUAL(STyp::Powierzchnia(30.0 * 0.8* 2.0* 2.0), b->pobierzPowierzchnie());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(0.0), b->pobierzAtak());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(60.0*4.0* 2.0* 2.0), b->pobierzPancerz());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(2500.0*2.0* 2.0* 2.0), b->pobierzOslone());
}

REJESTRUJ_PACZKE_TESTOW(ObronaTest);
