#include "BudynekTest.h"

void BudynekTest::startTestow() {
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x8));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(17)), SpEx::PodstawoweParametry(STyp::Ilosc(20))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(17)), SpEx::PodstawoweParametry(STyp::Ilosc(20))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(17)), SpEx::PodstawoweParametry(STyp::Ilosc(20))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(18)), SpEx::PodstawoweParametry(STyp::Ilosc(20))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(18)), SpEx::PodstawoweParametry(STyp::Ilosc(20))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(19)), SpEx::PodstawoweParametry(STyp::Ilosc(20))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(19)), SpEx::PodstawoweParametry(STyp::Ilosc(20))));
	a = &(planeta->pobierzBudynek(SpEx::Planeta::Indeks(STyp::Identyfikator(17))));
	b = &(planeta->pobierzBudynek(SpEx::Planeta::Indeks(STyp::Identyfikator(18))));
	c = &(planeta->pobierzBudynek(SpEx::Planeta::Indeks(STyp::Identyfikator(19))));
}

void BudynekTest::podstawowyTest(){

	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(1), a->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(1), b->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(1), c->pobierzIlosc());

	auto z = a->pobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_TRUE(( z.size()>0));
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(180), z[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(10), z[0]->pobierzIdentyfikator());
	
	auto p = a->pobierzProdukcje();
	UNIT_TEST_ASSERT_TRUE(( p.size()>0));
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(6000), p[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(1), p[0]->pobierzIdentyfikator());
	

	p = b->pobierzProdukcje();
	UNIT_TEST_ASSERT_TRUE((p.size()>0));
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(6000), p[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(10), p[0]->pobierzIdentyfikator());
	
	z = b->pobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_EQUAL( 0, z.size());

	p = c->pobierzProdukcje();
	UNIT_TEST_ASSERT_EQUAL( 0, p.size());
	z = c->pobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_EQUAL( 0, z.size());
}

//REJESTRUJ_PACZKE_TESTOW(BudynekTest);
