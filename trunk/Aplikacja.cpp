#include "Aplikacja.h"
#include <time.h>
#include <sstream>
#include <iomanip>
#include "StatekInfo.h"
#include <fstream>
#include "XmlBO.h"
#include <io.h>
#include "ZmianaPoziomObiektu.h"

void myPurecallHandler(){
	Log::getInstance().error(Aplikacja::getInstance().getStackTrace());
}
void myInvalidParameterHandler(const wchar_t* expression,
   const wchar_t* function, 
   const wchar_t* file, 
   unsigned int line, 
   uintptr_t pReserved)
{
	char* c_expression = new char[wcslen(expression)+1];
	char* c_function = new char[wcslen(function)+1];
	char* c_file = new char[wcslen(file)+1];
	wcstombs_s(nullptr,c_expression,wcslen(expression)+1,expression,wcslen(expression));	
	wcstombs_s(nullptr,c_function,wcslen(function)+1,function,wcslen(function));
	wcstombs_s(nullptr,c_file,wcslen(file)+1,file,wcslen(file));
	stringstream str;
	str<<"Invalid parameter detected in function: "<<c_function<<". File: " << c_file <<". Line: "<<line<<".\nExpression: "<< c_expression;
	Log::getInstance().error(str.str());
	Log::getInstance().error(Aplikacja::getInstance().getStackTrace());
}

Aplikacja::Aplikacja() throw(NiezainicjalizowanaKlasa)
	: isDbgHelpInit(false), log(Log::getInstance()), instancjaGry(new Gra(*this))
{

#ifdef TESTS
	/* Wylaczenie logow typu debug na potrzeby ograniczenia logow testow*/
	log.logDebugDisable();
	/* ------------------------------------ */
#endif

	//Ladowanie potrzebnych bibliotek
	hLibrary = LoadLibrary("Dbghelp.dll");
	if(hLibrary){		
		symInitialize = (SymInitializeS)GetProcAddress(hLibrary,"SymInitialize");
		symFromAddr = (SymFromAddrS)GetProcAddress(hLibrary,"SymFromAddr");
		if(symFromAddr && symInitialize){
			isDbgHelpInit = true;
		}
	}

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

	if(!ZaladujOpcje()){
		throw OgolnyWyjatek(EXCEPTION_PLACE);
	}
	
	//Wyswietlanie informacji o aplikacji
	LogApInfo();

	//Wyswietlanie informacji o zaladowanej bibliotece
	if(hLibrary){
		if(isDbgHelpInit){
			log.info("Za³adowano biblioteke Dbghelp.dll");
		}else{
			log.warn("Nie zanaleziono funkcji SymInitialize i/lub SymFromAddr.");
		}
	}else{
		log.warn("Nie za³adowano biblioteki Dbghelp.dll");
	}

	pluginy = shared_ptr<Cplugin>(new Cplugin(folderPluginow,instancjaGry->getZmianaFabryka(),log));

	RejestrujZmianaPoziomObiektu(instancjaGry->getZmianaFabryka(),log);

	if(!pluginy->LoadDefaultZmiana())
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,Tekst("Domyslne elementy zmiany."));

	if(!pluginy->LoadPluginsZmiana())
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,Tekst("Dodatkowe elementy zmiany."));

	
	_set_purecall_handler(myPurecallHandler);
	_set_invalid_parameter_handler(myInvalidParameterHandler);

}

Aplikacja::Aplikacja( const Aplikacja& a)
	:isDbgHelpInit(a.isDbgHelpInit), log(Log::getInstance()), instancjaGry(a.instancjaGry) ,hLibrary(a.hLibrary)
{
}

Aplikacja& Aplikacja::operator=(const Aplikacja& a){
	isDbgHelpInit = a.isDbgHelpInit;
	instancjaGry = a.instancjaGry;
	hLibrary=a.hLibrary;
	symInitialize = a.symInitialize;
	symFromAddr = a.symFromAddr;
	pluginy = a.pluginy;
	return *this;
}

Log& Aplikacja::getLog(){
	return log;
}

Gra& Aplikacja::getGra(){
	return *instancjaGry;
}

bool Aplikacja::WczytajDane(){
	return instancjaGry->WczytajDane(nazwaPlikuDanych);
}

bool Aplikacja::ZaladujOpcje(){
	ticpp::Document dane;
	try{
#ifdef TESTS
		dane.LoadFile("options_test.xml");
#else
		dane.LoadFile("options.xml");
#endif
		auto root_data = dane.IterateChildren("SpaceGame",nullptr);
		if(root_data){

			auto jezyk = XmlBO::IterateChildrenElement<NOTHROW>(root_data,"locale");
			if(jezyk){
				jezykAplikacji = jezyk->GetText(false);
				if(jezykAplikacji.size() != 0){
					try{
						locale pl (jezykAplikacji);
						locale::global (pl);
					}catch(exception&){
						jezykAplikacji.clear();
					}
				}
			}

			if(jezykAplikacji.size() == 0){
				jezykAplikacji = "Polish";
				locale pl (jezykAplikacji);
				locale::global (pl);
			}

			auto plikDanych = XmlBO::IterateChildrenElement<THROW>(root_data,"data");
			if(plikDanych){
				nazwaPlikuDanych = plikDanych->GetText();
				if( _access(nazwaPlikuDanych.c_str(),0) == -1 ){ // Sprawdzenie czy folder istnieje
					throw OgolnyWyjatek(EXCEPTION_PLACE,OgolnyWyjatek::domyslnyOgolnyWyjatekID,Tekst("Brak pliku danych."),Tekst("Plik z danymi programu nie zosta³ znaleziony!"));
				}
			}else{
				throw WyjatekParseraXML(EXCEPTION_PLACE,exception(""),WyjatekParseraXML::trescBladStrukturyXml);
			}
			
			auto pluginy = XmlBO::IterateChildrenElement<NOTHROW>(root_data,"plugins");
			if(pluginy){
				folderPluginow = pluginy->GetText(false);
				if( _access(folderPluginow.c_str(),0) == -1 ){ // Sprawdzenie czy folder istnieje
					folderPluginow.clear();
				}
			}
			
			if(folderPluginow.size() == 0){
				folderPluginow = "plugins\\";
			}

		}else{
			throw WyjatekParseraXML(EXCEPTION_PLACE,exception(""),WyjatekParseraXML::trescBladStrukturyXml);
		}
	}catch(ticpp::Exception& e){
		log.error(e.what());
		return false;
	}
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
			}
		}
		free (symbol);
	}
	return stackTrace.str();
}

Aplikacja::~Aplikacja()
{
	if(hLibrary)
		FreeLibrary(hLibrary);
}

bool Aplikacja::ZapiszGre() const{
	TiXmlDocument dokument;
	TiXmlElement* root = new TiXmlElement("Space-Explorers");
	dokument.LinkEndChild(root);
	if(instancjaGry->zapisz(root))
		return dokument.SaveFile("save.xml");
	return false;
}

bool Aplikacja::WczytajGre(){
	TiXmlDocument dokument;
	dokument.LoadFile("save.xml");
	TiXmlElement* root = dokument.RootElement();
	if(root){
		shared_ptr<Gra> tmp = shared_ptr<Gra>(new Gra(*this));
		if(tmp->WczytajDane(this->nazwaPlikuDanych) && tmp->odczytaj(root->FirstChildElement(CLASSNAME(Gra)))){
			instancjaGry = tmp;
			return true;
		}
		return false;
	}
	return false;
}
