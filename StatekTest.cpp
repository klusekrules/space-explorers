#include "StatekTest.h"

void StatekTest::startTestow(){
	planeta = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(0x4));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(12), STyp::Ilosc(2)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(13), STyp::Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(14), STyp::Ilosc(1)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(11), STyp::Ilosc(8)));
	a = &(planeta->pobierzStatek(STyp::Identyfikator(12)));
	b = &(planeta->pobierzStatek(STyp::Identyfikator(13)));
	c = &(planeta->pobierzStatek(STyp::Identyfikator(14)));
	d = &(planeta->pobierzStatek(STyp::Identyfikator(11)));
}

void StatekTest::Issue42Test(){
	UNIT_TEST_ASSERT_EQUAL(STyp::Masa(4 + 14), a->pobierzMase());
	UNIT_TEST_ASSERT_EQUAL(STyp::Powierzchnia(8), a->pobierzPowierzchnie());
	UNIT_TEST_ASSERT_EQUAL(STyp::Objetosc(1300 * 12 * 2), a->pobierzPojemnoscMaksymalnaLadowni());
	UNIT_TEST_ASSERT_EQUAL(STyp::ZuzyciePaliwa(12), a->pobierzJednostkoweZuzyciePaliwa());
	UNIT_TEST_ASSERT_EQUAL(STyp::Moc(5), a->pobierzMocSilnika());
	UNIT_TEST_ASSERT_EQUAL(STyp::Fluktuacja(0.97f*8.0f), a->pobierzSprawnoscSilnika());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(9.0 * 90 * 2), a->pobierzAtak());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(10.0 * 250 * 2), a->pobierzPancerz());
	UNIT_TEST_ASSERT_EQUAL(STyp::Obrazenia(11.0 * 300 * 2), a->pobierzOslone());
}

void StatekTest::Issue52Test(){
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(4), b->pobierzPoziom());
	UNIT_TEST_ASSERT_EQUAL(STyp::Poziom(2), c->pobierzPoziom());
}

void StatekTest::FlotaTest(){	
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x1), STyp::Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x4), STyp::Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0x7), STyp::Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0xB), STyp::Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(c->pobierzIdentyfikator(), STyp::Ilosc(3800)));
	UNIT_TEST_ASSERT_TRUE(planeta->wybuduj(STyp::Identyfikator(0xC), STyp::Ilosc(3800)));

	auto idFlotyDo = planeta->dodajFlote();
	STyp::Ilosc obiektA = planeta->pobierzObiekt(STyp::Identyfikator(0xB)).pobierzIlosc();
	STyp::Ilosc obiektB = planeta->pobierzObiekt(STyp::Identyfikator(0xC)).pobierzIlosc();
	STyp::Ilosc obiektC = planeta->pobierzObiekt(STyp::Identyfikator(0x1)).pobierzIlosc();
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFlotyDo, STyp::Identyfikator(0xB), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFlotyDo, c->pobierzIdentyfikator(), STyp::Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujSurowceNaFlote(idFlotyDo, STyp::Identyfikator(0x1), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujStatekNaFlote(idFlotyDo, STyp::Identyfikator(0xC), STyp::Ilosc(900)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzFlote(idFlotyDo)->rozladujFloteNaPlanecie() );
	planeta->pobierzFlote(idFlotyDo)->ustawCelPodrozy(SpEx::Flota::CelPodrozy::Transport);
	planeta->pobierzFlote(idFlotyDo)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFlotyDo)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzFlote(idFlotyDo)->rozladujFloteNaPlanecie() );
	UNIT_TEST_ASSERT_EQUAL(obiektA, planeta->pobierzObiekt(STyp::Identyfikator(0xB)).pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(obiektB, planeta->pobierzObiekt(STyp::Identyfikator(0xC)).pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(obiektC, planeta->pobierzObiekt(STyp::Identyfikator(0x1)).pobierzIlosc());
	UNIT_TEST_ASSERT_TRUE( planeta->usunFlote(idFlotyDo) );

	auto idFloty = planeta->dodajFlote();
	planeta->pobierzFlote(idFloty)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFloty)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFloty, STyp::Identyfikator(0xB), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFloty, c->pobierzIdentyfikator(), STyp::Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujSurowceNaFlote(idFloty, STyp::Identyfikator(0x1), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujStatekNaFlote(idFloty, STyp::Identyfikator(0xC), STyp::Ilosc(900)));

	obiektA = planeta->pobierzObiekt(STyp::Identyfikator(0xB)).pobierzIlosc();
	obiektB = planeta->pobierzObiekt(STyp::Identyfikator(0xC)).pobierzIlosc();
	obiektC = planeta->pobierzObiekt(STyp::Identyfikator(0x1)).pobierzIlosc();
	auto idFlotyDoRozladunku = planeta->dodajFlote();
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFlotyDoRozladunku, STyp::Identyfikator(0xB), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->przeniesDoFloty(idFlotyDoRozladunku, c->pobierzIdentyfikator(), STyp::Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujSurowceNaFlote(idFlotyDoRozladunku, STyp::Identyfikator(0x1), STyp::Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE(planeta->zaladujStatekNaFlote(idFlotyDoRozladunku, STyp::Identyfikator(0xC), STyp::Ilosc(900)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzFlote(idFlotyDoRozladunku)->rozladujLadownieNaPlanecie() );
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawCelPodrozy(SpEx::Flota::CelPodrozy::Transport);
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzFlote(idFlotyDoRozladunku)->rozladujLadownieNaPlanecie() );
	UNIT_TEST_ASSERT_EQUAL(obiektA, planeta->pobierzObiekt(STyp::Identyfikator(0xB)).pobierzIlosc() + STyp::Ilosc(500));
	UNIT_TEST_ASSERT_EQUAL(obiektB, planeta->pobierzObiekt(STyp::Identyfikator(0xC)).pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(obiektC, planeta->pobierzObiekt(STyp::Identyfikator(0x1)).pobierzIlosc());
}

//REJESTRUJ_PACZKE_TESTOW(StatekTest);
