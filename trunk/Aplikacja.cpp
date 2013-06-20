#include "Aplikacja.h"
#include <time.h>
#include <sstream>
#include <iomanip>
#include "StatekInfo.h"
#include <fstream>

Aplikacja::Aplikacja() throw(NiezainicjalizowanaKlasa)
	: isDbgHelpInit(false), log(Log::getInstance()), fabryka(ZmianaFabryka::pobierzInstancje()), pluginy(fabryka,log), pustyobiekBaseInfo( Info(Tekst(""),Tekst(""),IdType(0),Wymagania(nullptr)) , Poziom(0) ), pustyObiektBase( Ilosc(0), pustyobiekBaseInfo )
{
	/* Ustawianie polskich znaków */
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
	log.ustawFormatCzasu(Log::Czas);
	log.dodajGniazdoWyjsciowe(shared_ptr<ostream>(new fstream (filename,ios_base::app)));
	/* ------------------------------------ */

	/* Wylaczenie logow typu debug na potrzeby ograniczenia logow testow*/
	log.logDebugDisable();
	/* ------------------------------------ */

	//Wyswietlanie informacji o aplikacji
	LogApInfo();
	
	//Ladowanie potrzebnych bibliotek
	hLibrary = LoadLibrary("Dbghelp.dll");
	if(hLibrary){
		log.info("Za³adowano biblioteke Dbghelp.dll");
		symInitialize = (SymInitializeS)GetProcAddress(hLibrary,"SymInitialize");
		symFromAddr = (SymFromAddrS)GetProcAddress(hLibrary,"SymFromAddr");
		if(symFromAddr && symInitialize){
			isDbgHelpInit = true;
		}else{
			log.warn("Nie zanaleziono funkcji SymInitialize i/lub SymFromAddr.");
		}
	}else{
		log.warn("Nie za³adowano biblioteki Dbghelp.dll");
	}

	if(!pluginy.LoadDefaultZmiana())
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,Tekst("Domyslne elementy zmiany."));

	if(!pluginy.LoadPluginsZmiana())
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,Tekst("Dodatkowe elementy zmiany."));

	
	//_set_purecall_handler(myPurecallHandler);
	//TODO: zaimplementowanie logoowania podczas ka¿dej sytuacji wyj¹tkowej takiej jak wy¿ej

}

ZmianaFabryka& Aplikacja::getZmianaFabryka(){
	return fabryka;
}
Log& Aplikacja::getLog(){
	return log;
}

bool Aplikacja::WczytajDane( const string& sFile ){
	ticpp::Document dane;
	try{
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
		log.error("Nie uda³o siê otworzyæ pliku!");
		return false;
	}
	return true;
}

bool Aplikacja::ZaladujOpcje(){
	ticpp::Document dane;
	try{
		dane.LoadFile("options.xml");
		auto root_data = dane.IterateChildren("SpaceGame",nullptr);
		
	}catch(ticpp::Exception& e){
		cout<< e.what();
		log.error("Nie uda³o siê otworzyæ pliku!");
		return false;
	}
	return true;
}

bool Aplikacja::WczytajSurowce(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		try{
			ptr = root->IterateChildren(CLASSNAME(SurowceInfo),ptr);
			if(ptr){
				SurowceInfo* t = new SurowceInfo(ptr);
				log.debug(*t);
				listaSurowcowInfo[t->ID()]=t;
			}
		}catch(OgolnyWyjatek& e){
			log.warn(e.generujKomunikat());
			log.debug(e);
			return false;
		}
	}while(ptr);
	return true;
}

bool Aplikacja::WczytajStatki(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		try{
			ptr = root->IterateChildren(CLASSNAME(StatekInfo),ptr);
			if(ptr){
				StatekInfo* t = new StatekInfo(ptr);
				log.debug(*t);
				listaStatkowInfo[t->ID()]=t;
			}
		}catch(OgolnyWyjatek& e){
			log.warn(e.generujKomunikat());
			log.debug(e);
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
