#pragma once
#include "Main.h"
#include "ObiektBase.h"
#include "ObiektBaseInfo.h"
#include <Windows.h>
#include "Info.h"
#include "Biblioteki.h"
#include "SurowceInfo.h"

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
* Klasa reprezentuj¹ca instancjê aplikacji.
*/
class Aplikacja
{
protected:

	Aplikacja();

	SymInitializeS symInitialize;
	SymFromAddrS symFromAddr;
	HMODULE hLibrary;
	bool isDbgHelpInit;

	ObiektBaseInfo pustyobiekBaseInfo;
	ObiektBase pustyObiektBase;

	hash_map<Klucz, SurowceInfo* > listaSurowcowInfo;

	bool WczytajSurowce(ticpp::Node* root);

public:

	bool WczytajDane();

	static Aplikacja& getInstance(){
		static Aplikacja app;
		return app;
	}

	string getStackTrace() const;

	~Aplikacja();

	const ObiektBase& getObiekt(IdType id){
		return pustyObiektBase;
	}
	const ObiektBase& getObiekt(Klucz k){
		return pustyObiektBase;
	}
};

