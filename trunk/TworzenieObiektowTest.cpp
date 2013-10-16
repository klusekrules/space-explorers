#include "TworzenieObiektowTest.h"


TworzenieObiektowTest::TworzenieObiektowTest()
{
}

void TworzenieObiektowTest::startTestow(){
	gra = &(Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	planeta = gra->pobierzPlanete(Identyfikator(0x2));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	UNIT_TEST_ASSERT_TRUE(gra->przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
}

void TworzenieObiektowTest::tworzenieObiektow(){
	for(int i = 1 ; i <= 0x13 ; ++i ){
		UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(i),Poziom(1)),Ilosc(100)));
		UNIT_TEST_ASSERT_NOTEQUAL( Identyfikator(0) , planeta->pobierzObiekt(Identyfikator(i)).pobierzIdentyfikator() );
	}
}

void TworzenieObiektowTest::falszyweObiekty(){
	for(int i = 0xffff ; i>=0xfff0 ; --i ){
		UNIT_TEST_ASSERT_FALSE(planeta->wybuduj(Planeta::Indeks(Identyfikator(i),Poziom(1)),Ilosc(100)));
		UNIT_TEST_ASSERT_EQUAL( Identyfikator(0) , planeta->pobierzObiekt(Planeta::Indeks(Identyfikator(i),Poziom(1))).pobierzIdentyfikator() );
	}
}

TworzenieObiektowTest::~TworzenieObiektowTest()
{
}
