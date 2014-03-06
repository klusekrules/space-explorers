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
		
	SpEx::Aplikacja::iloscArgumentow = argv;
	SpEx::Aplikacja::argumenty = argc;
	SpEx::Aplikacja::pobierzInstancje();

	MaszynaStanow::pobierzInstancje().start();
	//TestyJednostkowe::pobierzInstancje().wykonajTesty();
}

#endif