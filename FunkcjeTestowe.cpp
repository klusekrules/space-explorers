#include "Test.h"
#include "Testy.h"

Statek* tworzStatek( Test& t, const IdType& id,const Ilosc& i) throw (OgolnyWyjatek,NieznalezionoObiektu){
	Statek* s = Aplikacja::getInstance().getGra().getStatek(id).TworzEgzemplarz(i);
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
	Surowce* s = Aplikacja::getInstance().getGra().getSurowce(id).TworzEgzemplarz(i);
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

bool ladowanie_danych( Test & t ){
	/* Generowanie danych */

	//Statek	
	t.assert_false( EXCEPTION_PLACE , Aplikacja::getInstance().WczytajDane() );
	shared_ptr<Statek> s( tworzStatek(t,IdType(1),Ilosc(1)) );
	Aplikacja::getInstance().getLog().debug(*s);
	return true;
}

bool test_KlasaNiepoprawneParametryFunkcji( Test & t ){
	try{
		Ilosc temp(5);
		shared_ptr<Statek> s( tworzStatek(t,IdType(1),Ilosc(1)));
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
	shared_ptr<Statek> a (tworzStatek(t,IdType(4),Ilosc(8)));
	Aplikacja::getInstance().getLog().debug("Pojemnosc Maksymalna:");
	Aplikacja::getInstance().getLog().debug(a->getPojemnoscMax());
	shared_ptr<Statek> b (tworzStatek(t,IdType(1),Ilosc(150)));
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
	ObiektInfo& p = Aplikacja::getInstance().getGra().getStatek(IdType(1));
	Aplikacja::getInstance().getLog().debug( "Klasa info:");
	Aplikacja::getInstance().getLog().debug(p);
	shared_ptr<Obiekt>o (p.TworzEgzemplarz(Ilosc(8)));
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
	a = tworzStatek(t,IdType(1),Ilosc(8));
	lista.add(a);
	Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
	Aplikacja::getInstance().getLog().debug(*a);

	b = tworzStatek(t,IdType(2),Ilosc(8));
	lista.add(b);	
	Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
	Aplikacja::getInstance().getLog().debug(*b);

	c = tworzStatek(t,IdType(3),Ilosc(8));
	lista.add(c);
	Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
	Aplikacja::getInstance().getLog().debug(*c);

	d = tworzStatek(t,IdType(4),Ilosc(8));
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

	Statek& sTmp1 = lista.get(Klucz(IdType( 2 ),Poziom( 1 )));
	t.assert_false(EXCEPTION_PLACE,sTmp1.getId()==IdType( 2 ));
	t.assert_false(EXCEPTION_PLACE,sTmp1.getPoziom()==Poziom( 1 ));
	Aplikacja::getInstance().getLog().debug("Pobranie z kontenera: ");
	Aplikacja::getInstance().getLog().debug(sTmp1);
	Aplikacja::getInstance().getLog().debug("Usuniecie z kontenera wartosci o kluczu: ");
	Aplikacja::getInstance().getLog().debug(Klucz(IdType( 1 ),Poziom( 1 )));
	t.assert_false(EXCEPTION_PLACE,lista.del(Klucz(IdType( 1 ),Poziom( 1 ))));
	Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera po usunieciu");
	Aplikacja::getInstance().getLog().debug(lista);
	Aplikacja::getInstance().getLog().debug("Pobranie i jednoszesne usuniecie z kontenera wartosci o kluczu:");
	Aplikacja::getInstance().getLog().debug(Klucz(IdType( 4 ),Poziom( 1 )));
	Statek* sTmp2 = lista.getAndDel(Klucz(IdType( 4 ),Poziom( 1 )));
	t.assert_false(EXCEPTION_PLACE,sTmp2->getId()==IdType( 4 ));
	t.assert_false(EXCEPTION_PLACE,sTmp2->getPoziom()==Poziom( 1 ));
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
	shared_ptr<Statek> a( tworzStatek(t,IdType(1),Ilosc(8)) );
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
	shared_ptr<Statek> a( tworzStatek(t,IdType(1),Ilosc(8)) );
	Obrazenia oAtak = a->Atak();
	Obrazenia baseAtak(a->getStatekInfo().getAtak(Poziom(1)).value()*8.0);
	Obrazenia tbAtak(baseAtak.value() *(JednostkaAtakujaca::srednia-(JednostkaAtakujaca::odchylenie * 3 )));
	Obrazenia teAtak(baseAtak.value() *(JednostkaAtakujaca::srednia+(JednostkaAtakujaca::odchylenie * 3 )));
	Aplikacja::getInstance().getLog().debug(oAtak);
	Aplikacja::getInstance().getLog().debug(baseAtak);
	Aplikacja::getInstance().getLog().debug(tbAtak);
	Aplikacja::getInstance().getLog().debug(teAtak);
	t.assert_false(EXCEPTION_PLACE, tbAtak <= oAtak && oAtak <= teAtak);

	Obrazenia oOslona = a->Oslona(oAtak);
	Obrazenia baseOslona(a->getStatekInfo().getOslona(Poziom(1)).value()*8.0);
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
	Obrazenia basePancerz(a->getStatekInfo().getPancerz(Poziom(1)).value()*8.0);
	Obrazenia tbPancerz(basePancerz<oOslona?oOslona-basePancerz:Obrazenia(0));
	Aplikacja::getInstance().getLog().debug(oPancerz);
	Aplikacja::getInstance().getLog().debug(basePancerz);
	Aplikacja::getInstance().getLog().debug(tbPancerz);
	t.assert_false(EXCEPTION_PLACE, tbPancerz == oPancerz);
	return true;
}

bool test_Issue42( Test & t ){
	shared_ptr<Statek> a( tworzStatek(t,IdType(2),Ilosc(2)) );
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