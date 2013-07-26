#include "NiepoprawneParametryFunkcjiTest.h"


NiepoprawneParametryFunkcjiTest::NiepoprawneParametryFunkcjiTest(void)
{
}

void NiepoprawneParametryFunkcjiTest::startTestow(){
	Gra* gra = &(Aplikacja::getInstance().getGra());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	Identyfikator id = gra->generujPlanete();
	UNIT_TEST_ASSERT_TRUE(gra->przeniesPlaneteDoUzytkownika(id));
	planeta = &(gra->getUzytkownik().pobierzPlanete(id));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Identyfikator(0xC),Ilosc(100)));
}

void NiepoprawneParametryFunkcjiTest::tworzenieWyjatku(){
	try{
		Ilosc temp(5);
		const Statek& tmp = planeta->pobierzStatek(Identyfikator(0xC));
		throw NiepoprawneParametryFunkcji( EXCEPTION_PLACE , tmp , temp );
	}catch( const NiepoprawneParametryFunkcji& e ){
		UNIT_TEST_ASSERT_FALSE(e.getParametry().isEmpty());
	}
}

NiepoprawneParametryFunkcjiTest::~NiepoprawneParametryFunkcjiTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(NiepoprawneParametryFunkcjiTest);
