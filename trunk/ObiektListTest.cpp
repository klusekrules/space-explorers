#include "ObiektListTest.h"

void ObiektListTest::startTestow(){
	SpEx::Gra& gra = SpEx::Aplikacja::pobierzInstancje().pobierzGre();
	a = std::shared_ptr<SpEx::Statek>(gra.pobierzStatek(STyp::Identyfikator(5)).tworzEgzemplarz(STyp::Ilosc(8)));
	b = std::shared_ptr<SpEx::Statek>(gra.pobierzStatek(STyp::Identyfikator(6)).tworzEgzemplarz(STyp::Ilosc(8)));
	c = std::shared_ptr<SpEx::Statek>(gra.pobierzStatek(STyp::Identyfikator(7)).tworzEgzemplarz(STyp::Ilosc(8)));
	d = std::shared_ptr<SpEx::Statek>(gra.pobierzStatek(STyp::Identyfikator(8)).tworzEgzemplarz(STyp::Ilosc(8)));
	UNIT_TEST_ASSERT_NOTNULL(a);
	UNIT_TEST_ASSERT_NOTNULL(b);
	UNIT_TEST_ASSERT_NOTNULL(c);
	UNIT_TEST_ASSERT_NOTNULL(d);
}

void ObiektListTest::podstawowyTest(){
	lista.dodaj(a);
	lista.dodaj(b);
	lista.dodaj(c);
	lista.dodaj(d);
	auto l = lista.listaObiektow();
	UNIT_TEST_ASSERT_FALSE(l.empty());
	auto r = lista.listaKluczy();
	UNIT_TEST_ASSERT_FALSE(r.empty());
	SpEx::Statek& sTmp1 = *lista.pobierz(STyp::Identyfikator(6));
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(6), sTmp1.pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE(lista.usun(STyp::Identyfikator(5)));
	std::shared_ptr<SpEx::Statek> sTmp2 = lista.wyjmij(STyp::Identyfikator(8));
	UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(8), sTmp2->pobierzIdentyfikator());
	l = lista.listaObiektow();
	UNIT_TEST_ASSERT_FALSE(l.empty());
	r = lista.listaKluczy();
	UNIT_TEST_ASSERT_FALSE(r.empty());
	UNIT_TEST_ASSERT_TRUE(SpEx::ListaObiektow<SpEx::Statek>::przenies(r.front(), STyp::Ilosc(1), lista, listaDruga));
	STyp::Ilosc porownanie = lista.pobierz(r.front())->pobierzIlosc() + listaDruga.pobierz(r.front())->pobierzIlosc();
	UNIT_TEST_ASSERT_EQUAL(1,listaDruga.rozmiar());
	UNIT_TEST_ASSERT_TRUE(SpEx::ListaObiektow<SpEx::Statek>::przenies(r.front(), lista, listaDruga));
	UNIT_TEST_ASSERT_EQUAL(porownanie,listaDruga.pobierz(r.front())->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(1,listaDruga.rozmiar());
	listaDruga.wyczysc();
	UNIT_TEST_ASSERT_TRUE(listaDruga.pusty());
}

void ObiektListTest::koniecTestow(){
	lista.wyczysc();
	listaDruga.wyczysc();
}

REJESTRUJ_PACZKE_TESTOW(ObiektListTest);
