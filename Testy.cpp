#include "Testy.h"

Testy::Testy(){
	locale pl ("Polish");
	locale::global (pl);
}


Testy::~Testy(){
	for( auto i : statki ){
		if(i.second!=nullptr)
			delete i.second;
	}
	for( auto i : surowce ){
		if(i.second!=nullptr)
			delete i.second;
	}
}

unsigned int Testy::bledy(0);
unsigned int Testy::testy(0);
unsigned int Testy::bledyGlobal(0);
unsigned int Testy::testyGlobal(0);
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
void Testy::endTest(){
	stringstream s;
	s<<"Przeprowadzono Testow: "<<testyGlobal<<" , Wykryto Bledow: "<<bledyGlobal;
	Log::info("----------------------------------------------");
	Log::info("              Zakonczenie testow               ");
	Log::info(s.str());
	Log::info("----------------------------------------------");
}

bool Testy::ladowanie_danych(){
	/* Generowanie danych */

	//Statek
	startTestModul("Ladowanie Danych");
	try{
		for(int i = 1; i <= 10; ++i){
			stringstream str;
			str<<i;
			StatekInfo* s = new StatekInfo( 
				ObiektInfo( Masa(124*i) , Objetosc(150*i*i) , Powierzchnia(10*i) , ObiektBaseInfo( Info( Tekst("Tytul statku nr: ") += str.str(), Tekst("Opis statku nr: ") += str.str(), IdType( i ) , Wymagania() ), Poziom(1) ) ),
				JednostkaLatajacaInfo( Info( Tekst("Wlasciwosci silnika tytul nr: ") += str.str(), Tekst("Wlasciwosci silnika opis nr: ") += str.str(), IdType( i * 10 + 1 ) , Wymagania() ) , Klucz( IdType(i * 10 + 4) , Poziom(1) ), MocSilnika(300000), ZuzyciePaliwa(1600), Masa(135) ),
				JednostkaAtakujacaInfo( Info( Tekst("Wlasciwosci bojowe tytul nr: ") += str.str(), Tekst("Wlasciwosci bojowe opis nr: ") += str.str(), IdType( i * 10 + 2 ) , Wymagania() ) , Obrazenia(130), Obrazenia(600), Obrazenia(400) ),
				LadowniaInfo( Objetosc(50*i*i) , Info( Tekst("Ladownia tytul nr: ") += str.str(), Tekst(" Ladownia opis nr: ") += str.str(), IdType( i * 10 + 3 ) , Wymagania() ) )
				);
			if(!assert_false( EXCEPTION_PLACE , setStatek(s))){
				Log::debug("Nie udalo sie dodac statku: ");
				Log::debug<StatekInfo>( *s );
				delete s;
			}else{
				Log::debug("Dodano statek: ");
				Log::debug<StatekInfo>( *s );
			}
		}
		for(int i = 1; i <= 3; ++i){
			stringstream str;
			str<<i;
			SurowceInfo * s = new SurowceInfo(
				ObiektInfo( Masa(i*i) , Objetosc(i) , Powierzchnia(1) , ObiektBaseInfo( Info( Tekst("Tytul surowca nr: ") += str.str(), Tekst("Opis surowca nr: ") += str.str(), IdType( 10+i ) , Wymagania() ), Poziom(1) ) )
				);
			if(!assert_false( EXCEPTION_PLACE , setSurowce(s))){
				Log::debug("Nie udalo sie dodac statku: ");
				Log::debug<SurowceInfo>( *s );
				delete s;
			}else{
				Log::debug("Dodano surowiec: ");
				Log::debug<SurowceInfo>( *s );
			}
		}
	}catch(OgolnyWyjatek& e){
		Log::error("Wykryto wyjatek:");
		Log::error(e);
		endTestModul();
		return false;
	}
	return endTestModul();
}

bool Testy::setStatek(StatekInfo* statek){
	if(statki.find(statek->getId()) != statki.end())
		return false;
	statki[statek->getId()] = statek;
	return true;
}

StatekInfo& Testy::getStatek(const IdType& id)const throw (NieznalezionoObiektu) {
	auto iter = statki.find(id);
	if(iter==statki.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
	return *(iter->second);
}

Statek* Testy::tworzStatek(const IdType& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu){
	Statek* s = getStatek(id).TworzEgzemplarz(i);
	if(assert_false(EXCEPTION_PLACE, s!=nullptr))
	{
		assert_false(EXCEPTION_PLACE, s->getIlosc()==i);
		assert_false(EXCEPTION_PLACE, s->getId()==id);
		Log::debug( "Stworzony obiekt:");
		Log::debug<Obiekt>(*s);
	}else{
		throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Tworzenie Obiektu"),Tekst("Nie udalo sie utworzyc obiektu"));
	}
	return s;
}

bool Testy::setSurowce(SurowceInfo* surowiec){
	if(surowce.find(surowiec->getId()) != surowce.end())
		return false;
	surowce[surowiec->getId()] = surowiec;
	return true;
}

SurowceInfo& Testy::getSurowce(const IdType& id)const throw (NieznalezionoObiektu) {
	auto iter = surowce.find(id);
	if(iter==surowce.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
	return *(iter->second);
}

Surowce* Testy::tworzSurowce(const IdType& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu){
	Surowce* s = getSurowce(id).TworzEgzemplarz(i);
	if(assert_false(EXCEPTION_PLACE, s!=nullptr))
	{
		assert_false(EXCEPTION_PLACE, s->getIlosc()==i);
		assert_false(EXCEPTION_PLACE, s->getId()==id);
		Log::debug( "Stworzony obiekt:");
		Log::debug<Obiekt>(*s);
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
	Statek *a = nullptr;
	try{
		a = tworzStatek(IdType(10),Ilosc(8));
		Log::debug("Pojemnosc Maksymalna:");
		Log::debug(a->getPojemnoscMax());
		Statek *b = tworzStatek(IdType(1),Ilosc(150));

		try{
		assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*b));
		}catch(...){
			delete b;
			throw;
		}
		delete b;
		Surowce* c = tworzSurowce(IdType(11),Ilosc(20));
		try{
		assert_false(EXCEPTION_PLACE,a->DodajObiektDoLadowni(*c));
		}catch(...){
			delete c;
			throw;
		}
		delete c;
		Log::debug("Zawartosc po dodaniu obiektu: ");
		Log::debug<Ladownia>(*a);
		assert_false(EXCEPTION_PLACE,a->getZajeteMiejsce()!=Objetosc(0));
		Log::debug("Zajete miejsce: ");
		Log::debug(a->getZajeteMiejsce());
		Log::debug("Dzielenie ladowni");
		Ladownia::Zbiornik* zb = a->PodzielLadownie(Objetosc(3000)+Objetosc(a->getPojemnoscMax().value()/2.0),Objetosc(a->getPojemnoscMax().value()/2.0));
		assert_true(EXCEPTION_PLACE,zb->isEmpty());
		Log::debug("Zbiornik odlaczony od ladowni: ");
		Log::debug(*zb);
		delete zb;
		Log::debug("Ladownia po podzieleniu: ");
		Log::debug<Ladownia>(*a);
	}catch(OgolnyWyjatek& e){
		Log::error("Wykryto wyjatek:");
		Log::error(e);
		if(a!=nullptr) delete a;
		endTestModul();
		return false;
	}
	if(a!=nullptr) delete a;
	return endTestModul();
}

bool Testy::test_tworzenieObiektow(){
	startTestModul("Tworzenie Obiektow");
	Obiekt *o = nullptr;
	try{
	ObiektInfo& p = getStatek(IdType(5));
	Log::debug( "Klasa info:");
	Log::debug<ObiektInfo>(p);
	o = p.TworzEgzemplarz(Ilosc(8));
	if(assert_false(EXCEPTION_PLACE, o!=nullptr))
	{
		assert_false(EXCEPTION_PLACE, o->getIlosc()==Ilosc(8));
		Log::debug( "Stworzony obiekt:");
		Log::debug<Obiekt>(*o);
	}
	}catch(OgolnyWyjatek& e){
		Log::error("Wykryto wyjatek:");
		Log::error(e);
		if(o != nullptr)
			delete o;
		endTestModul();
		return false;
	}
	if(o != nullptr)
		delete o;
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
		a = tworzStatek(IdType(1),Ilosc(8));
		lista.add(a);	
		Log::debug("Dodano do kontenera");
		Log::debug<Statek>(*a);

		b = tworzStatek(IdType(2),Ilosc(8));
		lista.add(b);	
		Log::debug("Dodano do kontenera");
		Log::debug<Statek>(*b);

		c = tworzStatek(IdType(3),Ilosc(8));
		lista.add(c);
		Log::debug("Dodano do kontenera");
		Log::debug<Statek>(*c);

		d = tworzStatek(IdType(4),Ilosc(8));
		lista.add(d);
		Log::debug("Dodano do kontenera");
		Log::debug<Statek>(*d);

		Log::debug("Zawartoœæ kontenera");
		Log::debug(lista);
		Log::debug("Pobranie listy obiektow");
		auto l = lista.rawObiektList();
		assert_true(EXCEPTION_PLACE,l.empty());
		Log::debug("Ilosc elementow:");
		Log::debug(Ilosc(l.size()));
		for( auto a : l ){
			Log::debug<Statek>(*a);
		}
		Log::debug("Pobranie listy kluczy");
		auto r = lista.rawKluczList();
		assert_true(EXCEPTION_PLACE,r.empty());
		Log::debug("Ilosc elementow:");
		Log::debug(Ilosc(r.size()));
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
		Log::debug(Ilosc(l.size()));
		for( auto a : l ){
			Log::debug<Statek>(*a);
		}
		Log::debug("Pobranie listy kluczy");
		r = lista.rawKluczList();
		assert_true(EXCEPTION_PLACE,r.empty());
		Log::debug("Ilosc elementow:");
		Log::debug(Ilosc(r.size()));
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
		Log::debug(Ilosc(listaDruga.size()));
		Log::debug("Czyszczenie kontenera");
		listaDruga.clear();
		assert_false(EXCEPTION_PLACE,listaDruga.isEmpty());
		Log::debug("Zawartoœæ drugiego kontenera po wyczyszceniu");
		Log::debug(listaDruga);
		Log::debug("Test Zakoñczony powodzeniem.");
	}catch(OgolnyWyjatek& e){
		Log::error("Wykryto wyjatek:");
		Log::error(e);
		endTestModul();
		return false;
	}
	return endTestModul();
}

/*
Testy::Testy()
	: init(Inicjalizacja::getSingleton())
{
	cout<<"\nPoczatek testu test_ladowaniePlikuXML\n";
	try{
		init->zaladuj("..\\options.xml");
	}catch(ticpp::Exception& ex){
		cout<<ex.what()<<endl;
		throw;
	}
}
*/
/*
void Testy::test_ladowaniePlikuXML(){
	try{
		auto listaSurowcow = init->getSurowceInfo();
		for( auto iter = listaSurowcow.begin() ; iter!= listaSurowcow.end() ; iter++){
			cout<< "\nOpis Surowca:\n"<< (*iter)->toString() << endl;
		}
		auto listaStatkow = init->getStatekInfo();
		for( auto iter = listaStatkow.begin() ; iter!= listaStatkow.end() ; iter++){
			cout<< "\nOpis Statku:\n"<< (*iter)->toString() << endl;
		}
		cout << endl << init->toString() << endl;
	}catch(ticpp::Exception& ex){
		cout<<ex.what()<<endl;
		throw;
	}
	cout<<"\nKoniec testu test_ladowaniePlikuXML\n";
}
void Testy::test_podzialuStatku(){
	cout<<"\nPoczatek testu test_podzialuStatku\nTworzenie Obiektów\n";
	auto transportowiecSI = init->getStatekInfo(0);
	if(transportowiecSI==NULL){
		cout<<"\nNiepowodzenie testu test_podzialuStatku\n";
		return;
	}

	Statek* transportowiec = transportowiecSI->TworzEgzemplarz(2);
	
	cout<<"Utworzono transportowiec:\n"<<transportowiec->toString();
	auto mysliwiecSI = init->getStatekInfo(1);
	if(mysliwiecSI==NULL){
		cout<<"\nNiepowodzenie testu test_podzialuStatku\n";
		delete transportowiec;
		return;
	}

	Statek* mysliwiec = mysliwiecSI->TworzEgzemplarz(2);
	
	cout<<"Utworzono mysliwiec:\n"<<mysliwiec->toString();

	cout<<"\nDodawanie mysliwca do ³adowni transoportowca\n";
	transportowiec->DodajObiektDoLadowni(mysliwiec);
	cout<<"Rezultat:\n"<<transportowiec->toString();

	cout<<"\nRozdzielanie transportowca na dwa obiekty\n";
	Obiekt* podzial = transportowiec->Podziel(1);
	cout<<"Rezultat:\nPierwszy transportowiec\n"<<transportowiec->toString()<<"\nDrugi Transportowiec:\n"<<podzial->toString();

	delete transportowiec;
	delete podzial;

	cout<<"\nKoniec testu test_podzialuStatku\n";
}


void Testy::test_metodyToString(){
}

void Testy::run(){
	/*
	cout <<"START TESTOW"<<endl;
	SPG::IloscJednostek pojemnoscLadowni = 10000.0l;
	Obiekt obiekt( 0.1l , 1.0l , 0.0l);
	Surowce surowce( SPG::typSurowcaStal , 1234.567l, obiekt);
	Surowce surowiecMetal( surowce);
	Surowce surowiecPaliwo( SPG::typSurowcaWodor , 1099.0l, obiekt);
	Surowce surowiecPaliwoDodatkowe( SPG::typSurowcaWodor , 122.0l, obiekt);
	Ladownia ladownia( pojemnoscLadowni);
	
	cout << "Testy klasy Surowce..." <<endl;
	cout << "Obiekt surowiecPaliwo: " <<endl << surowiecPaliwo.toString().str() << endl<< endl;
	cout << "Obiekt surowiecPaliwoDodatkowe: " <<endl << surowiecPaliwoDodatkowe.toString().str() << endl<< endl;
	cout << "Obiekt surowiecMetal: " <<endl << surowiecMetal.toString().str() << endl<< endl;

	try{
		Surowce test;
		cout << "Dodawanie Surowcow... surowiecPaliwo + surowiecPaliwoDodatkowe " << endl;
		test = surowiecPaliwo + surowiecPaliwoDodatkowe;
		cout << "Po dodaniu: "<< endl << test.toString().str() << endl<< endl;

		cout << "Dodawanie Surowcow... surowiecMetal + surowiecPaliwoDodatkowe " << endl;
		test = surowiecMetal +surowiecPaliwo;
		cout << "Po dodaniu: " << test.toString().str() << endl<< endl;

	} catch( NiezgodnyTypSurowca e ){
		cout << e.toString().str() << endl;
	}

	cout << "Testy klasy Ladownia..." <<endl;
	
	try{
		cout << "Dodawanie surowca do ladowni..." <<endl;
		ladownia.DodajObiekt( &surowce);
		cout<< "Zawartosc Ladowni: "<<endl<<ladownia.toString().str()<< endl<< endl;

		ladownia.DodajObiekt( &surowiecPaliwo );
		cout<< "Zawartosc Ladowni: "<<endl<<ladownia.toString().str()<< endl<< endl;

		ladownia.DodajObiekt( &surowiecPaliwoDodatkowe );
		cout<< "Zawartosc Ladowni: "<<endl<<ladownia.toString().str()<< endl<< endl;

		ladownia.DodajObiekt( &surowiecMetal );
		cout<< "Zawartosc Ladowni: "<<endl<<ladownia.toString().str()<< endl<< endl;

		cout<< "Wolne miejsce w ladowni: "<< ladownia.WolneMiejsce() << endl<< endl;

		Obiekt *wsk = ladownia.PobierzObiekt(SPG::typSurowcaStal);
		cout << "Pobieranie surowca z ladowni..." <<endl;
		if(wsk!=NULL){
			Surowce sPobrany( *wsk );
			cout<< "Pobrany surowiec: " <<endl <<sPobrany.toString().str()<< endl<< endl;
			cout<< "Zawartosc Ladowni: "<<endl <<ladownia.toString().str()<< endl<< endl;
		}
		wsk = ladownia.PobierzObiekt(SPG::typSurowcaWodor, 600.0l);
		if(wsk!=NULL){
			Surowce sPobrany2( *wsk );
			cout<< "Pobrany surowiec: " <<endl <<sPobrany2.toString().str()<< endl<< endl;
			cout<< "Zawartosc Ladowni: "<<endl <<ladownia.toString().str() << endl<< endl;
			delete wsk;
		}
		cout<< "Wolne miejsce w ladowni: "<< ladownia.WolneMiejsce() <<endl;

		cout<< "Sprawdzanie metody SprawdzIloscSurowca..."<<endl;
		cout<< "Ilosc surowca typu Paliwo: "<< ladownia.SprawdzIloscObiektow(SPG::typSurowcaWodor)<<endl;
		cout<< "Ilosc surowca typu Metal: " << ladownia.SprawdzIloscObiektow(SPG::typSurowcaStal) <<endl;
		
	} catch( NiezgodnyTypSurowca e ){
		cout << e.toString().str() << endl<< endl;
	}

	cout << "Testy klasy SurowceInfo..." <<endl;
	cout << "Tworzenie klasy..." <<endl;

	//SurowceInfo sInfo( SPG::typSurowcaDeuter , SPG::typSurowcaDeuterNazwa , SPG::typSurowcaDeuterOpis );

	//cout << "Zawartosc klasy : " <<endl << sInfo.toString().str()<< endl;
	char napis[21];
	LoadString( NULL,102, napis ,20);
	cout<<"Test Pobierania danych plikow resource.\nPobrany napis: "<< napis <<endl;
	cout<<"Test Tworzenia statku";
	
	Statek statek;
	cout << statek.toString().str()<< endl<< endl;
	
	cout <<"KONIEC TESTOW"<<endl;
}*/