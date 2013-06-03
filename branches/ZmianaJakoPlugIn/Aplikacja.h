#pragma once
#include "Main.h"
#include "ObiektBase.h"
#include "ObiektBaseInfo.h"
#include <Windows.h>
#include "Info.h"
#include "Biblioteki.h"
#include "SurowceInfo.h"
#include "StatekInfo.h"
#include "FuncTransf\ZmianaFabryka.h"
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
	friend class Testy;
private:
	void LogApInfo();
	ZmianaFabryka &fabryka;
protected:

	Aplikacja();

	SymInitializeS symInitialize;
	SymFromAddrS symFromAddr;
	HMODULE hLibrary;
	bool isDbgHelpInit;

	ObiektBaseInfo pustyobiekBaseInfo;
	ObiektBase pustyObiektBase;

	hash_map<Klucz, SurowceInfo* > listaSurowcowInfo;
	hash_map<Klucz, StatekInfo* > listaStatkowInfo;

	bool WczytajSurowce(ticpp::Node* root);
	bool WczytajStatki(ticpp::Node* root);

public:

	bool WczytajDane( const string& sFile );

	ZmianaFabryka& getZmianaFabryka();

	static Aplikacja& getInstance(){
		static Aplikacja app;
		return app;
	}

	string getStackTrace() const;

	~Aplikacja();

	const ObiektBase& getObiekt(IdType id)const{
		return pustyObiektBase;
	}

	StatekInfo& getStatek(const Klucz& id)const throw (NieznalezionoObiektu) {
		auto iter = listaStatkowInfo.find(id);
		if(iter==listaStatkowInfo.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
		return *(iter->second);
	}

	SurowceInfo& getSurowce(const Klucz& id)const throw (NieznalezionoObiektu) {
	auto iter = listaSurowcowInfo.find(id);
	if(iter==listaSurowcowInfo.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
	return *(iter->second);
	}

	const ObiektBase& getObiekt(Klucz k) const{
		return pustyObiektBase;
	}
};

