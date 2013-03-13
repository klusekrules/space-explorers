#include "Biblioteki.h"
#include "Testy.h"
#include "Tekst.h"
#include "IdType.h"
#include "Klucz.h"
#include "Base.h"
#include "ObiektBase.h"
#include "Obiekt.h"
#include "ObiektList.hpp"
#include "ObiektInfo.h"
#include "Ladownia.h"
#include "LadowniaInfo.h"

Testy::Testy(){
	locale pl ("Polish");
	locale::global (pl);
}


Testy::~Testy(){
}


void Testy::run(){
	test_podstawoweDzialaniaKlas();
	test_KlasaObiektList();
	test_tworzenieObiektow();
	test_KlasaLadownia();
	test_KlasaNiepoprawneParametryFunkcji();
}

bool Testy::test_KlasaNiepoprawneParametryFunkcji(){
	bool result = false;
	bool error = false;
	Log::debug("Test Klasy NiepoprawneParametryFunkcji!");
	try{
		Ilosc temp(5);
		Objetosc tmp( 10.7 );
		throw NiepoprawneParametryFunkcji( EXCEPTION_PLACE , tmp , temp );
	}
	catch( const NiepoprawneParametryFunkcji& e ){
		Log::debug("Zawartosc klasy NiepoprawneParametryFunkcji = ");
		Log::debug(e.generujKomunikat());
	}
	Log::debug("Test Klasy NiepoprawneParametryFunkcji zakoñczony powodzeniem.");
	return true;
}

bool Testy::test_KlasaLadownia(){
	bool result = false;
	bool error = false;
	Log::debug("Test Klasy £adownia!");
	Log::debug("Zawartoœæ Klasy po utworzeniu");
	Info iladInfo(Tekst("Ladownia"),Tekst("Opis Ladowni"),IdType(54),Wymagania());
	LadowniaInfo ladInfo(Objetosc(100),iladInfo);
	Ladownia ladownia( ladInfo );
	Log::debug(ladownia);
	Log::debug("Pobieranie wlasnosci ladowi");
	Log::debug("Zajete miejsce:");
	Log::debug(ladownia.getZajeteMiejsce());
	Log::debug("Pojemnosc Maksymalna:");
	Log::debug(ladownia.getPojemnoscMax());
	Log::debug("Test dodawania elementów do ³adowni.");
	Info iInfo(Tekst("Tytul"),Tekst("Opis"),IdType(14),Wymagania());
	ObiektInfo *ptr = new ObiektInfo( Masa(1) , Objetosc(1) , Powierzchnia(1), Poziom(0) , iInfo);
	Obiekt *o = ptr->TworzEgzemplarz(Ilosc(30));
	ObiektInfo *ptr2 = new ObiektInfo( Masa(1) , Objetosc(5) , Powierzchnia(1), Poziom(0) , iInfo);
	Obiekt *o2 = ptr2->TworzEgzemplarz(Ilosc(6));
	ladownia.DodajObiektDoLadowni(*o);
	ladownia.DodajObiektDoLadowni(*o2);
	Log::debug("Zawartosc po dodaniu obiektu: ");
	Log::debug(ladownia);
	delete o2;
	delete o;
	Log::debug("Dzielenie ladowni");
	Ladownia::Zbiornik* zb = ladownia.PodzielLadownie(Objetosc(40),Objetosc(35));
	Log::debug("Zbiornik odlaczony od ladowni: ");
	Log::debug(*zb);
	delete zb;
	Log::debug("Ladownia po podzieleniu: ");
	Log::debug(ladownia);
	delete ptr;
	delete ptr2;
	Log::debug("Test Klasy £adownia zakoñczony powodzeniem.");
	return error;
}

bool Testy::test_tworzenieObiektow(){
	bool result = false;
	bool error = false;
	Log::debug("Test tworzenia egzemplazy obiektow");
	ObiektInfo * ptr = new ObiektInfo( Masa(0) , Objetosc(0) , Powierzchnia(0) , Poziom( 2 ), Info(Tekst("Napis"), Tekst("Opis"), IdType(1),Wymagania()) );
	Log::debug( "Klasa info:");
	Log::debug<ObiektInfo>(*ptr);
	Obiekt *o = ptr->TworzEgzemplarz(Ilosc(8));
	Log::debug( "Stworzony obiekt:");
	Log::debug<Obiekt>(*o);
	delete o;
	delete ptr;	
	Log::debug("Test Zakoñczony powodzeniem.");
	return error;
}
bool Testy::test_KlasaObiektList(){
	bool result = false;
	bool error = false;
	cout << boolalpha;
	Log::debug("Test klasy: ");
	Log::debug(ObiektList<Obiekt>::className());
	ObiektList<Obiekt> lista;
	ObiektList<Obiekt> listaDruga;
	ObiektInfo oiA( Masa(0), Objetosc(0), Powierzchnia(0), Poziom(2), Info(Tekst("A"),Tekst("A"),IdType(10),Wymagania()));
	ObiektInfo oiB( Masa(0), Objetosc(0), Powierzchnia(0), Poziom(3), Info(Tekst("B"),Tekst("B"),IdType(10),Wymagania()));
	ObiektInfo oiC( Masa(0), Objetosc(0), Powierzchnia(0), Poziom(2), Info(Tekst("C"),Tekst("C"),IdType(10),Wymagania()));
	ObiektInfo oiD( Masa(0), Objetosc(0), Powierzchnia(0), Poziom(2), Info(Tekst("D"),Tekst("D"),IdType(11),Wymagania()));
	Obiekt *a = oiA.TworzEgzemplarz(Ilosc(4));
	Obiekt *b = oiB.TworzEgzemplarz(Ilosc(4));
	Obiekt *c = oiC.TworzEgzemplarz(Ilosc(4));
	Obiekt *d = oiD.TworzEgzemplarz(Ilosc(4));
	Log::debug("Dodano do kontenera");
	Log::debug<Obiekt>(*a);
	lista.add(a);	
	Log::debug("Dodano do kontenera");
	Log::debug<Obiekt>(*b);
	lista.add(b);	
	Log::debug("Dodano do kontenera");
	Log::debug<Obiekt>(*c);
	lista.add(c);
	Log::debug("Dodano do kontenera");
	Log::debug<Obiekt>(*d);
	lista.add(d);
	Log::debug("Zawartoœæ kontenera");
	Log::debug(lista);
	Log::debug("Pobranie listy obiektow");
	auto l = lista.rawObiektList();
	Log::debug("Ilosc elementow:");
	Log::debug(Ilosc(l.size()));
	for( auto a : l ){
		Log::debug<Obiekt>(*a);
	}
	Log::debug("Pobranie listy kluczy");
	auto r = lista.rawKluczList();
	Log::debug("Ilosc elementow:");
	Log::debug(Ilosc(r.size()));
	for( auto a : r ){
		Log::debug(a);
	}

	Log::debug("Pobranie z kontenera: ");
	Log::debug<Obiekt>(lista.get(Klucz(IdType( 10 ),Poziom( 2 ))));
	Log::debug("Usuniecie z kontenera wartosci o kluczu: ");
	Log::debug(Klucz(IdType( 10 ),Poziom( 2 )));
	lista.del(Klucz(IdType( 10 ),Poziom( 2 )));
	Log::debug("Zawartoœæ kontenera");
	Log::debug(lista);
	Log::debug("Pobranie i jednoszesne usuniecie z kontenera wartosci o kluczu:");
	Log::debug(Klucz(IdType( 10 ),Poziom( 3 )));
	auto tmp = lista.getAndDel(Klucz(IdType( 10 ),Poziom( 3 )));
	Log::debug<Obiekt>(*tmp);
	delete tmp;
	Log::debug("Zawartoœæ kontenera");
	Log::debug(lista);
	Log::debug("Pobranie listy obiektow");
	l = lista.rawObiektList();
	Log::debug("Ilosc elementow:");
	Log::debug(Ilosc(l.size()));
	for( auto a : l ){
		Log::debug<Obiekt>(*a);
	}
	Log::debug("Pobranie listy kluczy");
	r = lista.rawKluczList();
	Log::debug("Ilosc elementow:");
	Log::debug(Ilosc(r.size()));
	for( auto a : r ){
		Log::debug(a);
	}
	Log::debug("Przenoszenie jednej sztuki obiektu o kluczu");
	Log::debug(r.front());
	Log::debug("do drugiego kontenera.");
	ObiektList<Obiekt>::move(r.front(),Ilosc(1),lista,listaDruga);
	Log::debug("Zawartoœæ kontenera");
	Log::debug(lista);
	Log::debug("Zawartoœæ drugiego kontenera");
	Log::debug(listaDruga);
	Log::debug("Przenoszenie calego obiektu o kluczu");
	Log::debug(r.front());
	Log::debug("do drugiego kontenera.");
	ObiektList<Obiekt>::move(r.front(),lista,listaDruga);
	Log::debug("Zawartoœæ kontenera");
	Log::debug(lista);
	Log::debug("Zawartoœæ drugiego kontenera");
	Log::debug(listaDruga);
	Log::debug("Rozmiar drugiej listy:");
	Log::debug(Ilosc(listaDruga.size()));
	Log::debug("Czyszczenie kontenera");
	listaDruga.clear();
	Log::debug("Zawartoœæ drugiego kontenera po wyczyszceniu");
	Log::debug(listaDruga);
	Log::debug("Test Zakoñczony powodzeniem.");

	return error;

}
bool Testy::test_podstawoweDzialaniaKlas(){
	bool result = false;
	bool error = false;
	cout << boolalpha;
	cout << "\nTest klasy: Tekst\n";
	Tekst tekst;
	cout << "Pusta klasa: \"" << tekst.toString() << "\"\n";
	tekst.setTekst("Testowanie klasy Tekst");
	cout << "Napis zwarty w klasie: \""<< tekst.getTekst() << "\"\n";
	cout << "Zawartoœæ klasy po dodaniu napisu: \""<< tekst.toString() << "\"\n";
	Tekst tekst2(" Dodawany napis");
	cout << "Drugi obiekt klasy Tekst po utworzeniu: \""<<tekst2.toString()<<"\"\n";
	tekst+=tekst2;
	cout << "Po dodaniu dwóch obiektów: \""<<tekst.value()<<"\"\n";
	cout << "Porównywanie tekstów: Równe = "<< (tekst2==tekst) << ", Ró¿ne = "<<(tekst2!=tekst)<< endl;
	cout << "Zawartoœci obu napisów: \n1. \""<<tekst.toString()<<"\"\n2. \""<<tekst2.toString()<<"\"\n"; 
	cout << "Test Zakoñczony powodzeniem.\n";

	cout << "\nTest klasy: Klucz\n";
	Klucz key( IdType(14) , Poziom(1) );
	Klucz key2( IdType(13) , Poziom(1) );
	Klucz key3( key2 );
	cout << "Zawartosc klasy po utworzeniu \n(key):"<< key.toString() << "\n(key2):" << key2.toString() << "\n(key3):" << key3.toString()<<endl;
	cout << "Porownywanie kluczy: key == key2 "<< (key==key2) <<" , key2 == key3 " << (key2==key3) << " , key != key3 " << (key != key3) << endl;
	cout << "Test Zakoñczony powodzeniem.\n";

	cout << "\nTest klasy: Base\n";
	Base base1( IdType(30) );
	cout << "Zawartoœæ utworzonej klasy: " << base1.toString() << endl;
	cout << "Test Zakoñczony powodzeniem.\n";
	
	cout << "\nTest klasy: ObiektBase\n";
	Info iA( Tekst("A"), Tekst("A"), IdType(1),Wymagania() );
	Info iB( Tekst("B"), Tekst("B"), IdType(2),Wymagania() );
	ObiektBase objbase1( Ilosc(14), Poziom(20), iA );
	cout << "Zawartoœæ utworzonej klasy: " << objbase1.toString() << endl;
	ObiektBase objbase2( Ilosc(1), Poziom(20), iA );
	cout << "Zawartoœæ utworzonej klasy: " << objbase2.toString() << endl;
	ObiektBase objbase3( Ilosc(2), Poziom(10), iB );
	cout << "Zawartoœæ utworzonej klasy: " << objbase3.toString() << endl;
	cout << "Klucz dla pierwszego elementu: " << objbase1.ID().toString()<<endl;
	cout << "Próba dzielenia objbase1 wzg 5: "<< objbase1.czyMoznaPodzielic(Ilosc(5))<<endl;
	cout << "Proba po³¹czenia objbase2 i 3: " << objbase2.czyMoznaPolaczyc(objbase3) << endl; 
	cout << "Proba po³¹czenia objbase1 i 2: " << objbase2.czyMoznaPolaczyc(objbase1) << endl; 
	
	cout << "Test Zakoñczony powodzeniem.\n";

	return error;
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