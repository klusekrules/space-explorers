#include "TworzenieObiektowTest.h"

void TworzenieObiektowTest::startTestow(){
	gra = &(SpEx::Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	planeta = gra->pobierzPlanete(STyp::Identyfikator(0x2));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(gra->przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
}

void TworzenieObiektowTest::tworzenieObiektow(){
	for(int i = 1 ; i <= 8 ; ++i ){
		UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(i), SpEx::PodstawoweParametry(STyp::Ilosc(100))));
		UNIT_TEST_ASSERT_NOTEQUAL(STyp::Identyfikator(0), planeta->pobierzObiekt(STyp::Identyfikator(i)).pobierzIdentyfikator());
	}
}

void TworzenieObiektowTest::falszyweObiekty(){
	for(int i = 0xffff ; i>=0xfff0 ; --i ){
		try{
			UNIT_TEST_ASSERT_FALSE(planeta->wybuduj(STyp::Identyfikator(i), SpEx::PodstawoweParametry(STyp::Ilosc(100))));
			UNIT_TEST_ASSERT_EQUAL(STyp::Identyfikator(0), planeta->pobierzObiekt(STyp::Identyfikator(i)).pobierzIdentyfikator());
		}
		catch (STyp::Wyjatek&){

		}
	}
}
