#include "NiepoprawneParametryFunkcjiTest.h"

void NiepoprawneParametryFunkcjiTest::startTestow(){
	SpEx::Gra* gra = &(SpEx::Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x7));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(gra->przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(SpEx::Planeta::Indeks(STyp::Identyfikator(0xC)), STyp::Ilosc(100)));
}

void NiepoprawneParametryFunkcjiTest::tworzenieWyjatku(){
	try{
		STyp::Ilosc temp(5);
		const SpEx::Statek& tmp = planeta->pobierzStatek(STyp::Identyfikator(0xC));
		throw SpEx::NiepoprawneParametryFunkcji(EXCEPTION_PLACE, STyp::Tekst() , tmp, temp);
	}
	catch (const SpEx::NiepoprawneParametryFunkcji& e){
		UNIT_TEST_ASSERT_FALSE(e.getParametry().isEmpty());
	}
}

REJESTRUJ_PACZKE_TESTOW(NiepoprawneParametryFunkcjiTest);
