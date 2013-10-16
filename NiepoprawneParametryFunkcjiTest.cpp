#include "NiepoprawneParametryFunkcjiTest.h"


NiepoprawneParametryFunkcjiTest::NiepoprawneParametryFunkcjiTest(void)
{
}

void NiepoprawneParametryFunkcjiTest::startTestow(){
	Gra* gra = &(Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(Identyfikator(0x7));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	UNIT_TEST_ASSERT_TRUE(gra->przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(Planeta::Indeks(Identyfikator(0xC),Poziom(1)),Ilosc(100)));
}

void NiepoprawneParametryFunkcjiTest::tworzenieWyjatku(){
	try{
		Ilosc temp(5);
		const Statek& tmp = planeta->pobierzStatek(Planeta::Indeks(Identyfikator(0xC),Poziom(1)));
		throw NiepoprawneParametryFunkcji( EXCEPTION_PLACE , tmp , temp );
	}catch( const NiepoprawneParametryFunkcji& e ){
		UNIT_TEST_ASSERT_FALSE(e.getParametry().isEmpty());
	}
}

NiepoprawneParametryFunkcjiTest::~NiepoprawneParametryFunkcjiTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(NiepoprawneParametryFunkcjiTest);
