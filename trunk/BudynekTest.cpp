#include "BudynekTest.h"


BudynekTest::BudynekTest(void)
{
}
void BudynekTest::startTestow() {
	auto idPlanety = Aplikacja::getInstance().getGra().generujPlanete();
	UNIT_TEST_ASSERT_TRUE(Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(idPlanety));
	planeta = &(Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(idPlanety));
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

	auto z = a->PobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_TRUE(( z.size()>0));
	UNIT_TEST_ASSERT_EQUAL(Ilosc(180), z[0]->getIlosc());
	UNIT_TEST_ASSERT_EQUAL(Identyfikator(10), z[0]->pobierzIdentyfikator());
	
	auto p = a->PobierzProdukcje();
	UNIT_TEST_ASSERT_TRUE(( p.size()>0));
	UNIT_TEST_ASSERT_EQUAL( Ilosc(6000), p[0]->getIlosc());
	UNIT_TEST_ASSERT_EQUAL( Identyfikator(1), p[0]->pobierzIdentyfikator());
	

	p = b->PobierzProdukcje();
	UNIT_TEST_ASSERT_TRUE((p.size()>0));
	UNIT_TEST_ASSERT_EQUAL( Ilosc(6000), p[0]->getIlosc());
	UNIT_TEST_ASSERT_EQUAL( Identyfikator(10), p[0]->pobierzIdentyfikator());
	
	z = b->PobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_EQUAL( 0, z.size());

	p = c->PobierzProdukcje();
	UNIT_TEST_ASSERT_EQUAL( 0, p.size());
	z = c->PobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_EQUAL( 0, z.size());
}

BudynekTest::~BudynekTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(BudynekTest);
