#include "Main.h"
#include "Biblioteki.h"
#include "Aplikacja.h"
#include <SFML/Graphics.hpp>
#include "MaszynaStanow.h"
#include "lua.hpp"

#ifdef TESTS
#include "TestyJednostkowe.h"

void main( int argv , char* argc[] ){

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
	try{
		SpEx::Aplikacja::iloscArgumentow = argv;
		SpEx::Aplikacja::argumenty = argc;
		SpEx::Aplikacja::pobierzInstancje();

		SpEx::MaszynaStanow::pobierzInstancje().start();
		//TestyJednostkowe::pobierzInstancje().wykonajTesty();
	}
	catch (STyp::Wyjatek& wyjatek){
		MessageBox(
			nullptr,
			wyjatek.getTresc()().c_str(),
			wyjatek.getTytul()().c_str(),
			MB_ICONERROR
			);
	}
	catch (std::exception& exception){
		MessageBox(
			nullptr,
			exception.what(),
			"Fatal error",
			MB_ICONERROR
			);
	}
	catch (...){
		MessageBox(
			nullptr,
			"Unknown Exception!",
			"Fatal error",
			MB_ICONERROR
			);
	}
}

#endif