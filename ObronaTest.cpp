#include "ObronaTest.h"


ObronaTest::ObronaTest(void)
{
}


ObronaTest::~ObronaTest(void)
{
}


void ObronaTest::startTestow(){
	planeta = Aplikacja::pobierzInstancje().pobierzGre().stworzPlanete();
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x14),Ilosc(2)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x15),Ilosc(0)) );
	a = &(planeta->pobierzObrone(Identyfikator(0x14)));
	b = const_cast<Obrona*>(&(planeta->pobierzObrone(Identyfikator(0x15))));
}

void ObronaTest::Test1(){
	UNIT_TEST_ASSERT_EQUAL( Masa(900.0*2.0), a->pobierzMase() );
	UNIT_TEST_ASSERT_EQUAL( Objetosc(50.0*2.0), a->pobierzObjetosc() );
	UNIT_TEST_ASSERT_EQUAL( Powierzchnia(10.0*2.0), a->pobierzPowierzchnie() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(90.0*2.0), a->pobierzAtak() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(60.0*2.0), a->pobierzPancerz() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(0), a->pobierzOslone() );
}

void ObronaTest::Test2(){
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x1),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x4),Ilosc(200)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x7),Ilosc(150)));
	UNIT_TEST_ASSERT_FALSE( b->pobierzObronaInfo().ObiektInfo::czySpelniaWymagania(Ilosc(1),PodstawoweParametry(Poziom(1),b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0xF),Ilosc(1)));
	UNIT_TEST_ASSERT_FALSE( b->pobierzObronaInfo().ObiektInfo::czySpelniaWymagania(Ilosc(1),PodstawoweParametry(Poziom(1),b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0xF),Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE( b->pobierzObronaInfo().ObiektInfo::czySpelniaWymagania(Ilosc(1),PodstawoweParametry(Poziom(1),b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x15),Ilosc(1)));
	UNIT_TEST_ASSERT_EQUAL( Masa(60.0), b->pobierzMase() );
	UNIT_TEST_ASSERT_EQUAL( Objetosc(40.0 * 0.9), b->pobierzObjetosc() );
	UNIT_TEST_ASSERT_EQUAL( Powierzchnia(30.0 * 0.8), b->pobierzPowierzchnie() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(0.0), b->pobierzAtak() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(60.0*4.0), b->pobierzPancerz() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(2500.0*2.0), b->pobierzOslone() );
	
}

void ObronaTest::Test3(){
	b->wzrostPoziomu();
	UNIT_TEST_ASSERT_FALSE( b->pobierzObronaInfo().ObiektInfo::czySpelniaWymagania(Ilosc(1),PodstawoweParametry(Poziom(2),b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x1),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x4),Ilosc(200)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x7),Ilosc(150)));
	UNIT_TEST_ASSERT_TRUE( b->pobierzObronaInfo().ObiektInfo::czySpelniaWymagania(Ilosc(1),PodstawoweParametry(Poziom(2),b->pobierzIdentyfikatorPlanety())));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x15),Ilosc(1)));
	UNIT_TEST_ASSERT_EQUAL( Masa(60.0*4.0 * 2.0), b->pobierzMase() );
	UNIT_TEST_ASSERT_EQUAL( Objetosc(40.0 * 0.9 * 2.0 * 2.0), b->pobierzObjetosc() );
	UNIT_TEST_ASSERT_EQUAL( Powierzchnia(30.0 * 0.8* 2.0* 2.0), b->pobierzPowierzchnie() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(0.0), b->pobierzAtak() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(60.0*4.0* 2.0* 2.0), b->pobierzPancerz() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(2500.0*2.0* 2.0* 2.0), b->pobierzOslone() );
}

REJESTRUJ_PACZKE_TESTOW(ObronaTest);
