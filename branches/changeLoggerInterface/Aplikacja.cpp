#include "Aplikacja.h"
#include <time.h>
#include <sstream>
#include <iomanip>
#include "StatekInfo.h"

#include "ZmianaDekorator.h"
#include "ZmianaAgregacja.h"
#include "ZmianaLiniowa.h"
#include "ZmianaPotegowa.h"

Aplikacja::Aplikacja()
	: isDbgHelpInit(false), pustyobiekBaseInfo( Info(Tekst(""),Tekst(""),IdType(0),Wymagania(nullptr)) , Poziom(0) ), pustyObiektBase( Ilosc(0), pustyobiekBaseInfo )
{
	hLibrary = LoadLibrary("Dbghelp.dll");
	if(hLibrary){		
		symInitialize = (SymInitializeS)GetProcAddress(hLibrary,"SymInitialize");
		symFromAddr = (SymFromAddrS)GetProcAddress(hLibrary,"SymFromAddr");
		if(symFromAddr && symInitialize)
			isDbgHelpInit = true;
		//_set_purecall_handler(myPurecallHandler);
	}

	// Rejestracja zmian w fabryce 
	ZmianaLiniowa::RejestrujZmianaLiniowa();
	ZmianaDekorator::RejestrujZmianaDekotor();
	ZmianaAgregacja::RejestrujZmianaAgregacja();	
	ZmianaPotegowa::RejestrujZmianaPotegowa();
	// -----------------------------------------

}

bool Aplikacja::WczytajDane( const string& sFile ){
	ticpp::Document opcje;
	ticpp::Document dane;
	//ticpp::Document komunikaty;
	try{
		/* TODO: £adowanie opcji przenieœæ do innej funkcji
 
		opcje.LoadFile(sFile);
		auto root = opcje.IterateChildren("SpaceGame",nullptr);
		auto b = root->IterateChildren("data",nullptr);
		if(b!=nullptr){
			string s = b->ToElement()->GetText();
			*/
		dane.LoadFile(sFile);
		auto root_data = dane.IterateChildren("SpaceGame",nullptr);
		if(root_data){
			if(!WczytajSurowce(root_data))
				return false;
			if(!WczytajStatki(root_data))
				return false;
		}
	}catch(ticpp::Exception& e){
		cout<< e.what();
		Log::error("Nie uda³o siê otworzyæ pliku!");
		return false;
	}
	return true;
}

bool Aplikacja::WczytajSurowce(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		try{
			ptr = root->IterateChildren(SurowceInfo::LogSurowceInfo::className(),ptr);
			if(ptr){
				SurowceInfo* t = new SurowceInfo(ptr);
				Log::info<SurowceInfo>(*t);
				listaSurowcowInfo[t->ID()]=t;
			}
		}catch(OgolnyWyjatek& e){
			Log::warn(e.generujKomunikat());
			Log::debug(e);
			return false;
		}
	}while(ptr);
	return true;
}

bool Aplikacja::WczytajStatki(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		try{
			ptr = root->IterateChildren(StatekInfo::LogStatekInfo::className(),ptr);
			if(ptr){
				StatekInfo* t = new StatekInfo(ptr);
				Log::info<StatekInfo>(*t);
				listaStatkowInfo[t->ID()]=t;
			}
		}catch(OgolnyWyjatek& e){
			Log::warn(e.generujKomunikat());
			Log::debug(e);
			return false;
		}
	}while(ptr);
	return true;
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
		symInitialize (hProcess, nullptr, true );
		frames = CaptureStackBackTrace( 0, 150, stack, nullptr );
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
	for(auto s : listaStatkowInfo)
		if(s.second)
			delete s.second;
	if(hLibrary)
		FreeLibrary(hLibrary);
}
