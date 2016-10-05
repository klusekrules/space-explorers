#include "Kontroler\Aplikacja.h"
#include "TypyProste\Wyjatek.h"
#include <fstream>

#ifdef TESTS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Testy\Szkielet\TestyJednostkowe.h"
#include "Eksport\Export.h"

void main( int argv , char* argc[] ){
	HANDLE hLogFile = CreateFile("mem_leak.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, hLogFile);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, hLogFile);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, hLogFile);

	try{
		SpEx::Aplikacja::iloscArgumentow = argv;
		SpEx::Aplikacja::argumenty = argc;

		if (SpEx::Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji()["Testowanie"].length()) {
			testyJednostkowe();
			zamknijAplikacje();
		}else
			SpEx::Aplikacja::pobierzInstancje().start();
		
		if (SpEx::Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji()["Zrzut"].length()) {
			std::fstream plik("zrzut.txt", std::ios_base::app);
			plik << SpEx::Aplikacja::pobierzInstancje().pobierzDebugInfo();
		}
	}
	catch (STyp::Wyjatek& wyjatek){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, wyjatek);
		MessageBox(
			nullptr,
			wyjatek.getTresc()().c_str(),
			wyjatek.getTytul()().c_str(),
			MB_ICONERROR
			);
	}
	catch (std::exception& exception){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, exception.what());
		MessageBox(
			nullptr,
			exception.what(),
			"Fatal error",
			MB_ICONERROR
			);
	}
	catch (...){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Unknown Exception!");
		MessageBox(
			nullptr,
			"Unknown Exception!",
			"Fatal error",
			MB_ICONERROR
			);
	}
	
}

#endif