#pragma once
#include "Main.h"
#include <Windows.h>
#include "Biblioteki.h"
#include "plugin\plugin.h"
#include "NiezainicjalizowanaKlasa.h"
#include "Gra.h"


typedef struct _SYMBOL_INFO {
	ULONG       SizeOfStruct;
	ULONG       TypeIndex;        // Type Index of symbol
	ULONG64     Reserved[2];
	ULONG       Index;
	ULONG       Size;
	ULONG64     ModBase;          // Base Address of module comtaining this symbol
	ULONG       Flags;
	ULONG64     Value;            // Value of symbol, ValuePresent should be 1
	ULONG64     Address;          // Address of symbol including base address of module
	ULONG       Register;         // register holding value or pointer to value
	ULONG       Scope;            // scope of the symbol
	ULONG       Tag;              // pdb classification
	ULONG       NameLen;          // Actual length of name
	ULONG       MaxNameLen;
	CHAR        Name[1];          // Name of symbol
} SYMBOL_INFO, *PSYMBOL_INFO;

typedef BOOL (WINAPI *SymInitializeS)( _In_ HANDLE hProcess,  _In_opt_ PCSTR UserSearchPath,   _In_ BOOL fInvadeProcess );
typedef BOOL (WINAPI *SymFromAddrS)( _In_ HANDLE hProcess, _In_ DWORD64 Address, _Out_opt_ PDWORD64 Displacement, _Inout_ PSYMBOL_INFO Symbol );


/**
* Klasa reprezentująca instancję aplikacji.
*/
class Aplikacja
{
	friend class Testy;
private:
	void LogApInfo();
	Log& log;
	shared_ptr<Cplugin> pluginy;
	shared_ptr<Gra> instancjaGry;

	string nazwaPlikuDanych;
	string jezykAplikacji;
	string folderPluginow;

protected:

	Aplikacja() throw(NiezainicjalizowanaKlasa);
	Aplikacja( const Aplikacja& );
	Aplikacja& operator=(const Aplikacja&);

	SymInitializeS symInitialize;
	SymFromAddrS symFromAddr;
	HMODULE hLibrary;
	bool isDbgHelpInit;

	bool ZaladujOpcje();

public:
	
	Gra& getGra();
	Log& getLog();

	bool WczytajDane();

	bool ZapiszGre() const;

	static Aplikacja& getInstance(){
		static Aplikacja app;
		return app;
	}

	string getStackTrace() const;

	~Aplikacja();
};

