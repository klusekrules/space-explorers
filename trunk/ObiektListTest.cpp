#include "ObiektListTest.h"


ObiektListTest::ObiektListTest(void)
{
}

void ObiektListTest::startTestow(){
	Gra& gra = Aplikacja::getInstance().getGra();
	a = shared_ptr<Statek>(gra.pobierzStatek(Identyfikator(11)).tworzEgzemplarz(Ilosc(8),Identyfikator(0)));
	b = shared_ptr<Statek>(gra.pobierzStatek(Identyfikator(12)).tworzEgzemplarz(Ilosc(8),Identyfikator(0)));
	c = shared_ptr<Statek>(gra.pobierzStatek(Identyfikator(13)).tworzEgzemplarz(Ilosc(8),Identyfikator(0)));
	d = shared_ptr<Statek>(gra.pobierzStatek(Identyfikator(14)).tworzEgzemplarz(Ilosc(8),Identyfikator(0)));
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
	Statek& sTmp1 = *lista.pobierz(Klucz(Identyfikator( 12 ),Poziom( 1 )));
	UNIT_TEST_ASSERT_EQUAL(Identyfikator( 12 ),sTmp1.pobierzIdentyfikator());
	UNIT_TEST_ASSERT_EQUAL(Poziom( 1 ),sTmp1.pobierzPoziom());
	UNIT_TEST_ASSERT_TRUE(lista.usun(Klucz(Identyfikator( 11 ),Poziom( 1 ))));
	shared_ptr<Statek> sTmp2 = lista.wyjmij(Klucz(Identyfikator( 14 ),Poziom( 2 )));
	UNIT_TEST_ASSERT_EQUAL(Identyfikator( 14 ),sTmp2->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_EQUAL(Poziom( 2 ),sTmp2->pobierzPoziom());
	l = lista.listaObiektow();
	UNIT_TEST_ASSERT_FALSE(l.empty());
	r = lista.listaKluczy();
	UNIT_TEST_ASSERT_FALSE(r.empty());
	UNIT_TEST_ASSERT_TRUE(ListaObiektow<Statek>::przenies(r.front(),Ilosc(1),lista,listaDruga));
	Ilosc porownanie = lista.pobierz(r.front())->pobierzIlosc() + listaDruga.pobierz(r.front())->pobierzIlosc();
	UNIT_TEST_ASSERT_EQUAL(1,listaDruga.rozmiar());
	UNIT_TEST_ASSERT_TRUE(ListaObiektow<Statek>::przenies(r.front(),lista,listaDruga));
	UNIT_TEST_ASSERT_EQUAL(porownanie,listaDruga.pobierz(r.front())->pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(1,listaDruga.rozmiar());
	listaDruga.wyczysc();
	UNIT_TEST_ASSERT_TRUE(listaDruga.pusty());
}

ObiektListTest::~ObiektListTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(ObiektListTest);
