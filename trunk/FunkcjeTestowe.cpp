#include "Test.h"
#include "Testy.h"

/*
bool test_wymagan( Test & t ){
	shared_ptr<Statek> a( tworzStatek(t,Identyfikator(11),Ilosc(8)) );
	auto tmp = a->PobierzKoszty();
	t.assert_false(EXCEPTION_PLACE,tmp[0]->getIlosc()==Ilosc(120000.0));
	t.assert_false(EXCEPTION_PLACE,tmp[1]->getIlosc()==Ilosc(4000.0));
	t.assert_false(EXCEPTION_PLACE,tmp[2]->getIlosc()==Ilosc(8*1*10*5*200));
	auto w = a->PobierzWarunki();
	t.assert_false(EXCEPTION_PLACE,w[0]->getPoziom()==Poziom(25));
	t.assert_false(EXCEPTION_PLACE,w[1]->getPoziom()==Poziom(5));
	return true;
}
/*
bool test_KlasaJednostkaAtakujaca( Test & t ){
	shared_ptr<Statek> a( tworzStatek(t,Identyfikator(11),Ilosc(8)) );
	Obrazenia oAtak = a->Atak();
	Obrazenia baseAtak(a->getStatekInfo().getAtak(PodstawoweParametry(Poziom(1),Identyfikator()))()*8.0);
	Obrazenia tbAtak(baseAtak() *(JednostkaAtakujaca::srednia-(JednostkaAtakujaca::odchylenie * 3 )));
	Obrazenia teAtak(baseAtak() *(JednostkaAtakujaca::srednia+(JednostkaAtakujaca::odchylenie * 3 )));
	Aplikacja::getInstance().getLog().debug(oAtak);
	Aplikacja::getInstance().getLog().debug(baseAtak);
	Aplikacja::getInstance().getLog().debug(tbAtak);
	Aplikacja::getInstance().getLog().debug(teAtak);
	t.assert_false(EXCEPTION_PLACE, tbAtak <= oAtak && oAtak <= teAtak);

	Obrazenia oOslona = a->Oslona(oAtak);
	Obrazenia baseOslona(a->getStatekInfo().getOslona(PodstawoweParametry(Poziom(1),Identyfikator()))()*8.0);
	double tbd=oAtak() - baseOslona() *(JednostkaAtakujaca::srednia+(JednostkaAtakujaca::odchylenie * 3 ));
	double ted=oAtak() - baseOslona() *(JednostkaAtakujaca::srednia-(JednostkaAtakujaca::odchylenie * 3 ));
	Obrazenia tbOslona(tbd>0?tbd:0);
	Obrazenia teOslona(ted>0?ted:0);
	Aplikacja::getInstance().getLog().debug(oOslona);
	Aplikacja::getInstance().getLog().debug(baseOslona);
	Aplikacja::getInstance().getLog().debug(tbOslona);
	Aplikacja::getInstance().getLog().debug(teOslona);
	t.assert_false(EXCEPTION_PLACE, tbOslona <= oOslona && oOslona <= teOslona);

	Obrazenia oPancerz = a->Pancerz(oOslona);
	Obrazenia basePancerz(a->getStatekInfo().getPancerz(PodstawoweParametry(Poziom(1),Identyfikator()))()*8.0);
	Obrazenia tbPancerz(basePancerz<oOslona?oOslona-basePancerz:Obrazenia(0));
	Aplikacja::getInstance().getLog().debug(oPancerz);
	Aplikacja::getInstance().getLog().debug(basePancerz);
	Aplikacja::getInstance().getLog().debug(tbPancerz);
	t.assert_false(EXCEPTION_PLACE, tbPancerz == oPancerz);
	return true;
}

bool test_Issue42( Test & t ){
	shared_ptr<Statek> a( tworzStatek(t,Identyfikator(12),Ilosc(2)) );
	t.assert_false(EXCEPTION_PLACE, a->getMasa() == Masa(4+14));
	t.assert_false(EXCEPTION_PLACE, a->getObjetosc() == Objetosc(6));
	t.assert_false(EXCEPTION_PLACE, a->getPowierzchnia() == Powierzchnia(8));
	t.assert_false(EXCEPTION_PLACE, a->getPojemnoscMax() == Objetosc(1300*12*2));
	t.assert_false(EXCEPTION_PLACE, a->getJednostkoweZuzyciePaliwa() == ZuzyciePaliwa(12));
	t.assert_false(EXCEPTION_PLACE, a->getMocSilnika() == MocSilnika(5));
	t.assert_false(EXCEPTION_PLACE, a->getSprawnoscSilnika() == Fluktuacja(0.97f*8.0f));
	t.assert_false(EXCEPTION_PLACE, a->getAtak() == Obrazenia(9.0*90*2));
	t.assert_false(EXCEPTION_PLACE, a->getPancerz() == Obrazenia(10.0*250*2));
	t.assert_false(EXCEPTION_PLACE, a->getOslona() == Obrazenia(11.0*300*2));
	return true;
}

bool test_Issue52( Test & t ){
	shared_ptr<Statek> a( tworzStatek(t,Identyfikator(13),Ilosc(1)) );
	t.assert_false(EXCEPTION_PLACE, a->getPoziom() == Poziom(4));
	shared_ptr<Statek> b( tworzStatek(t,Identyfikator(14),Ilosc(1)) );
	t.assert_false(EXCEPTION_PLACE, b->getPoziom() == Poziom(2));
	return true;
}

bool test_Technologie( Test & t ){
	shared_ptr<Technologia> a( tworzTechnologie(t,Identyfikator(15)) );
	Aplikacja::getInstance().getLog().debug(*a);
	shared_ptr<Technologia> b( tworzTechnologie(t,Identyfikator(16)) );
	Aplikacja::getInstance().getLog().debug(*b);
	return true;
}

bool test_Budynki( Test & t ){
	shared_ptr<Budynek> a( tworzBudynek(t,Identyfikator(17)) );
	a->setPoziom(Poziom(3));
	auto z = a->PobierzZapotrzebowanie();
	if(t.assert_false(EXCEPTION_PLACE, z.size()>0)){
		t.assert_false(EXCEPTION_PLACE, z[0]->getIlosc()==Ilosc(180));
		t.assert_false(EXCEPTION_PLACE, z[0]->getId()==Identyfikator(10));
	}
	auto p = a->PobierzProdukcje();
	if(t.assert_false(EXCEPTION_PLACE, p.size()>0)){
		t.assert_false(EXCEPTION_PLACE, p[0]->getIlosc()==Ilosc(6000));
		t.assert_false(EXCEPTION_PLACE, p[0]->getId()==Identyfikator(1));
	}

	shared_ptr<Budynek> b( tworzBudynek(t,Identyfikator(18)) );
	b->setPoziom(Poziom(2));
	p = b->PobierzProdukcje();
	if(t.assert_false(EXCEPTION_PLACE, p.size()>0)){
		t.assert_false(EXCEPTION_PLACE, p[0]->getIlosc()==Ilosc(6000));
		t.assert_false(EXCEPTION_PLACE, p[0]->getId()==Identyfikator(10));
	}
	z = b->PobierzZapotrzebowanie();
	t.assert_false(EXCEPTION_PLACE, z.size()==0);

	shared_ptr<Budynek> c( tworzBudynek(t,Identyfikator(19)) );
	c->setPoziom(Poziom(2));
	p = c->PobierzProdukcje();
	t.assert_false(EXCEPTION_PLACE, p.size()==0);
	z = c->PobierzZapotrzebowanie();
	t.assert_false(EXCEPTION_PLACE, z.size()==0);
	return true;
}

bool test_Issue41i57( Test & t ){
	auto idPlanety = Aplikacja::getInstance().getGra().generujPlanete();
	t.assert_false(EXCEPTION_PLACE,Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(idPlanety));
	Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(idPlanety);

	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x12),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x13),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x13),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0x12)).pobierzCzasBudowy()==Czas(78));
	return true;
}

bool test_Issue39( Test & t ){
	auto idPlanety = Aplikacja::getInstance().getGra().generujPlanete();
	t.assert_false(EXCEPTION_PLACE,Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(idPlanety));
	Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(idPlanety);
	
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0xC),Ilosc(1)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x1),Ilosc(20000)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x4),Ilosc(20000)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x7),Ilosc(20000)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x13),Ilosc(1)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x10),Ilosc(1)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x13),Ilosc(1)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x10),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x13),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x10),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(Identyfikator(0xC)).czyMoznaWybudowac());
	return true;
}

bool test_KlasyFlota( Test & t ){
	auto idPlanety = Aplikacja::getInstance().getGra().generujPlanete();
	t.assert_false(EXCEPTION_PLACE,Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(idPlanety));
	Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(idPlanety);
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x1),Ilosc(20000)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x4),Ilosc(20000)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0x7),Ilosc(20000)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0xB),Ilosc(1000)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(Identyfikator(0xE),Ilosc(2000)));
	auto idFloty = planeta.dodajFlote();
	t.assert_false(EXCEPTION_PLACE,planeta.przeniesDoFloty(idFloty,Identyfikator(0xB),Ilosc(500)));
	t.assert_false(EXCEPTION_PLACE,planeta.przeniesDoFloty(idFloty,Identyfikator(0xE),Ilosc(1000)));
	
	t.assert_false(EXCEPTION_PLACE,planeta.zaladujFlote(idFloty,Identyfikator(0x1),Ilosc(500)));
	t.assert_false(EXCEPTION_PLACE,planeta.zaladujFlote(idFloty,Identyfikator(0xE),Ilosc(900)));

	return true;
}
*/