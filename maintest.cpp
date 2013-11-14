#include "Main.h"
#include "Biblioteki.h"
#include "Aplikacja.h"
#include <SFML/Graphics.hpp>
#include "MaszynaStanow.h"

#ifdef TESTS
#include "TestyJednostkowe.h"
#include <atomic>

std::atomic<bool> atom = true;

void run(){
	while(atom){
		std::this_thread::yield();
	}
	ExitThread(0);
}

void main( int argv , char* argc[] ){

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
	
	std::thread t(run);
	std::thread d(run);
	atom = false;
	t.join();
	d.join();

	Aplikacja::iloscArgumentow = argv;
	Aplikacja::argumenty = argc;
	Aplikacja::pobierzInstancje();

	MaszynaStanow::pobierzInstancje().start();

}

#endif