#include "BudynekTest.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Gra.h"

void BudynekTest::startTestow() {
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x8));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->odepnijPlanete();
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(11)), SpEx::PodstawoweParametry(STyp::Poziom(1))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(11)), SpEx::PodstawoweParametry(STyp::Poziom(1))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(11)), SpEx::PodstawoweParametry(STyp::Poziom(1))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(12)), SpEx::PodstawoweParametry(STyp::Poziom(1))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(12)), SpEx::PodstawoweParametry(STyp::Poziom(1))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(13)), SpEx::PodstawoweParametry(STyp::Poziom(1))));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(13)), SpEx::PodstawoweParametry(STyp::Poziom(1))));
	a = &(planeta->pobierzObiekt<SpEx::Budynek>(SpEx::Planeta::Indeks(STyp::Identyfikator(11))));
	b = &(planeta->pobierzObiekt<SpEx::Budynek>(SpEx::Planeta::Indeks(STyp::Identyfikator(12))));
	c = &(planeta->pobierzObiekt<SpEx::Budynek>(SpEx::Planeta::Indeks(STyp::Identyfikator(13))));
}

void BudynekTest::podstawowyTest(){

	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(3), a->pobierzPoziom());
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(2), b->pobierzPoziom());
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(2), c->pobierzPoziom());

	auto z = a->pobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_TRUE(( z.size()>0));
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(120), z[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(4), z[0]->pobierzIdentyfikator());
	
	auto p = a->pobierzProdukcje();
	UNIT_TEST_ASSERT_TRUE(( p.size()>0));
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(50), p[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(1), p[0]->pobierzIdentyfikator());
	

	p = b->pobierzProdukcje();
	UNIT_TEST_ASSERT_TRUE((p.size()>0));
	UNIT_TEST_ASSERT_EQUAL(STyp::Ilosc(320), p[0]->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(4), p[0]->pobierzIdentyfikator());
	
	z = b->pobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_EQUAL( 0, z.size());

	p = c->pobierzProdukcje();
	UNIT_TEST_ASSERT_EQUAL( 0, p.size());
	z = c->pobierzZapotrzebowanie();
	UNIT_TEST_ASSERT_EQUAL( 0, z.size());
}

REJESTRUJ_PACZKE_TESTOW(BudynekTest);
