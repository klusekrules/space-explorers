#include "BudynekTest.h"


BudynekTest::BudynekTest(void)
{
}
void BudynekTest::startTestow() {
	planeta = Aplikacja::getInstance().getGra().stworzPlanete();
	UNIT_TEST_ASSERT_TRUE(Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(17),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(17),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(17),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(18),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(18),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(19),Ilosc(20)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(19),Ilosc(20)) );
	a = &(planeta->pobierzBudynek(Identyfikator(17)));
	b = &(planeta->pobierzBudynek(Identyfikator(18)));
	c = &(planeta->pobierzBudynek(Identyfikator(19)));
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
