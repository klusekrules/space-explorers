#include "Aplikacja.h"
#include <time.h>
#include <sstream>
#include <iomanip>

Aplikacja::Aplikacja()
	: isDbgHelpInit(false), pustyObiekt(Ilosc(0), Poziom(0), Info(Tekst(""),Tekst(""),IdType(0)))
{
	hLibrary = LoadLibrary("Dbghelp.dll");
	if(hLibrary!=NULL){		
		symInitialize = (SymInitializeS)GetProcAddress(hLibrary,"SymInitialize");
		symFromAddr = (SymFromAddrS)GetProcAddress(hLibrary,"SymFromAddr");
		if(symFromAddr!=NULL && symInitialize!= NULL )
			isDbgHelpInit = true;
		//_set_purecall_handler(myPurecallHandler);
	}
}

string Aplikacja::getStackTrace() const{
	stringstream stackTrace;	
	if( isDbgHelpInit )
	{
		void *stack[150];
		unsigned short frames;
		SYMBOL_INFO *symbol;
		HANDLE hProcess;
		locale l("C");
		stackTrace.imbue(l);
		hProcess = GetCurrentProcess ();
		symInitialize (hProcess, NULL, TRUE);
		frames = CaptureStackBackTrace( 0, 150, stack, NULL );
		symbol = (SYMBOL_INFO *) calloc (sizeof (SYMBOL_INFO) + 256 * sizeof (char), 1);
		symbol->MaxNameLen = 255;
		symbol->SizeOfStruct = sizeof (SYMBOL_INFO);
		if(frames>0){

			time_t rawtime;
			char buf [30];
			time(&rawtime);
			ctime_s(buf,30,&rawtime);
			stackTrace << buf;
			// i = 1 - Pominiêcie wywo³ania funkcji getStackTrace
			// i = 0 - W³¹cznie do wyœwietlanego wyniku wywo³ania funkcji getStackTrace
			for (unsigned int i = 1 ;i < frames; i++)
			{
				symFromAddr (hProcess, (DWORD_PTR) (stack[i]), 0, symbol);
				stackTrace << dec << (unsigned short)(frames - i - 1) << ": 0x" << setfill('0')<<setw(8)<<stack[i] << " " << (char*)(symbol->Name) << " = 0x" << setfill('0')<<setw(8) << hex <<symbol->Address << endl;
				//fprintf_s (fp,"%u: %p %s = 0x%Ix\n", frames - i - 1, stack[i], symbol->Name, symbol->Address);
			}
		}
		free (symbol);
	}
	return stackTrace.str();
}

Aplikacja::~Aplikacja()
{
	if(hLibrary!=NULL)
		FreeLibrary(hLibrary);
}
