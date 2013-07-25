#include "StatekTest.h"


StatekTest::StatekTest(void)
{
}

void StatekTest::startTestow(){
	auto idPlanety = Aplikacja::getInstance().getGra().generujPlanete();
	UNIT_TEST_ASSERT_TRUE(Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(idPlanety));
	planeta = &(Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(idPlanety));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(12),Ilosc(2)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(13),Ilosc(1)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(14),Ilosc(1)) );
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(11),Ilosc(8)) );
	a = &(planeta->pobierzStatek(Identyfikator(12)));
	b = &(planeta->pobierzStatek(Identyfikator(13)));
	c = &(planeta->pobierzStatek(Identyfikator(14)));
	d = &(planeta->pobierzStatek(Identyfikator(11)));
}

void StatekTest::Issue42Test(){
	UNIT_TEST_ASSERT_EQUAL( Masa(4+14), a->pobierzMase() );
	UNIT_TEST_ASSERT_EQUAL( Objetosc(540), a->pobierzObjetosc() );
	UNIT_TEST_ASSERT_EQUAL( Powierzchnia(8), a->pobierzPowierzchnie() );
	UNIT_TEST_ASSERT_EQUAL( Objetosc(1300*12*2), a->pobierzPojemnoscMaksymalna() );
	UNIT_TEST_ASSERT_EQUAL( ZuzyciePaliwa(12),a->pobierzJednostkoweZuzyciePaliwa() );
	UNIT_TEST_ASSERT_EQUAL( MocSilnika(5), a->pobierzMocSilnika() );
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
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x1),Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x4),Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x7),Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0xB),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0xE),Ilosc(3800)));

	auto idFlotyDo = planeta->dodajFlote();
	Ilosc obiektA = planeta->pobierzObiekt(Identyfikator(0xB)).pobierzIlosc();
	Ilosc obiektB = planeta->pobierzObiekt(Identyfikator(0xE)).pobierzIlosc();
	Ilosc obiektC = planeta->pobierzObiekt(Identyfikator(0x1)).pobierzIlosc();
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFlotyDo,Identyfikator(0xB),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFlotyDo,Identyfikator(0xE),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujFlote(idFlotyDo,Identyfikator(0x1),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujFlote(idFlotyDo,Identyfikator(0xE),Ilosc(900)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzFlote(idFlotyDo)->rozladujFloteNaPlanecie() );
	planeta->pobierzFlote(idFlotyDo)->ustawCelPodrozy(Flota::CelPodrozy::Transport);
	planeta->pobierzFlote(idFlotyDo)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFlotyDo)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzFlote(idFlotyDo)->rozladujFloteNaPlanecie() );
	UNIT_TEST_ASSERT_EQUAL( obiektA, planeta->pobierzObiekt(Identyfikator(0xB)).pobierzIlosc() );
	UNIT_TEST_ASSERT_EQUAL( obiektB, planeta->pobierzObiekt(Identyfikator(0xE)).pobierzIlosc() );
	UNIT_TEST_ASSERT_EQUAL( obiektC, planeta->pobierzObiekt(Identyfikator(0x1)).pobierzIlosc() );
	UNIT_TEST_ASSERT_TRUE( planeta->usunFlote(idFlotyDo) );

	auto idFloty = planeta->dodajFlote();
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFloty,Identyfikator(0xB),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFloty,Identyfikator(0xE),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujFlote(idFloty,Identyfikator(0x1),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujFlote(idFloty,Identyfikator(0xE),Ilosc(900)));

	obiektA = planeta->pobierzObiekt(Identyfikator(0xB)).pobierzIlosc();
	obiektB = planeta->pobierzObiekt(Identyfikator(0xE)).pobierzIlosc();
	obiektC = planeta->pobierzObiekt(Identyfikator(0x1)).pobierzIlosc();
	auto idFlotyDoRozladunku = planeta->dodajFlote();
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFlotyDoRozladunku,Identyfikator(0xB),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFlotyDoRozladunku,Identyfikator(0xE),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujFlote(idFlotyDoRozladunku,Identyfikator(0x1),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujFlote(idFlotyDoRozladunku,Identyfikator(0xE),Ilosc(900)));
	UNIT_TEST_ASSERT_FALSE( planeta->pobierzFlote(idFlotyDoRozladunku)->rozladujLadownieNaPlanecie() );
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawCelPodrozy(Flota::CelPodrozy::Transport);
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawPlaneteDocelowa(planeta->pobierzIdentyfikator());
	planeta->pobierzFlote(idFlotyDoRozladunku)->ustawPlanetePoczatkowa(planeta->pobierzIdentyfikator());
	UNIT_TEST_ASSERT_TRUE( planeta->pobierzFlote(idFlotyDoRozladunku)->rozladujLadownieNaPlanecie() );
	UNIT_TEST_ASSERT_EQUAL( obiektA, planeta->pobierzObiekt(Identyfikator(0xB)).pobierzIlosc()+Ilosc(500) );
	UNIT_TEST_ASSERT_EQUAL( obiektB, planeta->pobierzObiekt(Identyfikator(0xE)).pobierzIlosc()+Ilosc(1000) );
	UNIT_TEST_ASSERT_EQUAL( obiektC, planeta->pobierzObiekt(Identyfikator(0x1)).pobierzIlosc() );
}

StatekTest::~StatekTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(StatekTest);
