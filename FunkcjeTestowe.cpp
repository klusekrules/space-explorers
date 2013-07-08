#include "Test.h"
#include "Testy.h"

Statek* tworzStatek( Test& t, const IdType& id,const Ilosc& i) throw (OgolnyWyjatek,NieznalezionoObiektu){
	Statek* s = Aplikacja::getInstance().getGra().getStatek(id).TworzEgzemplarz(i,IdType());
	if(t.assert_false(EXCEPTION_PLACE, s!=nullptr))
	{
		t.assert_false(EXCEPTION_PLACE, s->getIlosc()==i);
		t.assert_false(EXCEPTION_PLACE, s->getId()==id);
		Aplikacja::getInstance().getLog().debug( "Stworzony obiekt:");
		Aplikacja::getInstance().getLog().debug(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie uda³o siê utworzyæ obiektu"));
	}
	return s;
}

Surowce* tworzSurowce( Test& t, const IdType& id,const Ilosc& i) throw (OgolnyWyjatek,NieznalezionoObiektu){
	Surowce* s = Aplikacja::getInstance().getGra().getSurowce(id).TworzEgzemplarz(i,IdType());
	if(t.assert_false(EXCEPTION_PLACE, s!=nullptr))
	{
		t.assert_false(EXCEPTION_PLACE, s->getIlosc()==i);
		t.assert_false(EXCEPTION_PLACE, s->getId()==id);
		Aplikacja::getInstance().getLog().debug( "Stworzony obiekt:");
		Aplikacja::getInstance().getLog().debug(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie uda³o siê utworzyæ obiektu"));
	}
	return s;
}

Technologia* tworzTechnologie( Test& t, const IdType& id) throw (OgolnyWyjatek,NieznalezionoObiektu){
	Technologia* s = Aplikacja::getInstance().getGra().getTechnologia(id).TworzEgzemplarz(Ilosc(),IdType());
	if(t.assert_false(EXCEPTION_PLACE, s!=nullptr))
	{
		t.assert_false(EXCEPTION_PLACE, s->getId()==id);
		Aplikacja::getInstance().getLog().debug( "Stworzony obiekt:");
		Aplikacja::getInstance().getLog().debug(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie uda³o siê utworzyæ obiektu"));
	}
	return s;
}

Budynek* tworzBudynek( Test& t, const IdType& id) throw (OgolnyWyjatek,NieznalezionoObiektu){
	Budynek* s = Aplikacja::getInstance().getGra().getBudynek(id).TworzEgzemplarz(Ilosc(),IdType());
	if(t.assert_false(EXCEPTION_PLACE, s!=nullptr))
	{
		t.assert_false(EXCEPTION_PLACE, s->getId()==id);
		Aplikacja::getInstance().getLog().debug( "Stworzony obiekt:");
		Aplikacja::getInstance().getLog().debug(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie uda³o siê utworzyæ obiektu"));
	}
	return s;
}

bool ladowanie_danych( Test & t ){
	t.assert_false( EXCEPTION_PLACE , Aplikacja::getInstance().WczytajDane() );
	return true;
}

bool test_KlasaNiepoprawneParametryFunkcji( Test & t ){
	try{
		Ilosc temp(5);
		shared_ptr<Statek> s( tworzStatek(t,IdType(11),Ilosc(1)));
		Statek& tmp = *s;
		throw NiepoprawneParametryFunkcji( EXCEPTION_PLACE , tmp , temp );
	}catch( const NiepoprawneParametryFunkcji& e ){
		t.assert_true(EXCEPTION_PLACE , e.getParametry().isEmpty());
		Aplikacja::getInstance().getLog().debug(e.getParametry());
		Aplikacja::getInstance().getLog().debug("Zawartosc klasy NiepoprawneParametryFunkcji = ");
		Aplikacja::getInstance().getLog().debug(e.generujKomunikat());
	}
	return true;
}

bool test_KlasaLadownia( Test & t ){
	shared_ptr<Statek> a (tworzStatek(t,IdType(14),Ilosc(8)));
	Aplikacja::getInstance().getLog().debug("Pojemnosc Maksymalna:");
	Aplikacja::getInstance().getLog().debug(a->getPojemnoscMax());
	shared_ptr<Statek> b (tworzStatek(t,IdType(11),Ilosc(10)));
	t.assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*b));
	shared_ptr<Surowce> c (tworzSurowce(t,IdType(6),Ilosc(20)));
	t.assert_false(EXCEPTION_PLACE,c->czyTypPrzyrostowy());
	t.assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*c));
	shared_ptr<Surowce> d (tworzSurowce(t,IdType(10),Ilosc(20)));
	t.assert_true(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*d));
	Aplikacja::getInstance().getLog().debug("Zawartosc po dodaniu obiektu: ");
	Aplikacja::getInstance().getLog().debug(*a);
	t.assert_false(EXCEPTION_PLACE,a->getZajeteMiejsce()!=Objetosc(0));
	Aplikacja::getInstance().getLog().debug("Zajete miejsce: ");
	Aplikacja::getInstance().getLog().debug(a->getZajeteMiejsce());
	Aplikacja::getInstance().getLog().debug("Dzielenie ladowni");
	shared_ptr<Ladownia::Zbiornik> zb (a->PodzielLadownie(Objetosc(a->getZajeteMiejsce().value()*0.1)+Objetosc(a->getZajeteMiejsce().value()/2.0),Objetosc(a->getZajeteMiejsce().value()/2.0)));
	t.assert_true(EXCEPTION_PLACE,zb->isEmpty());
	Aplikacja::getInstance().getLog().debug("Zbiornik odlaczony od ladowni: ");
	Aplikacja::getInstance().getLog().debug(*zb);
	Aplikacja::getInstance().getLog().debug("Ladownia po podzieleniu: ");
	Aplikacja::getInstance().getLog().debug(*a);
	return true;
}

bool test_tworzenieObiektow( Test & t ){
	ObiektInfo& p = Aplikacja::getInstance().getGra().getStatek(IdType(11));
	Aplikacja::getInstance().getLog().debug( "Klasa info:");
	Aplikacja::getInstance().getLog().debug(p);
	shared_ptr<Obiekt>o (p.TworzEgzemplarz(Ilosc(8),IdType()));
	if(t.assert_false(EXCEPTION_PLACE, o!=nullptr))
	{
		t.assert_false(EXCEPTION_PLACE, o->getIlosc()==Ilosc(8));
		Aplikacja::getInstance().getLog().debug( "Stworzony obiekt:");
		Aplikacja::getInstance().getLog().debug(*o);
	}
	return true;
}

bool test_KlasaObiektList( Test & t ){
	ObiektList<Statek> lista;
	ObiektList<Statek> listaDruga;
	
	Statek *a = nullptr;
	Statek *b = nullptr;
	Statek *c = nullptr;
	Statek *d = nullptr;
	a = tworzStatek(t,IdType(11),Ilosc(8));
	lista.add(a);
	Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
	Aplikacja::getInstance().getLog().debug(*a);

	b = tworzStatek(t,IdType(12),Ilosc(8));
	lista.add(b);	
	Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
	Aplikacja::getInstance().getLog().debug(*b);

	c = tworzStatek(t,IdType(13),Ilosc(8));
	lista.add(c);
	Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
	Aplikacja::getInstance().getLog().debug(*c);

	d = tworzStatek(t,IdType(14),Ilosc(8));
	lista.add(d);
	Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
	Aplikacja::getInstance().getLog().debug(*d);

	Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera");
	Aplikacja::getInstance().getLog().debug(lista);
	Aplikacja::getInstance().getLog().debug("Pobranie listy obiektow");
	auto l = lista.rawObiektList();
	t.assert_true(EXCEPTION_PLACE,l.empty());
	Aplikacja::getInstance().getLog().debug("Ilosc elementow:");
	Aplikacja::getInstance().getLog().debug(Ilosc(static_cast<long double>(l.size())));
	for( auto a : l ){
		Aplikacja::getInstance().getLog().debug(*a);
	}
	Aplikacja::getInstance().getLog().debug("Pobranie listy kluczy");
	auto r = lista.rawKluczList();
	t.assert_true(EXCEPTION_PLACE,r.empty());
	Aplikacja::getInstance().getLog().debug("Ilosc elementow:");
	Aplikacja::getInstance().getLog().debug(Ilosc(static_cast<long double>(r.size())));
	for( auto a : r ){
		Aplikacja::getInstance().getLog().debug(a);
	}

	Statek& sTmp1 = lista.get(Klucz(IdType( 12 ),Poziom( 1 )));
	t.assert_false(EXCEPTION_PLACE,sTmp1.getId()==IdType( 12 ));
	t.assert_false(EXCEPTION_PLACE,sTmp1.getPoziom()==Poziom( 1 ));
	Aplikacja::getInstance().getLog().debug("Pobranie z kontenera: ");
	Aplikacja::getInstance().getLog().debug(sTmp1);
	Aplikacja::getInstance().getLog().debug("Usuniecie z kontenera wartosci o kluczu: ");
	Aplikacja::getInstance().getLog().debug(Klucz(IdType( 11 ),Poziom( 1 )));
	t.assert_false(EXCEPTION_PLACE,lista.del(Klucz(IdType( 11 ),Poziom( 1 ))));
	Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera po usunieciu");
	Aplikacja::getInstance().getLog().debug(lista);
	Aplikacja::getInstance().getLog().debug("Pobranie i jednoszesne usuniecie z kontenera wartosci o kluczu:");
	Aplikacja::getInstance().getLog().debug(Klucz(IdType( 14 ),Poziom( 2 )));
	Statek* sTmp2 = lista.getAndDel(Klucz(IdType( 14 ),Poziom( 2 )));
	t.assert_false(EXCEPTION_PLACE,sTmp2->getId()==IdType( 14 ));
	t.assert_false(EXCEPTION_PLACE,sTmp2->getPoziom()==Poziom( 2 ));
	Aplikacja::getInstance().getLog().debug(*sTmp2);
	delete sTmp2;
	Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera");
	Aplikacja::getInstance().getLog().debug(lista);
	Aplikacja::getInstance().getLog().debug("Pobranie listy obiektow");
	l = lista.rawObiektList();
	t.assert_true(EXCEPTION_PLACE,l.empty());
	Aplikacja::getInstance().getLog().debug("Ilosc elementow:");
	Aplikacja::getInstance().getLog().debug(Ilosc(static_cast<long double>(l.size())));
	for( auto a : l ){
		Aplikacja::getInstance().getLog().debug(*a);
	}
	Aplikacja::getInstance().getLog().debug("Pobranie listy kluczy");
	r = lista.rawKluczList();
	t.assert_true(EXCEPTION_PLACE,r.empty());
	Aplikacja::getInstance().getLog().debug("Ilosc elementow:");
	Aplikacja::getInstance().getLog().debug(Ilosc(static_cast<long double>(r.size())));
	for( auto a : r ){
		Aplikacja::getInstance().getLog().debug(a);
	}
	Aplikacja::getInstance().getLog().debug("Przenoszenie jednej sztuki obiektu o kluczu");
	Aplikacja::getInstance().getLog().debug(r.front());
	Aplikacja::getInstance().getLog().debug("do drugiego kontenera.");
	ObiektList<Statek>::move(r.front(),Ilosc(1),lista,listaDruga);
	t.assert_false(EXCEPTION_PLACE,listaDruga.size()==1);
	Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera");
	Aplikacja::getInstance().getLog().debug(lista);
	Aplikacja::getInstance().getLog().debug("Zawartoœæ drugiego kontenera");
	Aplikacja::getInstance().getLog().debug(listaDruga);
	Aplikacja::getInstance().getLog().debug("Przenoszenie calego obiektu o kluczu");
	Aplikacja::getInstance().getLog().debug(r.front());
	Aplikacja::getInstance().getLog().debug("do drugiego kontenera.");
	ObiektList<Statek>::move(r.front(),lista,listaDruga);
	t.assert_false(EXCEPTION_PLACE,listaDruga.size()==1);
	Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera");
	Aplikacja::getInstance().getLog().debug(lista);
	Aplikacja::getInstance().getLog().debug("Zawartoœæ drugiego kontenera");
	Aplikacja::getInstance().getLog().debug(listaDruga);
	Aplikacja::getInstance().getLog().debug("Rozmiar drugiej listy:");
	Aplikacja::getInstance().getLog().debug(Ilosc(static_cast<long double>(listaDruga.size())));
	Aplikacja::getInstance().getLog().debug("Czyszczenie kontenera");
	listaDruga.clear();
	t.assert_false(EXCEPTION_PLACE,listaDruga.isEmpty());
	Aplikacja::getInstance().getLog().debug("Zawartoœæ drugiego kontenera po wyczyszceniu");
	Aplikacja::getInstance().getLog().debug(listaDruga);
	Aplikacja::getInstance().getLog().debug("Test Zakoñczony powodzeniem.");
	return true;
}

bool test_wymagan( Test & t ){
	shared_ptr<Statek> a( tworzStatek(t,IdType(11),Ilosc(8)) );
	auto tmp = a->PobierzKoszty();
	for(auto e : tmp){
		Aplikacja::getInstance().getLog().debug(*e);
	}
	t.assert_false(EXCEPTION_PLACE,tmp[0]->getIlosc()==Ilosc(120000.0));
	t.assert_false(EXCEPTION_PLACE,tmp[1]->getIlosc()==Ilosc(4000.0));
	t.assert_false(EXCEPTION_PLACE,tmp[2]->getIlosc()==Ilosc(8*1*10*5*200));
	auto w = a->PobierzWarunki();
	for(auto e : w){
		Aplikacja::getInstance().getLog().debug(*e);
	}
	t.assert_false(EXCEPTION_PLACE,w[0]->getPoziom()==Poziom(25));
	t.assert_false(EXCEPTION_PLACE,w[1]->getPoziom()==Poziom(5));
	return true;
}

bool test_KlasaJednostkaAtakujaca( Test & t ){
	shared_ptr<Statek> a( tworzStatek(t,IdType(11),Ilosc(8)) );
	Obrazenia oAtak = a->Atak();
	Obrazenia baseAtak(a->getStatekInfo().getAtak(PodstawoweParametry(Poziom(1),IdType())).value()*8.0);
	Obrazenia tbAtak(baseAtak.value() *(JednostkaAtakujaca::srednia-(JednostkaAtakujaca::odchylenie * 3 )));
	Obrazenia teAtak(baseAtak.value() *(JednostkaAtakujaca::srednia+(JednostkaAtakujaca::odchylenie * 3 )));
	Aplikacja::getInstance().getLog().debug(oAtak);
	Aplikacja::getInstance().getLog().debug(baseAtak);
	Aplikacja::getInstance().getLog().debug(tbAtak);
	Aplikacja::getInstance().getLog().debug(teAtak);
	t.assert_false(EXCEPTION_PLACE, tbAtak <= oAtak && oAtak <= teAtak);

	Obrazenia oOslona = a->Oslona(oAtak);
	Obrazenia baseOslona(a->getStatekInfo().getOslona(PodstawoweParametry(Poziom(1),IdType())).value()*8.0);
	double tbd=oAtak.value() - baseOslona.value() *(JednostkaAtakujaca::srednia+(JednostkaAtakujaca::odchylenie * 3 ));
	double ted=oAtak.value() - baseOslona.value() *(JednostkaAtakujaca::srednia-(JednostkaAtakujaca::odchylenie * 3 ));
	Obrazenia tbOslona(tbd>0?tbd:0);
	Obrazenia teOslona(ted>0?ted:0);
	Aplikacja::getInstance().getLog().debug(oOslona);
	Aplikacja::getInstance().getLog().debug(baseOslona);
	Aplikacja::getInstance().getLog().debug(tbOslona);
	Aplikacja::getInstance().getLog().debug(teOslona);
	t.assert_false(EXCEPTION_PLACE, tbOslona <= oOslona && oOslona <= teOslona);

	Obrazenia oPancerz = a->Pancerz(oOslona);
	Obrazenia basePancerz(a->getStatekInfo().getPancerz(PodstawoweParametry(Poziom(1),IdType())).value()*8.0);
	Obrazenia tbPancerz(basePancerz<oOslona?oOslona-basePancerz:Obrazenia(0));
	Aplikacja::getInstance().getLog().debug(oPancerz);
	Aplikacja::getInstance().getLog().debug(basePancerz);
	Aplikacja::getInstance().getLog().debug(tbPancerz);
	t.assert_false(EXCEPTION_PLACE, tbPancerz == oPancerz);
	return true;
}

bool test_Issue42( Test & t ){
	shared_ptr<Statek> a( tworzStatek(t,IdType(12),Ilosc(2)) );
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
	shared_ptr<Statek> a( tworzStatek(t,IdType(13),Ilosc(1)) );
	t.assert_false(EXCEPTION_PLACE, a->getPoziom() == Poziom(4));
	shared_ptr<Statek> b( tworzStatek(t,IdType(14),Ilosc(1)) );
	t.assert_false(EXCEPTION_PLACE, b->getPoziom() == Poziom(2));
	return true;
}

bool test_Technologie( Test & t ){
	shared_ptr<Technologia> a( tworzTechnologie(t,IdType(15)) );
	Aplikacja::getInstance().getLog().debug(*a);
	shared_ptr<Technologia> b( tworzTechnologie(t,IdType(16)) );
	Aplikacja::getInstance().getLog().debug(*b);
	return true;
}

bool test_Budynki( Test & t ){
	shared_ptr<Budynek> a( tworzBudynek(t,IdType(17)) );
	a->setPoziom(Poziom(3));
	auto z = a->PobierzZapotrzebowanie();
	if(t.assert_false(EXCEPTION_PLACE, z.size()>0)){
		t.assert_false(EXCEPTION_PLACE, z[0]->getIlosc()==Ilosc(180));
		t.assert_false(EXCEPTION_PLACE, z[0]->getId()==IdType(10));
	}
	auto p = a->PobierzProdukcje();
	if(t.assert_false(EXCEPTION_PLACE, p.size()>0)){
		t.assert_false(EXCEPTION_PLACE, p[0]->getIlosc()==Ilosc(6000));
		t.assert_false(EXCEPTION_PLACE, p[0]->getId()==IdType(1));
	}

	shared_ptr<Budynek> b( tworzBudynek(t,IdType(18)) );
	b->setPoziom(Poziom(2));
	p = b->PobierzProdukcje();
	if(t.assert_false(EXCEPTION_PLACE, p.size()>0)){
		t.assert_false(EXCEPTION_PLACE, p[0]->getIlosc()==Ilosc(6000));
		t.assert_false(EXCEPTION_PLACE, p[0]->getId()==IdType(10));
	}
	z = b->PobierzZapotrzebowanie();
	t.assert_false(EXCEPTION_PLACE, z.size()==0);

	shared_ptr<Budynek> c( tworzBudynek(t,IdType(19)) );
	c->setPoziom(Poziom(2));
	p = c->PobierzProdukcje();
	t.assert_false(EXCEPTION_PLACE, p.size()==0);
	z = c->PobierzZapotrzebowanie();
	t.assert_false(EXCEPTION_PLACE, z.size()==0);
	return true;
}

bool test_Logowanie( Test & t ){
	t.assert_false(EXCEPTION_PLACE,Aplikacja::getInstance().getGra().Logowanie("",""));
	return true;
}

bool test_TworzeniePlanetyIObiektow( Test & t ){
	auto idPlanety = Aplikacja::getInstance().getGra().generujPlanete();
	t.assert_false(EXCEPTION_PLACE,Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(idPlanety));
	Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(idPlanety);

	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(17),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(17)).getPoziom()==Poziom(1));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(17)).getIlosc()==Ilosc(1));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(17),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(17)).getPoziom()==Poziom(2));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(17)).getIlosc()==Ilosc(1));

	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(15),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(15)).getPoziom()==Poziom(1));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(15)).getIlosc()==Ilosc(1));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(15),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(15)).getPoziom()==Poziom(2));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(15)).getIlosc()==Ilosc(1));

	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(1),Ilosc(100)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(1)).getPoziom()==Poziom(1));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(1)).getIlosc()==Ilosc(100));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(1),Ilosc(100)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(1)).getPoziom()==Poziom(1));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(1)).getIlosc()==Ilosc(200));

	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0xB),Ilosc(100)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xB)).getPoziom()==Poziom(1));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xB)).getIlosc()==Ilosc(100));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0xB),Ilosc(100)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xB)).getPoziom()==Poziom(1));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xB)).getIlosc()==Ilosc(200));
	
	t.assert_true(EXCEPTION_PLACE,planeta.wybuduj(IdType(20000),Ilosc(1)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(20000)).getId()==IdType(20000));

	t.assert_false(EXCEPTION_PLACE,planeta.pobierzIloscTypowObiektow()==Ilosc(4));

	/*shared_ptr<Statek> a (tworzStatek(t,IdType(14),Ilosc(8)));
	shared_ptr<Statek> b (tworzStatek(t,IdType(11),Ilosc(150)));
	t.assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*b));
	shared_ptr<Surowce> c (tworzSurowce(t,IdType(6),Ilosc(20)));
	t.assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*c));
	shared_ptr<Surowce> d (tworzSurowce(t,IdType(10),Ilosc(20)));
	t.assert_true(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*d));*/
	return true;
}

bool test_Issue41i57( Test & t ){
	auto idPlanety = Aplikacja::getInstance().getGra().generujPlanete();
	t.assert_false(EXCEPTION_PLACE,Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(idPlanety));
	Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(idPlanety);

	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x12),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x13),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x13),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0x12)).pobierzCzasBudowy()==Czas(78));
	return true;
}

bool test_Issue39( Test & t ){
	auto idPlanety = Aplikacja::getInstance().getGra().generujPlanete();
	t.assert_false(EXCEPTION_PLACE,Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(idPlanety));
	Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(idPlanety);
	
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0xC),Ilosc(1)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x1),Ilosc(20000)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x4),Ilosc(20000)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x7),Ilosc(20000)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x13),Ilosc(1)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x10),Ilosc(1)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x13),Ilosc(1)));
	t.assert_true(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x10),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x13),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xC)).czyMoznaWybudowac());
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x10),Ilosc(1)));
	t.assert_false(EXCEPTION_PLACE,planeta.pobierzObiekt(IdType(0xC)).czyMoznaWybudowac());
	return true;
}

bool test_ZapisStanuGry( Test & t ){
	int ptr_a = (int)(&(Aplikacja::getInstance().getGra()));
	auto p_a = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(IdType(3));
	t.assert_false(EXCEPTION_PLACE,Aplikacja::getInstance().ZapiszGre());
	t.assert_false(EXCEPTION_PLACE,Aplikacja::getInstance().WczytajGre());
	auto p_b = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(IdType(3));
	int ptr_b = (int)(&(Aplikacja::getInstance().getGra()));
	t.assert_true(EXCEPTION_PLACE,ptr_a==ptr_b);
	t.assert_false(EXCEPTION_PLACE,p_a.pobierzIloscTypowObiektow()==p_b.pobierzIloscTypowObiektow());
	t.assert_false(EXCEPTION_PLACE,p_a.pobierzObiekt(IdType(1)).getIlosc()==p_b.pobierzObiekt(IdType(1)).getIlosc());
	return true;
}

bool test_KlasyFlota( Test & t ){
	auto idPlanety = Aplikacja::getInstance().getGra().generujPlanete();
	t.assert_false(EXCEPTION_PLACE,Aplikacja::getInstance().getGra().przeniesPlaneteDoUzytkownika(idPlanety));
	Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(idPlanety);
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x1),Ilosc(20000)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x4),Ilosc(20000)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0x7),Ilosc(20000)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0xB),Ilosc(1000)));
	t.assert_false(EXCEPTION_PLACE,planeta.wybuduj(IdType(0xE),Ilosc(2000)));
	auto idFloty = planeta.dodajFlote();
	t.assert_false(EXCEPTION_PLACE,planeta.przeniesDoFloty(idFloty,IdType(0xB),Ilosc(500)));
	t.assert_false(EXCEPTION_PLACE,planeta.przeniesDoFloty(idFloty,IdType(0xE),Ilosc(1000)));
	
	t.assert_false(EXCEPTION_PLACE,planeta.zaladujFlote(idFloty,IdType(0x1),Ilosc(500)));
	t.assert_false(EXCEPTION_PLACE,planeta.zaladujFlote(idFloty,IdType(0xE),Ilosc(900)));

	return true;
}
