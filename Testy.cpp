#include "Testy.h"


Testy::Testy(){
	Aplikacja::getInstance();
}


Testy::~Testy(){
}

unsigned int Testy::bledy(0);
unsigned int Testy::testy(0);
unsigned int Testy::fatalError(0);
unsigned int Testy::bledyGlobal(0);
unsigned int Testy::testyGlobal(0);
unsigned int Testy::fatalErrorGlobal(0);
chrono::steady_clock::time_point Testy::startlocal;
chrono::steady_clock::time_point Testy::endlocal;
chrono::steady_clock::time_point Testy::start;
chrono::steady_clock::time_point Testy::end;
string Testy::modulName;


void Testy::startTest(){
	bledyGlobal=0;
	testyGlobal=0;
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("              Rozpoczêcie testów               ");
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	start = chrono::steady_clock::now();
}

void Testy::startTestModul(string name){
	modulName = name;
	bledy=0;
	testy=0;
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("           Rozpoczêcie testów modu³u           ");
	Aplikacja::getInstance().getLog().info(Testy::modulName);
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	startlocal = chrono::steady_clock::now();
}
bool Testy::assert_false( const Tekst& tPlik, const Ilosc& iLinia, bool a ){
	++testy;
	++testyGlobal;
	if(!a){
		Aplikacja::getInstance().getLog().error("Wykryto niepoprawny rezultat testu");
		Aplikacja::getInstance().getLog().error("Plik:");
		Aplikacja::getInstance().getLog().error( tPlik );
		Aplikacja::getInstance().getLog().error("Linia:");
		Aplikacja::getInstance().getLog().error( iLinia );
		++bledy;
		++bledyGlobal;
		return false;
	}
	return true;
}
bool Testy::assert_true( const Tekst& tPlik, const Ilosc& iLinia, bool a ){
	++testy;
	++testyGlobal;
	if(a){
		Aplikacja::getInstance().getLog().error("Wykryto niepoprawny rezultat testu");
		Aplikacja::getInstance().getLog().error("Plik:");
		Aplikacja::getInstance().getLog().error( tPlik );
		Aplikacja::getInstance().getLog().error("Linia:");
		Aplikacja::getInstance().getLog().error( iLinia );
		++bledy;
		++bledyGlobal;
		return false;
	}
	return true;
}

bool Testy::endTestModul(){	
	stringstream s,st;
	endlocal = chrono::steady_clock::now();
	st<<"Czas trwania testu: "<<chrono::duration_cast<chrono::milliseconds>(endlocal - startlocal).count()<< "ms.";
	s<<"Liczba Testów: "<<testy<<" , Liczba B³êdów: "<<bledy;
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("           Zakoñczenie testów modu³u           ");
	Aplikacja::getInstance().getLog().info(modulName);
	Aplikacja::getInstance().getLog().info(s.str());
	Aplikacja::getInstance().getLog().info(st.str());
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	return bledy==0;
}

bool Testy::endTestModulImidaite(){
	stringstream s,st;
	endlocal = chrono::steady_clock::now();
	st<<"Czas trwania testu: "<<chrono::duration_cast<chrono::milliseconds>(endlocal - startlocal).count()<< "ms.";
	s<<"Wykryto b³¹d krytyczny.\nPrzerwno dalsze dzia³anie metody testujacej.";
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("           Zakoñczenie testów modu³u           ");
	Aplikacja::getInstance().getLog().info(modulName);
	Aplikacja::getInstance().getLog().info(s.str());
	Aplikacja::getInstance().getLog().info(st.str());
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	++fatalErrorGlobal;
	return false;
}

void Testy::endTest(){
	stringstream s,t,st;
	end = chrono::steady_clock::now();
	st<<"Czas trwania testów: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count()<< "ms.";
	s<<"Przeprowadzono Testów: "<<testyGlobal<<" , Wykryto B³êdów: "<<bledyGlobal;
	t << "B³êdy krytyczne: " << fatalErrorGlobal;
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("              Zakoñczenie testów               ");
	Aplikacja::getInstance().getLog().info(s.str());
	Aplikacja::getInstance().getLog().info(t.str());
	Aplikacja::getInstance().getLog().info(st.str());
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	
}

bool Testy::ladowanie_danych()const{
	/* Generowanie danych */

	//Statek
	startTestModul("£adowanie Danych");
	try{
		assert_false( EXCEPTION_PLACE , Aplikacja::getInstance().WczytajDane() );
		shared_ptr<Statek> t( this->tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(1)));
		Aplikacja::getInstance().getLog().debug(*t);
	}catch(OgolnyWyjatek& e){
		Aplikacja::getInstance().getLog().error("Wykryto wyj¹tek:");
		Aplikacja::getInstance().getLog().error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}

Statek* Testy::tworzStatek(const Klucz& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu){
	Statek* s = Aplikacja::getInstance().getStatek(id).TworzEgzemplarz(i);
	if(assert_false(EXCEPTION_PLACE, s!=nullptr))
	{
		assert_false(EXCEPTION_PLACE, s->getIlosc()==i);
		assert_false(EXCEPTION_PLACE, s->ID()==id);
		Aplikacja::getInstance().getLog().debug( "Stworzony obiekt:");
		Aplikacja::getInstance().getLog().debug(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie uda³o siê utworzyæ obiektu"));
	}
	return s;
}

Surowce* Testy::tworzSurowce(const Klucz& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu){
	Surowce* s = Aplikacja::getInstance().getSurowce(id).TworzEgzemplarz(i);
	if(assert_false(EXCEPTION_PLACE, s!=nullptr))
	{
		assert_false(EXCEPTION_PLACE, s->getIlosc()==i);
		assert_false(EXCEPTION_PLACE, s->ID()==id);
		Aplikacja::getInstance().getLog().debug( "Stworzony obiekt:");
		Aplikacja::getInstance().getLog().debug(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie uda³o siê utworzyæ obiektu"));
	}
	return s;
}

void Testy::run() const{
	try{
		startTest();
		if(ladowanie_danych())
		{
			test_KlasaNiepoprawneParametryFunkcji();

			test_tworzenieObiektow();
		
			test_KlasaObiektList();
		
			test_KlasaLadownia();

			test_wymagan();

			test_KlasaJednostkaAtakujaca();

		}else{
			Aplikacja::getInstance().getLog().warn("Nie mo¿na kontynuowaæ testów!");
		}
		endTest();
	}catch( OgolnyWyjatek & e ){
		Aplikacja::getInstance().getLog().error(e.toString());
	}
}

bool Testy::test_KlasaNiepoprawneParametryFunkcji()const{
	startTestModul("Test klasy NiepoprawneParametryFunkcji");
	try{
		Ilosc temp(5);
		shared_ptr<Statek> t( this->tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(1)));
		Statek& tmp = *t;
		throw NiepoprawneParametryFunkcji( EXCEPTION_PLACE , tmp , temp );
	}catch( const NiepoprawneParametryFunkcji& e ){
		assert_true(EXCEPTION_PLACE , e.getParametry().isEmpty());
		Aplikacja::getInstance().getLog().debug(e.getParametry());
		Aplikacja::getInstance().getLog().debug("Zawartosc klasy NiepoprawneParametryFunkcji = ");
		Aplikacja::getInstance().getLog().debug(e.generujKomunikat());
	}
	return endTestModul();
}

bool Testy::test_KlasaLadownia()const{
	startTestModul("Test Klasy Ladownia");
	try{
		shared_ptr<Statek> a (tworzStatek(Klucz(IdType(4),Poziom(1)),Ilosc(8)));
		Aplikacja::getInstance().getLog().debug("Pojemnosc Maksymalna:");
		Aplikacja::getInstance().getLog().debug(a->getPojemnoscMax());
		shared_ptr<Statek> b (tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(150)));
		assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*b));
		shared_ptr<Surowce> c (tworzSurowce(Klucz(IdType(2),Poziom(3)),Ilosc(20)));
		assert_false(EXCEPTION_PLACE,c->czyTypPrzyrostowy());
		assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*c));
		shared_ptr<Surowce> d (tworzSurowce(Klucz(IdType(4),Poziom(1)),Ilosc(20)));
		assert_true(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*d));
		Aplikacja::getInstance().getLog().debug("Zawartosc po dodaniu obiektu: ");
		Aplikacja::getInstance().getLog().debug(*a);
		assert_false(EXCEPTION_PLACE,a->getZajeteMiejsce()!=Objetosc(0));
		Aplikacja::getInstance().getLog().debug("Zajete miejsce: ");
		Aplikacja::getInstance().getLog().debug(a->getZajeteMiejsce());
		Aplikacja::getInstance().getLog().debug("Dzielenie ladowni");
		shared_ptr<Ladownia::Zbiornik> zb (a->PodzielLadownie(Objetosc(a->getZajeteMiejsce().value()*0.1)+Objetosc(a->getZajeteMiejsce().value()/2.0),Objetosc(a->getZajeteMiejsce().value()/2.0)));
		assert_true(EXCEPTION_PLACE,zb->isEmpty());
		Aplikacja::getInstance().getLog().debug("Zbiornik odlaczony od ladowni: ");
		Aplikacja::getInstance().getLog().debug(*zb);
		Aplikacja::getInstance().getLog().debug("Ladownia po podzieleniu: ");
		Aplikacja::getInstance().getLog().debug(*a);
	}catch(OgolnyWyjatek& e){
		Aplikacja::getInstance().getLog().error("Wykryto wyjatek:");
		Aplikacja::getInstance().getLog().error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}

bool Testy::test_tworzenieObiektow()const{
	startTestModul("Tworzenie Obiektow");
	try{
		ObiektInfo& p = Aplikacja::getInstance().getStatek(Klucz(IdType(1),Poziom(1)));
		Aplikacja::getInstance().getLog().debug( "Klasa info:");
		Aplikacja::getInstance().getLog().debug(p);
		shared_ptr<Obiekt>o (p.TworzEgzemplarz(Ilosc(8)));
		if(assert_false(EXCEPTION_PLACE, o!=nullptr))
		{
			assert_false(EXCEPTION_PLACE, o->getIlosc()==Ilosc(8));
			Aplikacja::getInstance().getLog().debug( "Stworzony obiekt:");
			Aplikacja::getInstance().getLog().debug(*o);
		}
	}catch(OgolnyWyjatek& e){
		Aplikacja::getInstance().getLog().error("Wykryto wyjatek:");
		Aplikacja::getInstance().getLog().error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}
bool Testy::test_KlasaObiektList()const{
	startTestModul("Operacje na klasie ObiektList");
	ObiektList<Statek> lista;
	ObiektList<Statek> listaDruga;
	try{
		Statek *a = nullptr;
		Statek *b = nullptr;
		Statek *c = nullptr;
		Statek *d = nullptr;
		a = tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(8));
		lista.add(a);
		Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
		Aplikacja::getInstance().getLog().debug(*a);

		b = tworzStatek(Klucz(IdType(2),Poziom(1)),Ilosc(8));
		lista.add(b);	
		Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
		Aplikacja::getInstance().getLog().debug(*b);

		c = tworzStatek(Klucz(IdType(3),Poziom(1)),Ilosc(8));
		lista.add(c);
		Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
		Aplikacja::getInstance().getLog().debug(*c);

		d = tworzStatek(Klucz(IdType(4),Poziom(1)),Ilosc(8));
		lista.add(d);
		Aplikacja::getInstance().getLog().debug("Dodano do kontenera");
		Aplikacja::getInstance().getLog().debug(*d);

		Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera");
		Aplikacja::getInstance().getLog().debug(lista);
		Aplikacja::getInstance().getLog().debug("Pobranie listy obiektow");
		auto l = lista.rawObiektList();
		assert_true(EXCEPTION_PLACE,l.empty());
		Aplikacja::getInstance().getLog().debug("Ilosc elementow:");
		Aplikacja::getInstance().getLog().debug(Ilosc(static_cast<long double>(l.size())));
		for( auto a : l ){
			Aplikacja::getInstance().getLog().debug(*a);
		}
		Aplikacja::getInstance().getLog().debug("Pobranie listy kluczy");
		auto r = lista.rawKluczList();
		assert_true(EXCEPTION_PLACE,r.empty());
		Aplikacja::getInstance().getLog().debug("Ilosc elementow:");
		Aplikacja::getInstance().getLog().debug(Ilosc(static_cast<long double>(r.size())));
		for( auto a : r ){
			Aplikacja::getInstance().getLog().debug(a);
		}

		Statek& sTmp1 = lista.get(Klucz(IdType( 2 ),Poziom( 1 )));
		assert_false(EXCEPTION_PLACE,sTmp1.getId()==IdType( 2 ));
		assert_false(EXCEPTION_PLACE,sTmp1.getPoziom()==Poziom( 1 ));
		Aplikacja::getInstance().getLog().debug("Pobranie z kontenera: ");
		Aplikacja::getInstance().getLog().debug(sTmp1);
		Aplikacja::getInstance().getLog().debug("Usuniecie z kontenera wartosci o kluczu: ");
		Aplikacja::getInstance().getLog().debug(Klucz(IdType( 1 ),Poziom( 1 )));
		assert_false(EXCEPTION_PLACE,lista.del(Klucz(IdType( 1 ),Poziom( 1 ))));
		Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera po usunieciu");
		Aplikacja::getInstance().getLog().debug(lista);
		Aplikacja::getInstance().getLog().debug("Pobranie i jednoszesne usuniecie z kontenera wartosci o kluczu:");
		Aplikacja::getInstance().getLog().debug(Klucz(IdType( 4 ),Poziom( 1 )));
		Statek* sTmp2 = lista.getAndDel(Klucz(IdType( 4 ),Poziom( 1 )));
		assert_false(EXCEPTION_PLACE,sTmp2->getId()==IdType( 4 ));
		assert_false(EXCEPTION_PLACE,sTmp2->getPoziom()==Poziom( 1 ));
		Aplikacja::getInstance().getLog().debug(*sTmp2);
		delete sTmp2;
		Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera");
		Aplikacja::getInstance().getLog().debug(lista);
		Aplikacja::getInstance().getLog().debug("Pobranie listy obiektow");
		l = lista.rawObiektList();
		assert_true(EXCEPTION_PLACE,l.empty());
		Aplikacja::getInstance().getLog().debug("Ilosc elementow:");
		Aplikacja::getInstance().getLog().debug(Ilosc(static_cast<long double>(l.size())));
		for( auto a : l ){
			Aplikacja::getInstance().getLog().debug(*a);
		}
		Aplikacja::getInstance().getLog().debug("Pobranie listy kluczy");
		r = lista.rawKluczList();
		assert_true(EXCEPTION_PLACE,r.empty());
		Aplikacja::getInstance().getLog().debug("Ilosc elementow:");
		Aplikacja::getInstance().getLog().debug(Ilosc(static_cast<long double>(r.size())));
		for( auto a : r ){
			Aplikacja::getInstance().getLog().debug(a);
		}
		Aplikacja::getInstance().getLog().debug("Przenoszenie jednej sztuki obiektu o kluczu");
		Aplikacja::getInstance().getLog().debug(r.front());
		Aplikacja::getInstance().getLog().debug("do drugiego kontenera.");
		ObiektList<Statek>::move(r.front(),Ilosc(1),lista,listaDruga);
		assert_false(EXCEPTION_PLACE,listaDruga.size()==1);
		Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera");
		Aplikacja::getInstance().getLog().debug(lista);
		Aplikacja::getInstance().getLog().debug("Zawartoœæ drugiego kontenera");
		Aplikacja::getInstance().getLog().debug(listaDruga);
		Aplikacja::getInstance().getLog().debug("Przenoszenie calego obiektu o kluczu");
		Aplikacja::getInstance().getLog().debug(r.front());
		Aplikacja::getInstance().getLog().debug("do drugiego kontenera.");
		ObiektList<Statek>::move(r.front(),lista,listaDruga);
		assert_false(EXCEPTION_PLACE,listaDruga.size()==1);
		Aplikacja::getInstance().getLog().debug("Zawartoœæ kontenera");
		Aplikacja::getInstance().getLog().debug(lista);
		Aplikacja::getInstance().getLog().debug("Zawartoœæ drugiego kontenera");
		Aplikacja::getInstance().getLog().debug(listaDruga);
		Aplikacja::getInstance().getLog().debug("Rozmiar drugiej listy:");
		Aplikacja::getInstance().getLog().debug(Ilosc(static_cast<long double>(listaDruga.size())));
		Aplikacja::getInstance().getLog().debug("Czyszczenie kontenera");
		listaDruga.clear();
		assert_false(EXCEPTION_PLACE,listaDruga.isEmpty());
		Aplikacja::getInstance().getLog().debug("Zawartoœæ drugiego kontenera po wyczyszceniu");
		Aplikacja::getInstance().getLog().debug(listaDruga);
		Aplikacja::getInstance().getLog().debug("Test Zakoñczony powodzeniem.");
	}catch(OgolnyWyjatek& e){
		Aplikacja::getInstance().getLog().error("Wykryto wyjatek:");
		Aplikacja::getInstance().getLog().error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}

bool Testy::test_wymagan()const{
	startTestModul("Test Wymagan");
	try{
		shared_ptr<Statek> a( tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(8)) );
		auto t = a->PobierzKoszty();
		for(auto e : t){
			Aplikacja::getInstance().getLog().debug(*e);
		}
		assert_false(EXCEPTION_PLACE,t[0]->getIlosc()==Ilosc(120000.0));
		assert_false(EXCEPTION_PLACE,t[1]->getIlosc()==Ilosc(4000.0));
		assert_false(EXCEPTION_PLACE,t[2]->getIlosc()==Ilosc(8*1*10*5*200));
		auto w = a->PobierzWarunki();
		for(auto e : w){
			Aplikacja::getInstance().getLog().debug(*e);
		}
		assert_false(EXCEPTION_PLACE,w[0]->getPoziom()==Poziom(25));
		assert_false(EXCEPTION_PLACE,w[1]->getPoziom()==Poziom(5));

	}catch(OgolnyWyjatek& e){
		Aplikacja::getInstance().getLog().error("Wykryto wyjatek:");
		Aplikacja::getInstance().getLog().error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}
bool Testy::test_KlasaJednostkaAtakujaca()const{
	startTestModul("Test Jednostki Atakuj¹cej");
	try{
		shared_ptr<Statek> a( tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(8)) );
		Obrazenia oAtak = a->Atak();
		Obrazenia baseAtak(a->getStatekInfo().getAtak(Poziom(1)).value()*8.0);
		Obrazenia tbAtak(baseAtak.value() *(JednostkaAtakujaca::srednia-(JednostkaAtakujaca::odchylenie * 3 )));
		Obrazenia teAtak(baseAtak.value() *(JednostkaAtakujaca::srednia+(JednostkaAtakujaca::odchylenie * 3 )));
		Aplikacja::getInstance().getLog().debug(oAtak);
		Aplikacja::getInstance().getLog().debug(baseAtak);
		Aplikacja::getInstance().getLog().debug(tbAtak);
		Aplikacja::getInstance().getLog().debug(teAtak);
		assert_false(EXCEPTION_PLACE, tbAtak <= oAtak && oAtak <= teAtak);

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
		assert_false(EXCEPTION_PLACE, tbOslona <= oOslona && oOslona <= teOslona);

		Obrazenia oPancerz = a->Pancerz(oOslona);
		Obrazenia basePancerz(a->getStatekInfo().getPancerz(Poziom(1)).value()*8.0);
		Obrazenia tbPancerz(basePancerz<oOslona?oOslona-basePancerz:Obrazenia(0));
		Aplikacja::getInstance().getLog().debug(oPancerz);
		Aplikacja::getInstance().getLog().debug(basePancerz);
		Aplikacja::getInstance().getLog().debug(tbPancerz);
		assert_false(EXCEPTION_PLACE, tbPancerz == oPancerz);

	}catch(OgolnyWyjatek& e){
		Aplikacja::getInstance().getLog().error("Wykryto wyjatek:");
		Aplikacja::getInstance().getLog().error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}