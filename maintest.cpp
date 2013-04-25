#include "Main.h"
#include "Biblioteki.h"
#include "Aplikacja.h"

#ifdef TESTS

#include "Testy.h"
#include <chrono>
#include <iomanip>
#include <fstream>

void main(){
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );

	/* Ustawianie polskich znak�w */
	locale pl ("Polish");
	locale::global (pl);
	/* ------------------------------------ */
	
	/* ------- Konfiguracja Loggera -------*/
	struct tm timeinfo;
	time_t t = time(nullptr);
	localtime_s(&timeinfo, &t);
	char s[20];
	strftime(s,20,"%Y-%m-%d",&timeinfo);
	stringstream sfile;
	sfile << "space-explorers-" << s << ".log"; 
	string filename = sfile.str();
	Log::getInstance().ustawFormatCzasu(Log::Czas);
	Log::getInstance().dodajGniazdoWyjsciowe(shared_ptr<ostream>(new fstream (filename,ios_base::app)));
	/* ------------------------------------ */

	/* Wylaczenie logow typu debug na potrzeby ograniczenia logow testow*/
	Log::getInstance().logDebugDisable();
	/* ------------------------------------ */

	Testy test;
	test.run();
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