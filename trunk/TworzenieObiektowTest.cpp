#include "TworzenieObiektowTest.h"


TworzenieObiektowTest::TworzenieObiektowTest()
{
}

void TworzenieObiektowTest::startTestow(){
	gra = &(Aplikacja::getInstance().getGra());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	id = gra->generujPlanete();
	UNIT_TEST_ASSERT_TRUE(gra->przeniesPlaneteDoUzytkownika(id));
	planeta = &(gra->getUzytkownik().pobierzPlanete(id));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
}

void TworzenieObiektowTest::tworzenieObiektow(){
	for(int i = 1 ; i <= 0x13 ; ++i ){
		UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Identyfikator(i),Ilosc(100)));
		UNIT_TEST_ASSERT_NOTEQUAL( Identyfikator(0) , planeta->pobierzObiekt(Identyfikator(i)).pobierzIdentyfikator() );
	}
}

void TworzenieObiektowTest::falszyweObiekty(){
	for(int i = 0xffff ; i>=0xfff0 ; --i ){
		UNIT_TEST_ASSERT_FALSE(planeta->wybuduj(Identyfikator(i),Ilosc(100)));
		UNIT_TEST_ASSERT_EQUAL( Identyfikator(0) , planeta->pobierzObiekt(Identyfikator(i)).pobierzIdentyfikator() );
	}
}

TworzenieObiektowTest::~TworzenieObiektowTest()
{
}
