#include "Test.h"
#include "Testy.h"

/*
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
*/