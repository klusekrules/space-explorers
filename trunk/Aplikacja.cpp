#include "Aplikacja.h"
#include <time.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "XmlBO.h"
#include <io.h>
#include "ZmianaPoziomObiektu.h"
#include "DefinicjeWezlowXML.h"
#include "Walidator.h"

int Aplikacja::iloscArgumentow = 0;
char** Aplikacja::argumenty = nullptr;

Aplikacja& Aplikacja::pobierzInstancje(){
	static Aplikacja instancja;
	return instancja;
}

void myPurecallHandler(){
	Log::pobierzInstancje().loguj(Log::Error,Aplikacja::pobierzInstancje().pobierzSladStosu());
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
	Log::pobierzInstancje().loguj(Log::Error,str.str());
	Log::pobierzInstancje().loguj(Log::Error,Aplikacja::pobierzInstancje().pobierzSladStosu());
}

Aplikacja::Aplikacja() throw(NiezainicjalizowanaKlasa)
	: czyZainicjalizowanaBiblioteka_(false), logger_(Log::pobierzInstancje()), instancjaGry_(new Gra(*this))
{

#ifdef TESTS
	/* Wylaczenie logow typu debug na potrzeby ograniczenia logow testow*/
	logger_.zablokujLogi(Log::Debug);
	/* ------------------------------------ */
#endif

	//Ladowanie potrzebnych bibliotek
	uchwyt_ = LoadLibrary("Dbghelp.dll");
	if(uchwyt_){		
		symInitialize_ = (SymInitializeS)GetProcAddress(uchwyt_,"SymInitialize");
		symFromAddr_ = (SymFromAddrS)GetProcAddress(uchwyt_,"SymFromAddr");
		if(symFromAddr_ && symInitialize_){
			czyZainicjalizowanaBiblioteka_ = true;
		}
	}

	/* ------- Konfiguracja parametrów programu -------*/
	if(!przetworzArgumenty()){
		throw OgolnyWyjatek(EXCEPTION_PLACE);
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
	logger_.ustawFormatCzasu(Log::Czas);
	logger_.dodajGniazdoWyjsciowe( [](Log::TypLogow typ, const std::string& komunikat)->void{ cout << komunikat; } );
	logger_.dodajGniazdoWyjsciowe( [&filename](Log::TypLogow typ, const std::string& komunikat)->void{ static fstream plik(filename,ios_base::app); plik << komunikat; } );
	/* ------------------------------------ */

	if(!zaladujOpcje()){
		throw OgolnyWyjatek(EXCEPTION_PLACE);
	}

	//Wyswietlanie informacji o aplikacji
	logApInfo();

	//Wyswietlanie informacji o zaladowanej bibliotece
	if(uchwyt_){
		if(czyZainicjalizowanaBiblioteka_){
			logger_.loguj(Log::Info, "Za³adowano biblioteke Dbghelp.dll");
		}else{
			logger_.loguj(Log::Warning, "Nie zanaleziono funkcji SymInitialize i/lub SymFromAddr.");
		}
	}else{
		logger_.loguj(Log::Warning,"Nie za³adowano biblioteki Dbghelp.dll");
	}

	pluginy_ = shared_ptr<Cplugin>(new Cplugin(folderPluginow_,instancjaGry_->pobierzFabrykeZmian(),logger_));

	RejestrujZmianaPoziomObiektu(instancjaGry_->pobierzFabrykeZmian(),logger_);

	if(!pluginy_->zaladujDomyslneKlasyZmian())
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,Tekst("Domyslne elementy zmiany."));

	if(!pluginy_->zaladujZewnetrzneKlasyZmian())
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,Tekst("Dodatkowe elementy zmiany."));


	_set_purecall_handler(myPurecallHandler);
	_set_invalid_parameter_handler(myInvalidParameterHandler);

}

Aplikacja::Aplikacja( const Aplikacja& aplikacja )
	:logger_(Log::pobierzInstancje())
{
}

Aplikacja& Aplikacja::operator=(const Aplikacja& aplikacja ){
	return *this;
}

Log& Aplikacja::pobierzLogger() const{
	return logger_;
}

Gra& Aplikacja::pobierzGre() const{
	return *instancjaGry_;
}

bool Aplikacja::wczytajDane(){
	return instancjaGry_->wczytajDane(nazwaPlikuDanych_);
}

void Aplikacja::wyczyscDane(){
	instancjaGry_ = std::shared_ptr<Gra>(new Gra (*this));
}

bool Aplikacja::zaladujOpcje(){
	TiXmlDocument dane;
	try{
		dane.LoadFile(nazwaPlikuOpcji_);
		auto root_data = dane.FirstChildElement("SpaceGame");
		if(root_data){

			auto jezyk = XmlBO::ZnajdzWezel<NOTHROW>(root_data,"locale");
			if(jezyk){
				jezykAplikacji_ = jezyk->GetText();
				if(jezykAplikacji_.size() != 0){
					try{
						locale pl (jezykAplikacji_);
						locale::global (pl);
						this->logger_.loguj(Log::Debug, string("Separator u³amka: ") + std::use_facet<std::numpunct<char>>(pl).decimal_point());
					}catch(exception&){
						jezykAplikacji_.clear();
					}
				}
			}

			if(jezykAplikacji_.size() == 0){
				jezykAplikacji_ = "Polish";
				locale pl (jezykAplikacji_);
				locale::global (pl);
			}

			auto plikDanych = XmlBO::ZnajdzWezel<THROW>(root_data,"data");
			if(plikDanych){
				nazwaPlikuDanych_ = plikDanych->GetText();
				if( _access(nazwaPlikuDanych_.c_str(),0) == -1 ){ // Sprawdzenie czy folder istnieje
					throw OgolnyWyjatek(EXCEPTION_PLACE,OgolnyWyjatek::domyslnyOgolnyWyjatekID,Tekst("Brak pliku danych."),Tekst("Plik z danymi programu nie zosta³ znaleziony!"));
				}
			}else{
				throw WyjatekParseraXML(EXCEPTION_PLACE,exception(""),WyjatekParseraXML::trescBladStrukturyXml);
			}

			auto pluginy = XmlBO::ZnajdzWezel<NOTHROW>(root_data,"plugins");
			if(pluginy){
				folderPluginow_ = pluginy->GetText();
				if( _access(folderPluginow_.c_str(),0) == -1 ){ // Sprawdzenie czy folder istnieje
					folderPluginow_.clear();
				}
			}

			if(folderPluginow_.size() == 0){
				folderPluginow_ = "plugins\\";
			}

		}else{
			throw WyjatekParseraXML(EXCEPTION_PLACE,exception(""),WyjatekParseraXML::trescBladStrukturyXml);
		}
	}catch(ticpp::Exception& e){
		logger_.loguj(Log::Error,e.what());
		return false;
	}
	return true;
}

string Aplikacja::pobierzSladStosu() const{
	stringstream stackTrace;	
	if( czyZainicjalizowanaBiblioteka_ )
	{
		void *stack[150];
		unsigned short frames;
		SYMBOL_INFO *symbol;
		HANDLE hProcess;
		locale l("C");
		stackTrace.imbue(l);
		hProcess = GetCurrentProcess ();
		symInitialize_ (hProcess, nullptr, true );
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
				symFromAddr_ (hProcess, (DWORD_PTR) (stack[i]), 0, symbol);
				stackTrace << dec << (unsigned short)(frames - i - 1) << ": 0x" << setfill('0')<<setw(8)<<stack[i] << " " << (char*)(symbol->Name) << " = 0x" << setfill('0')<<setw(8) << hex <<symbol->Address << endl;
			}
		}
		free (symbol);
	}
	return stackTrace.str();
}

Aplikacja::~Aplikacja()
{
	if(uchwyt_)
		FreeLibrary(uchwyt_);
}

bool Aplikacja::zapiszGre(const string& nazwa, const string& hash) const{
	TiXmlDocument dokument;
	TiXmlElement* wezel = new TiXmlElement(WEZEL_XML_ROOT);
	dokument.LinkEndChild(wezel);
	locale::global (locale("C"));
	if(instancjaGry_->zapisz(wezel) && instancjaGry_->zapisz(nazwa,hash)){
		locale::global (locale(jezykAplikacji_));
		return dokument.SaveFile("save\\gra.xml");
	}
	locale::global (locale(jezykAplikacji_));
	return false;
}

bool Aplikacja::wczytajGre(const string& nazwa, const string& hash){
	TiXmlDocument dokument;
	if(!dokument.LoadFile("save\\gra.xml")){
		TiXmlElement* wezel = new TiXmlElement(WEZEL_XML_ROOT);
		dokument.LinkEndChild(wezel);
		TiXmlElement* gra = new TiXmlElement(WEZEL_XML_GRA);
		wezel->LinkEndChild(gra);
		dokument.SaveFile("save\\gra.xml");
	}
	TiXmlElement* wezel = dokument.RootElement();
	if(wezel){
		shared_ptr<Gra> gra = instancjaGry_;
		try{
			instancjaGry_ = shared_ptr<Gra>(new Gra(*this));
			Walidator::pobierzInstancje().wyczysc();
			Walidator::pobierzInstancje().dodajNowyIdentyfikatorPlanety(Identyfikator(0x0)); // Poprawna wartoœæ; U¿ywana gdy obiekty znajduj¹ siê we flocie.
			if(instancjaGry_->wczytajDane(this->nazwaPlikuDanych_) ){
				if(instancjaGry_->odczytaj(wezel->FirstChildElement(WEZEL_XML_GRA)))
					if(instancjaGry_->odczytaj(nazwa,hash))
						if(Walidator::pobierzInstancje().waliduj())
							return true;
			}
			instancjaGry_ = gra;
			return false;
		}catch( OgolnyWyjatek& e ){
			logger_.loguj(Log::Error,e);
		}catch( exception& e ){
			logger_.loguj(Log::Error,e.what());
		}catch(...){
		}
		instancjaGry_ = gra;
	}
	return false;
}

bool Aplikacja::przetworzArgumenty(){
	if(!argumenty || iloscArgumentow <= 0 )
		return false;
	nazwaPlikuOpcji_ = "options.xml";
	for( int numer = 0 ; numer < iloscArgumentow ; ++numer  ){
		if(!argumenty[numer])
			continue;
		string argument(argumenty[numer]);
		if(argument.empty())
			continue;
		if(!argument.compare("-O")){
			++numer;
			if(numer >= iloscArgumentow || !argumenty[numer])
				return false;
			string nazwa(argumenty[numer]);
			if(nazwa.empty())
				return false;
			nazwaPlikuOpcji_ = nazwa;
		}
	}
	return true;
}
