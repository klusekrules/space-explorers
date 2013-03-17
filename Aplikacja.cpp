#include "Aplikacja.h"
#include <time.h>
#include <sstream>
#include <iomanip>
#include "StatekInfo.h"
Aplikacja::Aplikacja()
	: isDbgHelpInit(false), pustyobiekBaseInfo( Info(Tekst(""),Tekst(""),IdType(0),Wymagania()) , Poziom(0) ), pustyObiektBase( Ilosc(0), pustyobiekBaseInfo )
{
	hLibrary = LoadLibrary("Dbghelp.dll");
	if(hLibrary!=nullptr){		
		symInitialize = (SymInitializeS)GetProcAddress(hLibrary,"SymInitialize");
		symFromAddr = (SymFromAddrS)GetProcAddress(hLibrary,"SymFromAddr");
		if(symFromAddr!=nullptr && symInitialize!= nullptr )
			isDbgHelpInit = true;
		//_set_purecall_handler(myPurecallHandler);
	}
}

bool Aplikacja::WczytajDane(){
	ticpp::Document opcje;
	ticpp::Document dane;
	ticpp::Document komunikaty;
	try{
		opcje.LoadFile("options.xml");
		auto root = opcje.IterateChildren("SpaceGame",nullptr);
		auto b = root->IterateChildren("data",nullptr);
		if(b!=nullptr){
			string s = b->ToElement()->GetText();
			cout << s << endl;
			dane.LoadFile(s);
			auto root2 = dane.IterateChildren("SpaceGame",nullptr);
			WczytajSurowce(root2);
			auto c = root2->IterateChildren("StatekInfo",nullptr);
			if(c!=nullptr)
			{
				StatekInfo* ptr = new StatekInfo(c);
				cout << ptr->toString()<<endl;
				delete ptr;
			}

		}
	}catch(ticpp::Exception& e){
		cout<< e.what();
		Log::error("Nie uda³o siê otworzyæ pliku!");
	}
	return true;
}

bool Aplikacja::WczytajSurowce(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		ptr = root->IterateChildren("SurowceInfo",ptr);
		if(ptr){
			SurowceInfo* t = new SurowceInfo(ptr);
			cout<<t->toString()<<endl;
			listaSurowcowInfo[t->ID()]=t;
		}
	}while(ptr);
	return false;
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
	for(auto s : listaSurowcowInfo)
		if(s.second)
			delete s.second;
	if(hLibrary!=NULL)
		FreeLibrary(hLibrary);
}
