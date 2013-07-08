#include "Main.h"
#include "Biblioteki.h"
#include "Aplikacja.h"
#include "FunkcjeTestowe.h"

#ifdef TESTS

#include "Testy.h"

void main(){
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );

	Testy test;
	test.dodajTest("£adowanie Danych",ladowanie_danych,true);
	test.dodajTest("Logowanie",test_Logowanie,true);
	test.dodajTest("Test klasy NiepoprawneParametryFunkcji",test_KlasaNiepoprawneParametryFunkcji,true);	
	test.dodajTest("Tworzenie Obiektow",test_tworzenieObiektow,true);
	test.dodajTest("Test Klasy Ladownia",test_KlasaLadownia,false);
	test.dodajTest("Operacje na klasie ObiektList",test_KlasaObiektList,false);
	test.dodajTest("Test Wymagan",test_wymagan,false);
	test.dodajTest("Test Jednostki Atakuj¹cej",test_KlasaJednostkaAtakujaca,false);
	test.dodajTest("Test dla zgloszenia 42",test_Issue42,false); 
	test.dodajTest("Test tworzenia technologi",test_Technologie,false); 
	test.dodajTest("Test dla zgloszenia 52",test_Issue52,false);
	test.dodajTest("Test budynków",test_Budynki,false);
	test.dodajTest("Test tworzenia planety i obiektow na planecie",test_TworzeniePlanetyIObiektow,true);
	test.dodajTest("Test dla zgloszenia 41 i 57",test_Issue41i57,false);
	test.dodajTest("Test dla zgloszenia 39",test_Issue39,false);
	test.dodajTest("Test klasy flota",test_KlasyFlota,false);
	test.dodajTest("Zapis Stanu Gry",test_ZapisStanuGry,false);
	test();
	/*ALLEGRO_DISPLAY *display = NULL;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return;
   }
 
   display = al_create_display(640, 480);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return;
   }
 
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_rest(10.0);
 
   al_destroy_display(display);
   */
	/*Testy *test = NULL;
	try{
		test = new Testy();
		test->test_ladowaniePlikuXML();
	}catch(OgolnyWyjatek& ex){
		cout<<"Niepowodzenie Testu!\n"<<ex.generujKomunikat();
		if(test!=NULL)
			delete test;
		return;
 	}catch(exception& ex){
		cout<<"Niepowodzenie Testu!\n"<<ex.what();
		if(test!=NULL)
			delete test;
		return;
	}

	try{
		test->test_podzialuStatku();
	}catch(exception& ex){
		cout<<"Niepowodzenie Testu!\n"<<ex.what();
		if(test!=NULL)
			delete test;
		return;
	}
	if(test!=NULL)
		delete test;*/
}

#endif