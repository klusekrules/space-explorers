#include "Testy.h"

Testy::Testy(){
	locale pl ("Polish");
	locale::global (pl);
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
string Testy::modulName;


void Testy::startTest(){
	bledyGlobal=0;
	testyGlobal=0;
	Log::getInstance().info("----------------------------------------------");
	Log::getInstance().info("              Rozpocz�cie test�w               ");
	Log::getInstance().info("----------------------------------------------");
}

void Testy::startTestModul(string name){
	modulName = name;
	bledy=0;
	testy=0;
	Log::getInstance().info("----------------------------------------------");
	Log::getInstance().info("           Rozpocz�cie test�w modu�u           ");
	Log::getInstance().info(Testy::modulName);
	Log::getInstance().info("----------------------------------------------");
}
bool Testy::assert_false( const Tekst& tPlik, const IdType& iLinia, bool a ){
	++testy;
	++testyGlobal;
	if(!a){
		Log::getInstance().error("Wykryto niepoprawny rezultat testu");
		Log::getInstance().error("Plik:");
		Log::getInstance().error( tPlik );
		Log::getInstance().error("Linia:");
		Log::getInstance().error( iLinia );
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
		Log::getInstance().error("Wykryto niepoprawny rezultat testu");
		Log::getInstance().error("Plik:");
		Log::getInstance().error( tPlik );
		Log::getInstance().error("Linia:");
		Log::getInstance().error( iLinia );
		++bledy;
		++bledyGlobal;
		return false;
	}
	return true;
}

bool Testy::endTestModul(){	
	stringstream s;
	s<<"Liczba Test�w: "<<testy<<" , Liczba B��d�w: "<<bledy;
	Log::getInstance().info("----------------------------------------------");
	Log::getInstance().info("           Zako�czenie test�w modu�u           ");
	Log::getInstance().info(modulName);
	Log::getInstance().info(s.str());
	Log::getInstance().info("----------------------------------------------");
	return bledy==0;
}

bool Testy::endTestModulImidaite(){
	stringstream s;
	s<<"Wykryto b��d krytyczny.\nPrzerwno dalsze dzia�anie metody testujacej.";
	Log::getInstance().info("----------------------------------------------");
	Log::getInstance().info("           Zako�czenie test�w modu�u           ");
	Log::getInstance().info(modulName);
	Log::getInstance().info(s.str());
	Log::getInstance().info("----------------------------------------------");
	++fatalErrorGlobal;
	return false;
}

void Testy::endTest(){
	stringstream s,t;
	s<<"Przeprowadzono Test�w: "<<testyGlobal<<" , Wykryto B��d�w: "<<bledyGlobal;
	t << "B��dy krytyczne: " << fatalErrorGlobal;
	Log::getInstance().info("----------------------------------------------");
	Log::getInstance().info("              Zako�czenie test�w               ");
	Log::getInstance().info(s.str());
	Log::getInstance().info(t.str());
	Log::getInstance().info("----------------------------------------------");
}

bool Testy::ladowanie_danych()const{
	/* Generowanie danych */

	//Statek
	startTestModul("�adowanie Danych");
	try{
		assert_false( EXCEPTION_PLACE , Aplikacja::getInstance().WczytajDane("test.xml") );
		shared_ptr<Statek> t( this->tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(1)));
		Log::getInstance().debug(*t);
	}catch(OgolnyWyjatek& e){
		Log::getInstance().error("Wykryto wyj�tek:");
		Log::getInstance().error(e);
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
		Log::getInstance().debug( "Stworzony obiekt:");
		Log::getInstance().debug(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie uda�o si� utworzy� obiektu"));
	}
	return s;
}

Surowce* Testy::tworzSurowce(const Klucz& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu){
	Surowce* s = Aplikacja::getInstance().getSurowce(id).TworzEgzemplarz(i);
	if(assert_false(EXCEPTION_PLACE, s!=nullptr))
	{
		assert_false(EXCEPTION_PLACE, s->getIlosc()==i);
		assert_false(EXCEPTION_PLACE, s->ID()==id);
		Log::getInstance().debug( "Stworzony obiekt:");
		Log::getInstance().debug(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie uda�o si� utworzy� obiektu"));
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

		}else{
			Log::getInstance().warn("Nie mo�na kontynuowa� test�w!");
		}
		endTest();
	}catch( OgolnyWyjatek & e ){
		Log::getInstance().error(e.toString());
	}
}

bool Testy::test_KlasaNiepoprawneParametryFunkcji()const{
	startTestModul("Test klasy NiepoprawneParametryFunkcji");
	try{
		Ilosc temp(5);
		shared_ptr<Statek> t( this->tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(1)));
		Statek& tmp = *t;
		throw NiepoprawneParametryFunkcji( EXCEPTION_PLACE , tmp , temp );
	}
	catch( const NiepoprawneParametryFunkcji& e ){
		assert_true(EXCEPTION_PLACE , e.getParametry().isEmpty());
		Log::getInstance().debug(e.getParametry());
		Log::getInstance().debug("Zawartosc klasy NiepoprawneParametryFunkcji = ");
		Log::getInstance().debug(e.generujKomunikat());
	}
	return endTestModul();
}

bool Testy::test_KlasaLadownia()const{
	startTestModul("Test Klasy Ladownia");
	try{
		shared_ptr<Statek> a (tworzStatek(Klucz(IdType(4),Poziom(1)),Ilosc(8)));
		Log::getInstance().debug("Pojemnosc Maksymalna:");
		Log::getInstance().debug(a->getPojemnoscMax());
		shared_ptr<Statek> b (tworzStatek(Klucz(IdType(1),Poziom(1)),Ilosc(150)));
		assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*b));
		shared_ptr<Surowce> c (tworzSurowce(Klucz(IdType(2),Poziom(3)),Ilosc(20)));
		assert_false(EXCEPTION_PLACE,c->czyTypPrzyrostowy());
		assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*c));
		shared_ptr<Surowce> d (tworzSurowce(Klucz(IdType(4),Poziom(1)),Ilosc(20)));
		assert_true(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*d));
		Log::getInstance().debug("Zawartosc po dodaniu obiektu: ");
		Log::getInstance().debug(*a);
		assert_false(EXCEPTION_PLACE,a->getZajeteMiejsce()!=Objetosc(0));
		Log::getInstance().debug("Zajete miejsce: ");
		Log::getInstance().debug(a->getZajeteMiejsce());
		Log::getInstance().debug("Dzielenie ladowni");
		shared_ptr<Ladownia::Zbiornik> zb (a->PodzielLadownie(Objetosc(a->getZajeteMiejsce().value()*0.1)+Objetosc(a->getZajeteMiejsce().value()/2.0),Objetosc(a->getZajeteMiejsce().value()/2.0)));
		assert_true(EXCEPTION_PLACE,zb->isEmpty());
		Log::getInstance().debug("Zbiornik odlaczony od ladowni: ");
		Log::getInstance().debug(*zb);
		Log::getInstance().debug("Ladownia po podzieleniu: ");
		Log::getInstance().debug(*a);
	}catch(OgolnyWyjatek& e){
		Log::getInstance().error("Wykryto wyjatek:");
		Log::getInstance().error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}

bool Testy::test_tworzenieObiektow()const{
	startTestModul("Tworzenie Obiektow");
	try{
		ObiektInfo& p = Aplikacja::getInstance().getStatek(Klucz(IdType(1),Poziom(1)));
		Log::getInstance().debug( "Klasa info:");
		Log::getInstance().debug(p);
		shared_ptr<Obiekt>o (p.TworzEgzemplarz(Ilosc(8)));
		if(assert_false(EXCEPTION_PLACE, o!=nullptr))
		{
			assert_false(EXCEPTION_PLACE, o->getIlosc()==Ilosc(8));
			Log::getInstance().debug( "Stworzony obiekt:");
			Log::getInstance().debug(*o);
		}
	}catch(OgolnyWyjatek& e){
		Log::getInstance().error("Wykryto wyjatek:");
		Log::getInstance().error(e);
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
		Log::getInstance().debug("Dodano do kontenera");
		Log::getInstance().debug(*a);

		b = tworzStatek(Klucz(IdType(2),Poziom(1)),Ilosc(8));
		lista.add(b);	
		Log::getInstance().debug("Dodano do kontenera");
		Log::getInstance().debug(*b);

		c = tworzStatek(Klucz(IdType(3),Poziom(1)),Ilosc(8));
		lista.add(c);
		Log::getInstance().debug("Dodano do kontenera");
		Log::getInstance().debug(*c);

		d = tworzStatek(Klucz(IdType(4),Poziom(1)),Ilosc(8));
		lista.add(d);
		Log::getInstance().debug("Dodano do kontenera");
		Log::getInstance().debug(*d);

		Log::getInstance().debug("Zawarto�� kontenera");
		Log::getInstance().debug(lista);
		Log::getInstance().debug("Pobranie listy obiektow");
		auto l = lista.rawObiektList();
		assert_true(EXCEPTION_PLACE,l.empty());
		Log::getInstance().debug("Ilosc elementow:");
		Log::getInstance().debug(Ilosc(static_cast<long double>(l.size())));
		for( auto a : l ){
			Log::getInstance().debug(*a);
		}
		Log::getInstance().debug("Pobranie listy kluczy");
		auto r = lista.rawKluczList();
		assert_true(EXCEPTION_PLACE,r.empty());
		Log::getInstance().debug("Ilosc elementow:");
		Log::getInstance().debug(Ilosc(static_cast<long double>(r.size())));
		for( auto a : r ){
			Log::getInstance().debug(a);
		}

		Statek& sTmp1 = lista.get(Klucz(IdType( 2 ),Poziom( 1 )));
		assert_false(EXCEPTION_PLACE,sTmp1.getId()==IdType( 2 ));
		assert_false(EXCEPTION_PLACE,sTmp1.getPoziom()==Poziom( 1 ));
		Log::getInstance().debug("Pobranie z kontenera: ");
		Log::getInstance().debug(sTmp1);
		Log::getInstance().debug("Usuniecie z kontenera wartosci o kluczu: ");
		Log::getInstance().debug(Klucz(IdType( 1 ),Poziom( 1 )));
		assert_false(EXCEPTION_PLACE,lista.del(Klucz(IdType( 1 ),Poziom( 1 ))));
		Log::getInstance().debug("Zawarto�� kontenera po usunieciu");
		Log::getInstance().debug(lista);
		Log::getInstance().debug("Pobranie i jednoszesne usuniecie z kontenera wartosci o kluczu:");
		Log::getInstance().debug(Klucz(IdType( 4 ),Poziom( 1 )));
		Statek* sTmp2 = lista.getAndDel(Klucz(IdType( 4 ),Poziom( 1 )));
		assert_false(EXCEPTION_PLACE,sTmp2->getId()==IdType( 4 ));
		assert_false(EXCEPTION_PLACE,sTmp2->getPoziom()==Poziom( 1 ));
		Log::getInstance().debug(*sTmp2);
		delete sTmp2;
		Log::getInstance().debug("Zawarto�� kontenera");
		Log::getInstance().debug(lista);
		Log::getInstance().debug("Pobranie listy obiektow");
		l = lista.rawObiektList();
		assert_true(EXCEPTION_PLACE,l.empty());
		Log::getInstance().debug("Ilosc elementow:");
		Log::getInstance().debug(Ilosc(static_cast<long double>(l.size())));
		for( auto a : l ){
			Log::getInstance().debug(*a);
		}
		Log::getInstance().debug("Pobranie listy kluczy");
		r = lista.rawKluczList();
		assert_true(EXCEPTION_PLACE,r.empty());
		Log::getInstance().debug("Ilosc elementow:");
		Log::getInstance().debug(Ilosc(static_cast<long double>(r.size())));
		for( auto a : r ){
			Log::getInstance().debug(a);
		}
		Log::getInstance().debug("Przenoszenie jednej sztuki obiektu o kluczu");
		Log::getInstance().debug(r.front());
		Log::getInstance().debug("do drugiego kontenera.");
		ObiektList<Statek>::move(r.front(),Ilosc(1),lista,listaDruga);
		assert_false(EXCEPTION_PLACE,listaDruga.size()==1);
		Log::getInstance().debug("Zawarto�� kontenera");
		Log::getInstance().debug(lista);
		Log::getInstance().debug("Zawarto�� drugiego kontenera");
		Log::getInstance().debug(listaDruga);
		Log::getInstance().debug("Przenoszenie calego obiektu o kluczu");
		Log::getInstance().debug(r.front());
		Log::getInstance().debug("do drugiego kontenera.");
		ObiektList<Statek>::move(r.front(),lista,listaDruga);
		assert_false(EXCEPTION_PLACE,listaDruga.size()==1);
		Log::getInstance().debug("Zawarto�� kontenera");
		Log::getInstance().debug(lista);
		Log::getInstance().debug("Zawarto�� drugiego kontenera");
		Log::getInstance().debug(listaDruga);
		Log::getInstance().debug("Rozmiar drugiej listy:");
		Log::getInstance().debug(Ilosc(static_cast<long double>(listaDruga.size())));
		Log::getInstance().debug("Czyszczenie kontenera");
		listaDruga.clear();
		assert_false(EXCEPTION_PLACE,listaDruga.isEmpty());
		Log::getInstance().debug("Zawarto�� drugiego kontenera po wyczyszceniu");
		Log::getInstance().debug(listaDruga);
		Log::getInstance().debug("Test Zako�czony powodzeniem.");
	}catch(OgolnyWyjatek& e){
		Log::getInstance().error("Wykryto wyjatek:");
		Log::getInstance().error(e);
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
			Log::getInstance().debug(*e);
		}
		assert_false(EXCEPTION_PLACE,t[0]->getIlosc()==Ilosc(120000.0));
		assert_false(EXCEPTION_PLACE,t[1]->getIlosc()==Ilosc(4000.0));
		auto w = a->PobierzWarunki();
		for(auto e : w){
			Log::getInstance().debug(*e);
		}
		assert_false(EXCEPTION_PLACE,w[0]->getPoziom()==Poziom(25));
		assert_false(EXCEPTION_PLACE,w[1]->getPoziom()==Poziom(5));

	}catch(OgolnyWyjatek& e){
		Log::getInstance().error("Wykryto wyjatek:");
		Log::getInstance().error(e);
		return endTestModulImidaite();
	}
	return endTestModul();
}