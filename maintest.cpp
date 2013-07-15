#include "Main.h"
#include "Biblioteki.h"
#include "Aplikacja.h"
#include "FunkcjeTestowe.h"

#ifdef TESTS
#include "Testy.h"
#include "TestyJednostkowe.h"

void main(){
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
	Aplikacja::getInstance();
	TestyJednostkowe::pobierzInstancje().wykonajTesty();

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