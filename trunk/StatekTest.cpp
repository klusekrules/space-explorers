#include "StatekTest.h"


StatekTest::StatekTest(void)
{
}

void StatekTest::startTestow(){
	planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(Identyfikator(0x4));
	UNIT_TEST_ASSERT_NOTNULL(planeta);
	planeta->wyczyscZawartoscPlanety();
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika(planeta->pobierzIdentyfikator()));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(12),Poziom(1)),Ilosc(2)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(13),Poziom(1)),Ilosc(1)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(14),Poziom(1)),Ilosc(1)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(11),Poziom(1)),Ilosc(8)) );
	a = &(planeta->pobierzStatek(Planeta::Indeks(Identyfikator(12),Poziom(1))));
	b = &(planeta->pobierzStatek(Planeta::Indeks(Identyfikator(13),Poziom(4))));
	c = &(planeta->pobierzStatek(Planeta::Indeks(Identyfikator(14),Poziom(2))));
	d = &(planeta->pobierzStatek(Planeta::Indeks(Identyfikator(11),Poziom(1))));
}

void StatekTest::Issue42Test(){
	UNIT_TEST_ASSERT_EQUAL( Masa(4+14), a->pobierzMase() );
	UNIT_TEST_ASSERT_EQUAL( Objetosc(540), a->pobierzObjetosc() );
	UNIT_TEST_ASSERT_EQUAL( Powierzchnia(8), a->pobierzPowierzchnie() );
	UNIT_TEST_ASSERT_EQUAL( Objetosc(1300*12*2), a->pobierzPojemnoscMaksymalnaLadowni() );
	UNIT_TEST_ASSERT_EQUAL( ZuzyciePaliwa(12),a->pobierzJednostkoweZuzyciePaliwa() );
	UNIT_TEST_ASSERT_EQUAL( Moc(5), a->pobierzMocSilnika() );
	UNIT_TEST_ASSERT_EQUAL( Fluktuacja(0.97f*8.0f), a->pobierzSprawnoscSilnika() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(9.0*90*2), a->pobierzAtak() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(10.0*250*2), a->pobierzPancerz() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(11.0*300*2), a->pobierzOslone() );
}

void StatekTest::Issue52Test(){
	UNIT_TEST_ASSERT_EQUAL( Poziom(4), b->pobierzPoziom() );
	UNIT_TEST_ASSERT_EQUAL( Poziom(2), c->pobierzPoziom() );
}

void StatekTest::FlotaTest(){	
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(0x1),Poziom(1)),Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(0x4),Poziom(1)),Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(0x7),Poziom(1)),Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(0xB),Poziom(1)),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(c->ID()),Ilosc(3800)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Planeta::Indeks(Identyfikator(0xC),Poziom(1)),Ilosc(3800)));

	auto idFlotyDo = planeta->dodajFlote();
	Ilosc obiektA = planeta->pobierzObiekt(Identyfikator(0xB)).pobierzIlosc();
	Ilosc obiektB = planeta->pobierzObiekt(Identyfikator(0xC)).pobierzIlosc();
	Ilosc obiektC = planeta->pobierzObiekt(Identyfikator(0x1)).pobierzIlosc();
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFlotyDo,Planeta::Indeks(Identyfikator(0xB),Poziom(1)),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFlotyDo,Planeta::Indeks(c->ID()),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujSurowceNaFlote(idFlotyDo,Planeta::Indeks(Identyfikator(0x1),Poziom(1)),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujStatekNaFlote(idFlotyDo,Planeta::Indeks(Identyfikator(0xC),Poziom(1)),Ilosc(900)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzFlote(idFlotyDo)->rozladujFloteNaPlanecie() );
	planeta->pobierzFlote(idFlotyDo)->ustawCelPodrozy(Flota::CelPodrozy::Transport);
	planeta->pobierzFlote(idFlotyDo)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFlotyDo)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzFlote(idFlotyDo)->rozladujFloteNaPlanecie() );
	UNIT_TEST_ASSERT_EQUAL( obiektA, planeta->pobierzObiekt(Identyfikator(0xB)).pobierzIlosc() );
	UNIT_TEST_ASSERT_EQUAL( obiektB, planeta->pobierzObiekt(Identyfikator(0xC)).pobierzIlosc() );
	UNIT_TEST_ASSERT_EQUAL( obiektC, planeta->pobierzObiekt(Identyfikator(0x1)).pobierzIlosc() );
	UNIT_TEST_ASSERT_TRUE( planeta->usunFlote(idFlotyDo) );

	auto idFloty = planeta->dodajFlote();
	planeta->pobierzFlote(idFloty)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFloty)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFloty,Planeta::Indeks(Identyfikator(0xB),Poziom(1)),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFloty,Planeta::Indeks(c->ID()),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujSurowceNaFlote(idFloty,Planeta::Indeks(Identyfikator(0x1),Poziom(1)),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujStatekNaFlote(idFloty,Planeta::Indeks(Identyfikator(0xC),Poziom(1)),Ilosc(900)));

	obiektA = planeta->pobierzObiekt(Identyfikator(0xB)).pobierzIlosc();
	obiektB = planeta->pobierzObiekt(Identyfikator(0xC)).pobierzIlosc();
	obiektC = planeta->pobierzObiekt(Identyfikator(0x1)).pobierzIlosc();
	auto idFlotyDoRozladunku = planeta->dodajFlote();
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFlotyDoRozladunku,Planeta::Indeks(Identyfikator(0xB),Poziom(1)),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFlotyDoRozladunku,Planeta::Indeks(c->ID()),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujSurowceNaFlote(idFlotyDoRozladunku,Planeta::Indeks(Identyfikator(0x1),Poziom(1)),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujStatekNaFlote(idFlotyDoRozladunku,Planeta::Indeks(Identyfikator(0xC),Poziom(1)),Ilosc(900)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzFlote(idFlotyDoRozladunku)->rozladujLadownieNaPlanecie() );
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawCelPodrozy(Flota::CelPodrozy::Transport);
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzFlote(idFlotyDoRozladunku)->rozladujLadownieNaPlanecie() );
	UNIT_TEST_ASSERT_EQUAL( obiektA, planeta->pobierzObiekt(Identyfikator(0xB)).pobierzIlosc()+Ilosc(500) );
	UNIT_TEST_ASSERT_EQUAL( obiektB, planeta->pobierzObiekt(Identyfikator(0xC)).pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL( obiektC, planeta->pobierzObiekt(Identyfikator(0x1)).pobierzIlosc() );
}

StatekTest::~StatekTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(StatekTest);
