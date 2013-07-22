#include "ObiektListTest.h"


ObiektListTest::ObiektListTest(void)
{
}

void ObiektListTest::startTestow(){
	Gra& gra = Aplikacja::getInstance().getGra();
	a = gra.getStatek(Identyfikator(11)).tworzEgzemplarz(Ilosc(8),Identyfikator(0));
	b = gra.getStatek(Identyfikator(12)).tworzEgzemplarz(Ilosc(8),Identyfikator(0));
	c = gra.getStatek(Identyfikator(13)).tworzEgzemplarz(Ilosc(8),Identyfikator(0));
	d = gra.getStatek(Identyfikator(14)).tworzEgzemplarz(Ilosc(8),Identyfikator(0));
	UNIT_TEST_ASSERT_NOTNULL(a);
	UNIT_TEST_ASSERT_NOTNULL(b);
	UNIT_TEST_ASSERT_NOTNULL(c);
	UNIT_TEST_ASSERT_NOTNULL(d);
}

void ObiektListTest::podstawowyTest(){
	lista.add(a);
	lista.add(b);
	lista.add(c);
	lista.add(d);
	auto l = lista.rawObiektList();
	UNIT_TEST_ASSERT_FALSE(l.empty());
	auto r = lista.rawKluczList();
	UNIT_TEST_ASSERT_FALSE(r.empty());
	Statek& sTmp1 = lista.get(Klucz(Identyfikator( 12 ),Poziom( 1 )));
	UNIT_TEST_ASSERT_EQUAL(Identyfikator( 12 ),sTmp1.pobierzIdentyfikator());
	UNIT_TEST_ASSERT_EQUAL(Poziom( 1 ),sTmp1.pobierzPoziom());
	UNIT_TEST_ASSERT_TRUE(lista.del(Klucz(Identyfikator( 11 ),Poziom( 1 ))));
	Statek* sTmp2 = lista.getAndDel(Klucz(Identyfikator( 14 ),Poziom( 2 )));
	UNIT_TEST_ASSERT_EQUAL(Identyfikator( 14 ),sTmp2->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_EQUAL(Poziom( 2 ),sTmp2->pobierzPoziom());
	delete sTmp2;
	l = lista.rawObiektList();
	UNIT_TEST_ASSERT_FALSE(l.empty());
	r = lista.rawKluczList();
	UNIT_TEST_ASSERT_FALSE(r.empty());
	ObiektList<Statek>::move(r.front(),Ilosc(1),lista,listaDruga);
	UNIT_TEST_ASSERT_EQUAL(1,listaDruga.size());
	ObiektList<Statek>::move(r.front(),lista,listaDruga);
	UNIT_TEST_ASSERT_EQUAL(1,listaDruga.size());
	listaDruga.clear();
	UNIT_TEST_ASSERT_TRUE(listaDruga.isEmpty());
}

ObiektListTest::~ObiektListTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(ObiektListTest);
