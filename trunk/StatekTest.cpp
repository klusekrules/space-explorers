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
	UNIT_TEST_ASSERT_EQUAL( Masa(4+14), a->getMasa() );
	UNIT_TEST_ASSERT_EQUAL( Objetosc(540), a->getObjetosc() );
	UNIT_TEST_ASSERT_EQUAL( Powierzchnia(8), a->getPowierzchnia() );
	UNIT_TEST_ASSERT_EQUAL( Objetosc(1300*12*2), a->getPojemnoscMax() );
	UNIT_TEST_ASSERT_EQUAL( ZuzyciePaliwa(12),a->getJednostkoweZuzyciePaliwa() );
	UNIT_TEST_ASSERT_EQUAL( MocSilnika(5), a->getMocSilnika() );
	UNIT_TEST_ASSERT_EQUAL( Fluktuacja(0.97f*8.0f), a->getSprawnoscSilnika() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(9.0*90*2), a->getAtak() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(10.0*250*2), a->getPancerz() );
	UNIT_TEST_ASSERT_EQUAL( Obrazenia(11.0*300*2), a->getOslona() );
}

void StatekTest::Issue52Test(){
	UNIT_TEST_ASSERT_EQUAL( Poziom(4), b->pobierzPoziom() );
	UNIT_TEST_ASSERT_EQUAL( Poziom(2), c->pobierzPoziom() );
}

void StatekTest::JednostkaAtakujacaTest(){
	Obrazenia oAtak = d->Atak();
	Obrazenia baseAtak(d->getStatekInfo().getAtak(PodstawoweParametry(Poziom(1),Identyfikator()))()*8.0);
	Obrazenia tbAtak(baseAtak() *(JednostkaAtakujaca::srednia-(JednostkaAtakujaca::odchylenie * 3 )));
	Obrazenia teAtak(baseAtak() *(JednostkaAtakujaca::srednia+(JednostkaAtakujaca::odchylenie * 3 )));
	UNIT_TEST_ASSERT_TRUE( (tbAtak <= oAtak && oAtak <= teAtak) );

	Obrazenia oOslona = d->Oslona(oAtak);
	Obrazenia baseOslona(d->getStatekInfo().getOslona(PodstawoweParametry(Poziom(1),Identyfikator()))()*8.0);
	double tbd=oAtak() - baseOslona() *(JednostkaAtakujaca::srednia+(JednostkaAtakujaca::odchylenie * 3 ));
	double ted=oAtak() - baseOslona() *(JednostkaAtakujaca::srednia-(JednostkaAtakujaca::odchylenie * 3 ));
	Obrazenia tbOslona(tbd>0?tbd:0);
	Obrazenia teOslona(ted>0?ted:0);
	UNIT_TEST_ASSERT_TRUE( (tbOslona <= oOslona && oOslona <= teOslona) );

	Obrazenia oPancerz = d->Pancerz(oOslona);
	Obrazenia basePancerz(d->getStatekInfo().getPancerz(PodstawoweParametry(Poziom(1),Identyfikator()))()*8.0);
	Obrazenia tbPancerz(basePancerz<oOslona?oOslona-basePancerz:Obrazenia(0));
	UNIT_TEST_ASSERT_EQUAL( tbPancerz , oPancerz );
}

void StatekTest::FlotaTest(){	
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x1),Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x4),Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0x7),Ilosc(20000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0xB),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE( planeta->wybuduj(Identyfikator(0xE),Ilosc(2000)));
	auto idFloty = planeta->dodajFlote();
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFloty,Identyfikator(0xB),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->przeniesDoFloty(idFloty,Identyfikator(0xE),Ilosc(1000)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujFlote(idFloty,Identyfikator(0x1),Ilosc(500)));
	UNIT_TEST_ASSERT_TRUE( planeta->zaladujFlote(idFloty,Identyfikator(0xE),Ilosc(900)));

}

StatekTest::~StatekTest(void)
{
}

REJESTRUJ_PACZKE_TESTOW(StatekTest);
