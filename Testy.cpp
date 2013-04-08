#include "Testy.h"

Testy::Testy(){
	locale pl ("Polish");
	locale::global (pl);
}


Testy::~Testy(){
}

unsigned int Testy::bledy(0);
unsigned int Testy::testy(0);
unsigned int Testy::fatalError(0);
unsigned int Testy::bledyGlobal(0);
unsigned int Testy::testyGlobal(0);
unsigned int Testy::fatalErrorGlobal(0);
string Testy::modulName;


void Testy::startTest(){
	bledyGlobal=0;
	testyGlobal=0;
	Log::info("----------------------------------------------");
	Log::info("              Rozpoczecie testow               ");
	Log::info("----------------------------------------------");
}

void Testy::startTestModul(string name){
	modulName = name;
	bledy=0;
	testy=0;
	Log::info("----------------------------------------------");
	Log::info("           Rozpoczecie testow modulu           ");
	Log::info(Testy::modulName);
	Log::info("----------------------------------------------");
}
bool Testy::assert_false( const Tekst& tPlik, const IdType& iLinia, bool a ){
	++testy;
	++testyGlobal;
	if(!a){
		Log::error("Wykryto niepoprawny rezultat testu");
		Log::error("Plik:");
		Log::error( tPlik );
		Log::error("Linia:");
		Log::error( iLinia );
		++bledy;
		++bledyGlobal;
		return false;
	}
	return true;
}
bool Testy::assert_true( const Tekst& tPlik, const IdType& iLinia, bool a ){
	++testy;
	++testyGlobal;
	if(a){
		Log::error("Wykryto niepoprawny rezultat testu");
		Log::error("Plik:");
		Log::error( tPlik );
		Log::error("Linia:");
		Log::error( iLinia );
		++bledy;
		++bledyGlobal;
		return false;
	}
	return true;
}

bool Testy::endTestModul(){	
	stringstream s;
	s<<"Liczba Testow: "<<testy<<" , Liczba Bledow: "<<bledy;
	Log::info("----------------------------------------------");
	Log::info("           Zakonczenie testow modulu           ");
	Log::info(modulName);
	Log::info(s.str());
	Log::info("----------------------------------------------");
	return bledy==0;
}

bool Testy::endTestModulImidaite(){
	stringstream s;
	s<<"Wykryto b³¹d krytyczny.\nPrzerwno dalsze dzia³anie metody testujacej.";
	Log::info("----------------------------------------------");
	Log::info("           Zakonczenie testow modulu           ");
	Log::info(modulName);
	Log::info(s.str());
	Log::info("----------------------------------------------");
	++fatalErrorGlobal;
	return false;
}

void Testy::endTest(){
	stringstream s,t;
	s<<"Przeprowadzono Testow: "<<testyGlobal<<" , Wykryto Bledow: "<<bledyGlobal;
	t << "Bledy krytyczne: " << fatalErrorGlobal;
	Log::info("----------------------------------------------");
	Log::info("              Zakonczenie testow               ");
	Log::info(s.str());
	Log::info(t.str());
	Log::info("----------------------------------------------");
}

bool Testy::ladowanie_danych(){
	/* Generowanie danych */

	//Statek
	startTestModul("Ladowanie Danych");
	try{
		assert_false( EXCEPTION_PLACE , Aplikacja::getInstance().WczytajDane("test.xml") );
	}catch(OgolnyWyjatek& e){
		Log::error("Wykryto wyjatek:");
		Log::error(e);
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
		Log::debug( "Stworzony obiekt:");
		Log::debug<Statek>(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie udalo sie utworzyc obiektu"));
	}
	return s;
}

Surowce* Testy::tworzSurowce(const Klucz& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu){
	Surowce* s = Aplikacja::getInstance().getSurowce(id).TworzEgzemplarz(i);
	if(assert_false(EXCEPTION_PLACE, s!=nullptr))
	{
		assert_false(EXCEPTION_PLACE, s->getIlosc()==i);
		assert_false(EXCEPTION_PLACE, s->ID()==id);
		Log::debug( "Stworzony obiekt:");
		Log::debug<Surowce>(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie udalo sie utworzyc obiektu"));
	}
	return s;
}

void Testy::run(){
	startTest();
	if(ladowanie_danych())
	{
		test_KlasaNiepoprawneParametryFunkcji();

		test_tworzenieObiektow();
		
		test_KlasaObiektList();
		
		test_KlasaLadownia();

		test_wymagan();

	}else{
		Log::warn("Nie mozna kontynuowac testow!");
	}
	endTest();
}

bool Testy::test_KlasaNiepoprawneParametryFunkcji(){
	startTestModul("Test klasy NiepoprawneParametryFunkcji");
	try{
		Ilosc temp(5);
		Objetosc tmp( 10.7 );
		throw NiepoprawneParametryFunkcji( EXCEPTION_PLACE , tmp , temp );
	}
	catch( const NiepoprawneParametryFunkcji& e ){
		assert_true(EXCEPTION_PLACE , e.getParametry().isEmpty());
		Log::debug(e.getParametry());
		Log::debug("Zawartosc klasy NiepoprawneParametryFunkcji = ");
		Log::debug(e.generujKomunikat());
	}
	return endTestModul();
}

bool Testy::test_KlasaLadownia(){
	startTestModul("Test Klasy Ladownia");
	try{
		shared_ptr<Statek> a (tworzStatek(Klucz(IdType(4),Poziom(1)),Ilosc(8)));
		Log::debug("Pojemnosc Maksymalna:");
		Log::debug(a->getPojemnoscMax());
		shared_ptr<Statek> b (tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(150)));
		assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*b));
		shared_ptr<Surowce> c (tworzSurowce(Klucz(IdType(2),Poziom(3)),Ilosc(20)));
		assert_false(EXCEPTION_PLACE,c->czyTypPrzyrostowy());
		assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*c));
		Log::debug("Zawartosc po dodaniu obiektu: ");
		Log::debug<Ladownia>(*a);
		assert_false(EXCEPTION_PLACE,a->getZajeteMiejsce()!=Objetosc(0));
		Log::debug("Zajete miejsce: ");
		Log::debug(a->getZajeteMiejsce());
		Log::debug("Dzielenie ladowni");
		shared_ptr<Ladownia::Zbiornik> zb (a->PodzielLadownie(Objetosc(a->getZajeteMiejsce().value()*0.1)+Objetosc(a->getZajeteMiejsce().value()/2.0),Objetosc(a->getZajeteMiejsce().value()/2.0)));
		assert_true(EXCEPTION_PLACE,zb->isEmpty());
		Log::debug("Zbiornik odlaczony od ladowni: ");
		Log::debug(*zb);
		Log::debug("Ladownia po podzieleniu: ");
		Log::debug<Ladownia>(*a);
	}catch(OgolnyWyjatek& e){
		Log::error("Wykryto wyjatek:");
		Log::error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}

bool Testy::test_tworzenieObiektow(){
	startTestModul("Tworzenie Obiektow");
	try{
		ObiektInfo& p = Aplikacja::getInstance().getStatek(Klucz(IdType(1),Poziom(1)));
		Log::debug( "Klasa info:");
		Log::debug<ObiektInfo>(p);
		shared_ptr<Obiekt>o (p.TworzEgzemplarz(Ilosc(8)));
		if(assert_false(EXCEPTION_PLACE, o!=nullptr))
		{
			assert_false(EXCEPTION_PLACE, o->getIlosc()==Ilosc(8));
			Log::debug( "Stworzony obiekt:");
			Log::debug<Obiekt>(*o);
		}
	}catch(OgolnyWyjatek& e){
		Log::error("Wykryto wyjatek:");
		Log::error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}
bool Testy::test_KlasaObiektList(){
	startTestModul("Operacje na klasie ObiektList");
	ObiektList<Statek> lista;
	ObiektList<Statek> listaDruga;
	Statek *a = nullptr;
	Statek *b = nullptr;
	Statek *c = nullptr;
	Statek *d = nullptr;
	try{
		a = tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(8));
		lista.add(a);	
		Log::debug("Dodano do kontenera");
		Log::debug<Statek>(*a);

		b = tworzStatek(Klucz(IdType(2),Poziom(1)),Ilosc(8));
		lista.add(b);	
		Log::debug("Dodano do kontenera");
		Log::debug<Statek>(*b);

		c = tworzStatek(Klucz(IdType(3),Poziom(1)),Ilosc(8));
		lista.add(c);
		Log::debug("Dodano do kontenera");
		Log::debug<Statek>(*c);

		d = tworzStatek(Klucz(IdType(4),Poziom(1)),Ilosc(8));
		lista.add(d);
		Log::debug("Dodano do kontenera");
		Log::debug<Statek>(*d);

		Log::debug("Zawartoœæ kontenera");
		Log::debug(lista);
		Log::debug("Pobranie listy obiektow");
		auto l = lista.rawObiektList();
		assert_true(EXCEPTION_PLACE,l.empty());
		Log::debug("Ilosc elementow:");
		Log::debug(Ilosc(static_cast<long double>(l.size())));
		for( auto a : l ){
			Log::debug<Statek>(*a);
		}
		Log::debug("Pobranie listy kluczy");
		auto r = lista.rawKluczList();
		assert_true(EXCEPTION_PLACE,r.empty());
		Log::debug("Ilosc elementow:");
		Log::debug(Ilosc(static_cast<long double>(r.size())));
		for( auto a : r ){
			Log::debug(a);
		}

		Statek& sTmp1 = lista.get(Klucz(IdType( 2 ),Poziom( 1 )));
		assert_false(EXCEPTION_PLACE,sTmp1.getId()==IdType( 2 ));
		assert_false(EXCEPTION_PLACE,sTmp1.getPoziom()==Poziom( 1 ));
		Log::debug("Pobranie z kontenera: ");
		Log::debug<Statek>(sTmp1);
		Log::debug("Usuniecie z kontenera wartosci o kluczu: ");
		Log::debug(Klucz(IdType( 1 ),Poziom( 1 )));
		assert_false(EXCEPTION_PLACE,lista.del(Klucz(IdType( 1 ),Poziom( 1 ))));
		Log::debug("Zawartoœæ kontenera po usunieciu");
		Log::debug(lista);
		Log::debug("Pobranie i jednoszesne usuniecie z kontenera wartosci o kluczu:");
		Log::debug(Klucz(IdType( 4 ),Poziom( 1 )));
		Statek* sTmp2 = lista.getAndDel(Klucz(IdType( 4 ),Poziom( 1 )));
		assert_false(EXCEPTION_PLACE,sTmp2->getId()==IdType( 4 ));
		assert_false(EXCEPTION_PLACE,sTmp2->getPoziom()==Poziom( 1 ));
		Log::debug<Statek>(*sTmp2);
		delete sTmp2;
		Log::debug("Zawartoœæ kontenera");
		Log::debug(lista);
		Log::debug("Pobranie listy obiektow");
		l = lista.rawObiektList();
		assert_true(EXCEPTION_PLACE,l.empty());
		Log::debug("Ilosc elementow:");
		Log::debug(Ilosc(static_cast<long double>(l.size())));
		for( auto a : l ){
			Log::debug<Statek>(*a);
		}
		Log::debug("Pobranie listy kluczy");
		r = lista.rawKluczList();
		assert_true(EXCEPTION_PLACE,r.empty());
		Log::debug("Ilosc elementow:");
		Log::debug(Ilosc(static_cast<long double>(r.size())));
		for( auto a : r ){
			Log::debug(a);
		}
		Log::debug("Przenoszenie jednej sztuki obiektu o kluczu");
		Log::debug(r.front());
		Log::debug("do drugiego kontenera.");
		ObiektList<Statek>::move(r.front(),Ilosc(1),lista,listaDruga);
		assert_false(EXCEPTION_PLACE,listaDruga.size()==1);
		Log::debug("Zawartoœæ kontenera");
		Log::debug(lista);
		Log::debug("Zawartoœæ drugiego kontenera");
		Log::debug(listaDruga);
		Log::debug("Przenoszenie calego obiektu o kluczu");
		Log::debug(r.front());
		Log::debug("do drugiego kontenera.");
		ObiektList<Statek>::move(r.front(),lista,listaDruga);
		assert_false(EXCEPTION_PLACE,listaDruga.size()==1);
		Log::debug("Zawartoœæ kontenera");
		Log::debug(lista);
		Log::debug("Zawartoœæ drugiego kontenera");
		Log::debug(listaDruga);
		Log::debug("Rozmiar drugiej listy:");
		Log::debug(Ilosc(static_cast<long double>(listaDruga.size())));
		Log::debug("Czyszczenie kontenera");
		listaDruga.clear();
		assert_false(EXCEPTION_PLACE,listaDruga.isEmpty());
		Log::debug("Zawartoœæ drugiego kontenera po wyczyszceniu");
		Log::debug(listaDruga);
		Log::debug("Test Zakoñczony powodzeniem.");
	}catch(OgolnyWyjatek& e){
		Log::error("Wykryto wyjatek:");
		Log::error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}

bool Testy::test_wymagan(){
	startTestModul("Test Wymagan");
	try{
		shared_ptr<Statek> a( tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(8)) );
		auto t = a->PobierzKoszty();
		for(auto e : t){
			Log::debug<Surowce>(*e);
		}
		assert_false(EXCEPTION_PLACE,t[0]->getIlosc()==Ilosc(120000.0));
		assert_false(EXCEPTION_PLACE,t[1]->getIlosc()==Ilosc(4000.0));
		auto w = a->PobierzWarunki();
		for(auto e : w){
			Log::debug<ObiektBaseInfo>(*e);
		}
		assert_false(EXCEPTION_PLACE,w[0]->getPoziom()==Poziom(25));
		assert_false(EXCEPTION_PLACE,w[1]->getPoziom()==Poziom(5));

	}catch(OgolnyWyjatek& e){
		Log::error("Wykryto wyjatek:");
		Log::error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}