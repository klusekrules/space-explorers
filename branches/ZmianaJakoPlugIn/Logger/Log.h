#pragma once
#pragma warning( disable : 4251 )
#include "LoggerInterface.h"

using namespace std;
#include <string>
#include <vector>
#include <memory>

#include <Windows.h>

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
* Klasa zarz�dzaj�ca wy�wietlaniem komunikat�w loguj�cych. 
* Udowst�pnia mo�liwo�� blokowania pojedy�czych poziom�w komunikat�w jak i wszystkich jednocze�nie.\n
* Klasa implementuje 4 rodzaje komunikat�w:
*	- Debug
*	- Info
*	- Warning
*	- Error
*	
* W przysz�o�ci zostanie dodana mo�liwo�� logowania do konkretnych strumieni.
*/

class LOGGER_API Log
{
private:

	vector< shared_ptr<ostream> > outstream;

	/**
	* Funkcja wysy�aj�ca napis do strumienia.
	* \param p Napis wysy�any do strumienia.
	*/
	void print( const string& p );

	bool blogEnable; /**< Zmmienna blokuj�ca wysy�anie wszystkich komunikat�w do strumienia */
	bool blogDebugEnable; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Debug do strumienia */
	bool blogInfoEnable; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Info do strumienia */
	bool blogWarnEnable; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Warning do strumienia */
	bool blogErrorEnable; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Error do strumienia */
	string formatCzasu;
	Log();

	
	SymInitializeS symInitialize;
	SymFromAddrS symFromAddr;
	HMODULE hLibrary;
	bool isDbgHelpInit;

public:

	enum FormatCzasu{
		Data,
		Czas,
		DataCzas
	};

	void dodajGniazdoWyjsciowe(shared_ptr<ostream> &t);

	void ustawFormatCzasu( FormatCzasu format );

	static Log& getInstance();

	/**
	* Funkcja informuj�ca czy wysy�anie log�w jest odblokowane
	* \return Je�eli wysy�anie log�w jest odblokowane zwraca true, je�eli nie zwraca false.
	* \sa isLogDebugEnable()
	* \sa isLogInfoEnable()
	* \sa isLogWarnEnable()
	* \sa isLogErrorEnable()
	* \sa logEnable()
	* \sa logDisable()
	*/
	bool isLogEnable()const;

	/**
	* Funkcja informuj�ca czy wysy�anie log�w typu Debug jest odblokowane
	* \return Je�eli wysy�anie log�w typu Debug jest odblokowane zwraca true, je�eli nie zwraca false.
	* \sa isLogEnable()
	* \sa isLogInfoEnable()
	* \sa isLogWarnEnable()
	* \sa isLogErrorEnable()
	* \sa logDebugEnable()
	* \sa logDebugDisable()
	*/
	bool isLogDebugEnable()const;

	/**
	* Funkcja informuj�ca czy wysy�anie log�w typu Info jest odblokowane
	* \return Je�eli wysy�anie log�w typu Info jest odblokowane zwraca true, je�eli nie zwraca false.
	* \sa isLogEnable()
	* \sa isLogDebugEnable()
	* \sa isLogWarnEnable()
	* \sa isLogErrorEnable()
	* \sa logInfoEnable()
	* \sa logInfoDisable()
	*/
	bool isLogInfoEnable()const;

	/**
	* Funkcja informuj�ca czy wysy�anie log�w typu Warning jest odblokowane
	* \return Je�eli wysy�anie log�w typu Warning jest odblokowane zwraca true, je�eli nie zwraca false.
	* \sa isLogEnable()
	* \sa isLogDebugEnable()
	* \sa isLogInfoEnable()
	* \sa isLogErrorEnable()
	* \sa logWarnEnable()
	* \sa logWarnDisable()
	*/
	bool isLogWarnEnable()const;

	/**
	* Funkcja informuj�ca czy wysy�anie log�w typu Error jest odblokowane
	* \return Je�eli wysy�anie log�w typu Error jest odblokowane zwraca true, je�eli nie zwraca false.
	* \sa isLogEnable()
	* \sa isLogDebugEnable()
	* \sa isLogInfoEnable()
	* \sa isLogWarnEnable()
	* \sa logErrorEnable()
	* \sa logErrorDisable()
	*/
	bool isLogErrorEnable()const;

	/**
	* Odblokowanie wysy�ania log�w do strumienia.
	* \sa logDisable()
	* \sa logDebugEnable()
	* \sa logInfoEnable()
	* \sa logWarnEnable()
	* \sa logErrorEnable()
	* \sa isLogEnable()
	*/
	void logEnable();
	
	/**
	* Zablokowanie wysy�ania log�w do strumienia.
	* \sa logEnable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logWarnDisable()
	* \sa logErrorDisable()
	* \sa isLogEnable()
	*/
	void logDisable();

	/**
	* Odblokowanie wysy�ania log�w typu Debug do strumienia.
	* \sa logDebugDisable()
	* \sa logEnable()
	* \sa logInfoEnable()
	* \sa logWarnEnable()
	* \sa logErrorEnable()
	* \sa isLogDebugEnable()
	* \sa debug( string p )
	* \sa debug( LoggerInterface<T> &p )
	*/
	void logDebugEnable();
	
	/**
	* Zablokowanie wysy�ania log�w typu Debug do strumienia.
	* \sa logDebugEnable()
	* \sa logDisable()
	* \sa logInfoDisable()
	* \sa logWarnDisable()
	* \sa logErrorDisable()
	* \sa isLogDebugEnable()
	* \sa debug( string p )
	* \sa debug( LoggerInterface<T> &p )
	*/
	void logDebugDisable();

	/**
	* Odblokowanie wysy�ania log�w typu Info do strumienia.
	* \sa logInfoDisable()
	* \sa logEnable()
	* \sa logDebugDisable()
	* \sa logWarnEnable()
	* \sa logErrorEnable()
	* \sa isLogInfoEnable()
	* \sa debug( string p )
	* \sa debug( LoggerInterface<T> &p )
	*/
	void logInfoEnable();
	
	/**
	* Zablokowanie wysy�ania log�w typu Info do strumienia.
	* \sa logInfoEnable()
	* \sa logDisable()
	* \sa logDebugDisable()
	* \sa logWarnDisable()
	* \sa logErrorDisable()
	* \sa isLogInfoEnable()
	* \sa debug( string p )
	* \sa debug( LoggerInterface<T> &p )
	*/
	void logInfoDisable();

	/**
	* Odblokowanie wysy�ania log�w typu Warning do strumienia.
	* \sa logWarnDisable()
	* \sa logEnable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logErrorEnable()
	* \sa isLogWarnEnable()
	* \sa warn( string p )
	* \sa warn( LoggerInterface<T> &p )
	*/
	void logWarnEnable();
	
	/**
	* Zablokowanie wysy�ania log�w typu Warning do strumienia.
	* \sa logWarnEnable()
	* \sa logDisable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logErrorDisable()
	* \sa isLogWarnEnable()
	* \sa warn( string p )
	* \sa warn( LoggerInterface<T> &p )
	*/
	void logWarnDisable();

	/**
	* Odblokowanie wysy�ania log�w typu Error do strumienia.
	* \sa logErrorDisable()
	* \sa logEnable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logWarnDisable()
	* \sa isLogErrorEnable()
	* \sa error( string p )
	* \sa error( LoggerInterface<T> &p )
	*/
	void logErrorEnable();
	
	/**
	* Zablokowanie wysy�ania log�w typu Error do strumienia.
	* \sa logErrorEnable()
	* \sa logDisable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logWarnDisable()
	* \sa isLogErrorEnable()
	* \sa error( string p )
	* \sa error( LoggerInterface<T> &p )
	*/
	void logErrorDisable();

	/**
	* Funkcja wysy�aj�ca komunikat typu Info do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
	* \sa info( LoggerInterface<T> &p )
	* \sa logInfoEnable()
	* \sa logInfoDisable()
	* \sa isLogInfoEnable()
	*/
	void info( const string& p );

	/**
	* Funkcja wysy�aj�ca komunikat typu Info do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
	* \sa info( string p )
	* \sa logInfoEnable()
	* \sa logInfoDisable()
	* \sa isLogInfoEnable()
	*/
	void info( const LoggerInterface& p );

	/**
	* Funkcja wysy�aj�ca komunikat typu Warning do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
	* \sa warn( LoggerInterface<T> &p )
	* \sa logWarnEnable()
	* \sa logWarnDisable()
	* \sa isLogWarnEnable()
	*/
	void warn( const string& p );

	/**
	* Funkcja wysy�aj�ca komunikat typu Warning do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
	* \sa warn( string p )
	* \sa logWarnEnable()
	* \sa logWarnDisable()
	* \sa isLogWarnEnable()
	*/
	void warn( const LoggerInterface& p );

	/**
	* Funkcja wysy�aj�ca komunikat typu Error do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
	* \sa error( LoggerInterface<T> &p )
	* \sa logErrorEnable()
	* \sa logErrorDisable()
	* \sa isLogErrorEnable()
	*/
	void error( const string& p );

	/**
	* Funkcja wysy�aj�ca komunikat typu Error do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
	* \sa error( string p )
	* \sa logErrorEnable()
	* \sa logErrorDisable()
	* \sa isLogErrorEnable()
	*/
	void error( const LoggerInterface& p );

	/**
	* Funkcja wysy�aj�ca komunikat typu Debug do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
	* \sa debug( LoggerInterface<T> &p )
	* \sa logDebugEnable()
	* \sa logDebugDisable()
	* \sa isLogDebugEnable()
	*/
	void debug( const string& p );

	/**
	* Funkcja wysy�aj�ca komunikat typu Debug do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
	* \sa debug( string p )
	* \sa logDebugEnable()
	* \sa logDebugDisable()
	* \sa isLogDebugEnable()
	*/
	void debug( const LoggerInterface& p );

	string getTimeStamp() const;
		
	string getStackTrace() const;
};