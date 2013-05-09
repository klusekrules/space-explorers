// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define LOGGER_API __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#ifdef _DEBUG
#ifdef _WIN64
#pragma comment( lib, "logger-x64-d" )
#else if _WIN32
#pragma comment( lib, "logger-x86-d" )
#endif
#else
#ifdef _WIN64
#pragma comment( lib, "logger-x64" )
#else if _WIN32
#pragma comment( lib, "logger-x86" )
#endif
#endif
#endif

#include "targetver.h"
#pragma warning( disable : 4251 )
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <stack>

using namespace std;

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

// TODO: reference additional headers your program requires here
