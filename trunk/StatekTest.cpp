#include "StatekTest.h"

void StatekTest::startTestow(){
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x4));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(5), STyp::Ilosc(2)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(6), STyp::Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(7), STyp::Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(8), STyp::Ilosc(8)));
	a = &(planeta->pobierzStatek(STyp::Identyfikator(5)));
	b = &(planeta->pobierzStatek(STyp::Identyfikator(6)));
	c = &(planeta->pobierzStatek(STyp::Identyfikator(7)));
	d = &(planeta->pobierzStatek(STyp::Identyfikator(8)));
}

void StatekTest::Issue42Test(){
	UNIT_TEST_ASSERT_EQUAL(STyp::Masa(560*2 + 40*2), a->pobierzMase());
	UNIT_TEST_ASSERT_EQUAL(STyp::Powierzchnia(120*2), a->pobierzPowierzchnie());
	UNIT_TEST_ASSERT_EQUAL(STyp::Objetosc(500 * 2), a->pobierzPojemnoscMaksymalnaLadowni());
	UNIT_TEST_ASSERT_EQUAL(STyp::Powierzchnia(0), a->pobierzPojemnoscMaksymalnaHangaru());
	UNIT_TEST_ASSERT_EQUAL(STyp::ZuzyciePaliwa(300*2), a->pobierzJednostkoweZuzyciePaliwa());
	UNIT_TEST_ASSERT_EQUAL(STyp::Moc(500), a->pobierzMocSilnika());
	UNIT_TEST_ASSERT_EQUAL(STyp::Fluktuacja(0.7f), a->pobierzSprawnoscSilnika());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(50 * 2), a->pobierzAtak());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(130 * 2), a->pobierzPancerz());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(40 * 2), a->pobierzOslone());
}

void StatekTest::FlotaTest(){	
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(1), STyp::Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(2), STyp::Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(3), STyp::Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(5), STyp::Ilosc(38)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(6), STyp::Ilosc(38)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(7), STyp::Ilosc(38)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(8), STyp::Ilosc(38)));

	auto idFlotyDo = planeta->dodajFlote();
	STyp::Ilosc obiektA = planeta->pobierzObiekt(STyp::Identyfikator(5)).pobierzIlosc();
	STyp::Ilosc obiektB = planeta->pobierzObiekt(STyp::Identyfikator(6)).pobierzIlosc();
	STyp::Ilosc obiektC = planeta->pobierzObiekt(STyp::Identyfikator(1)).pobierzIlosc();

	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFlotyDo, STyp::Identyfikator(5), STyp::Ilosc(10)));
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFlotyDo, STyp::Identyfikator(6), STyp::Ilosc(10)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujSurowceNaFlote(idFlotyDo, STyp::Identyfikator(1), STyp::Ilosc(5000)));
	UNIT_TEST_ASSERT_FALSE(planeta->zaladujStatekNaFlote(idFlotyDo, STyp::Identyfikator(7), STyp::Ilosc(1)));

	UNIT_TEST_ASSERT_NOTEQUAL(obiektA, planeta->pobierzObiekt(STyp::Identyfikator(5)).pobierzIlosc());
	UNIT_TEST_ASSERT_NOTEQUAL(obiektB, planeta->pobierzObiekt(STyp::Identyfikator(6)).pobierzIlosc());
	UNIT_TEST_ASSERT_NOTEQUAL(obiektC, planeta->pobierzObiekt(STyp::Identyfikator(1)).pobierzIlosc());

	UNIT_TEST_ASSERT_FALSE( planeta->pobierzFlote(idFlotyDo)->rozladujFloteNaPlanecie() );

	planeta->pobierzFlote(idFlotyDo)->ustawCelPodrozy(SpEx::Flota::CelPodrozy::Transport);
	planeta->pobierzFlote(idFlotyDo)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFlotyDo)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzFlote(idFlotyDo)->rozladujFloteNaPlanecie() );

	UNIT_TEST_ASSERT_EQUAL(obiektA, planeta->pobierzObiekt(STyp::Identyfikator(5)).pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(obiektB, planeta->pobierzObiekt(STyp::Identyfikator(6)).pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(obiektC, planeta->pobierzObiekt(STyp::Identyfikator(1)).pobierzIlosc());
	UNIT_TEST_ASSERT_TRUE( planeta->usunFlote(idFlotyDo) );

	auto idFloty = planeta->dodajFlote();
	planeta->pobierzFlote(idFloty)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFloty)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFloty, STyp::Identyfikator(6), STyp::Ilosc(10)));
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFloty, STyp::Identyfikator(8), STyp::Ilosc(10)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujSurowceNaFlote(idFloty, STyp::Identyfikator(1), STyp::Ilosc(5000)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujStatekNaFlote(idFloty, STyp::Identyfikator(7), STyp::Ilosc(30)));
	
	obiektA = planeta->pobierzObiekt(STyp::Identyfikator(3)).pobierzIlosc();
	obiektB = planeta->pobierzObiekt(STyp::Identyfikator(5)).pobierzIlosc();
	obiektC = planeta->pobierzObiekt(STyp::Identyfikator(8)).pobierzIlosc();

	auto idFlotyDoRozladunku = planeta->dodajFlote();
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFlotyDoRozladunku, STyp::Identyfikator(6), STyp::Ilosc(10)));
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFlotyDoRozladunku, STyp::Identyfikator(8), STyp::Ilosc(10)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujSurowceNaFlote(idFlotyDoRozladunku, STyp::Identyfikator(3), STyp::Ilosc(3000)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujStatekNaFlote(idFlotyDoRozladunku, STyp::Identyfikator(5), STyp::Ilosc(20)));

	UNIT_TEST_ASSERT_FALSE( planeta->pobierzFlote(idFlotyDoRozladunku)->rozladujLadownieNaPlanecie() );

	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawCelPodrozy(SpEx::Flota::CelPodrozy::Transport);
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzFlote(idFlotyDoRozladunku)->rozladujLadownieNaPlanecie() );

	UNIT_TEST_ASSERT_EQUAL(obiektA, planeta->pobierzObiekt(STyp::Identyfikator(3)).pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(obiektB, planeta->pobierzObiekt(STyp::Identyfikator(5)).pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(obiektC, planeta->pobierzObiekt(STyp::Identyfikator(8)).pobierzIlosc() + STyp::Ilosc(10) );
}

REJESTRUJ_PACZKE_TESTOW(StatekTest);
