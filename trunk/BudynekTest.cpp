#include "BudynekTest.h"


BudynekTest::BudynekTest(void)
{
}
void BudynekTest::startTestow() {
	planeta = Aplikacja::pobierzInstancje().pobierzGre().stworzPlanete();
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(17),Poziom(1)),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(17),Poziom(1)),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(17),Poziom(2)),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(18),Poziom(1)),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(18),Poziom(1)),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(19),Poziom(1)),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(19),Poziom(1)),Ilosc(20)) );
	a = &(planeta->pobierzBudynek(Planeta::Indeks(Identyfikator(17),Poziom(3))));
	b = &(planeta->pobierzBudynek(Planeta::Indeks(Identyfikator(18),Poziom(2))));
	c = &(planeta->pobierzBudynek(Planeta::Indeks(Identyfikator(19),Poziom(2))));
}

void BudynekTest::podstawowyTest(){

	UNIT_TEST_ASSERT_EQUAL(Ilosc(1),a->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(Ilosc(1),b->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(Ilosc(1),c->pobierzIlosc());

	auto z = a->pobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_TRUE(( z.size()>0));
	UNIT_TEST_ASSERT_EQUAL(Ilosc(180), z[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(Identyfikator(10), z[0]->pobierzIdentyfikator());
	
	auto p = a->pobierzProdukcje();
	UNIT_TEST_ASSERT_TRUE(( p.size()>0));
	UNIT_TEST_ASSERT_EQUAL( Ilosc(6000), p[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL( Identyfikator(1), p[0]->pobierzIdentyfikator());
	

	p = b->pobierzProdukcje();
	UNIT_TEST_ASSERT_TRUE((p.size()>0));
	UNIT_TEST_ASSERT_EQUAL( Ilosc(6000), p[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL( Identyfikator(10), p[0]->pobierzIdentyfikator());
	
	z = b->pobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_EQUAL( 0, z.size());

	p = c->pobierzProdukcje();
	UNIT_TEST_ASSERT_EQUAL( 0, p.size());
	z = c->pobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_EQUAL( 0, z.size());
}

BudynekTest::~BudynekTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(BudynekTest);
