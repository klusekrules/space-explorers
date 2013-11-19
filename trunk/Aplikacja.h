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
* \brief Klasa reprezentuj¹ca aplikacje.
*
* G³ówna klasa programu. Reprezentuje ca³¹ apliakcje.
* \author Daniel Wojdak
* \version 1
* \date 26-07-2013
*/
class Aplikacja
{
	friend class Testy;

public:
	
	/**
	* Iloœæ argumentów przekazanych w linii komend.
	*/
	static int iloscArgumentow;

	/**
	* Argumenty przekazane w linii komend
	*/
	static char** argumenty;

	/**
	* \brief Metoda pobieraj¹ca instacjê gry.
	* 
	* \return Referencja do obiektu gry.
	*/
	Gra& pobierzGre() const;

	/**
	* \brief Metoda pobieraj¹ca instacjê obiektu tworz¹cego logi.
	*
	* \return Referencja do loggera.
	*/
	Log& pobierzLogger() const;

	/**
	* \brief Metoda ³aduj¹ca dane gry.
	*
	* \return true je¿eli uda siê wczytaæ dane, false w przeciwnym wypadku.
	*/
	bool wczytajDane();

	/**
	* \brief Metoda zapisuj¹ca stan gry.
	*
	* \return true je¿eli uda siê zapisac grê, flase w przeciwnym wypadku.
	*/
	bool zapiszGre(const string& nazwa, const string& hash) const;

	/**
	* \brief Metoda wczytuj¹ca stan gry.
	*
	* \return true je¿eli uda siê wczytaæ stan gry, false w przeciwnym wypadku.
	*/
	bool wczytajGre(const string& nazwa, const string& hash);

	/**
	* \brief Metoda pobieraj¹ca instacjê Aplikacji.
	*
	* \return Referencja do instancji apalikacji.
	*/
	static Aplikacja& pobierzInstancje();

	/**
	* \brief Metoda pobieraj¹ca œla stosu.
	*
	* \return Napis zawieraj¹cy œlad stosu.
	*/
	string pobierzSladStosu() const;

	const Identyfikator& pobierzIdEkranuStartowego() const;

	/**
	* \brief Destruktor.
	*/
	~Aplikacja();

private:

	/**
	* \brief Konstruktor.
	*
	* Metoda wyrzuca wyj¹tek kiedy wyst¹pi b³¹d przy inicjalizacji aplikacji.
	* \throw NiezainicjalizowanaKlasa
	*/
	Aplikacja() throw(NiezainicjalizowanaKlasa);

	/**
	* \brief Konstruktor kopiuj¹cy.
	* \todo Oznaczenie metody jako delete kiedy kompilator bêdzie to wspieraæ.
	*/
	Aplikacja( const Aplikacja& aplikacja );

	/**
	* \brief Operator przypisania.
	* \todo Oznaczenie metody jako delete kiedy kompilator bêdzie to wspieraæ.
	*/
	Aplikacja& operator=( const Aplikacja& aplikacja );

	/**
	* \brief Metoda wcztuj¹ca opcje aplikacji.
	*
	* \return true je¿eli uda siê wczytaæ opcje, false w przeciwnym wypadku.
	*/
	bool zaladujOpcje();

	/**
	* \brief Metoda przetwarzaj¹ca argumenty linii komend
	*
	* Metoda odczytuje i przetwarza wszysktie argumenty przekazane w linii komend. Ustawia odpowiednie opcje programu.
	*/
	bool przetworzArgumenty();

	/**
	* \brief Metoda wyrzuca do loggera podstwowe dane identyfikuj¹ce wersje aplikacji.
	*/
	void logApInfo() const;

	Log& logger_; /// Instancja loggera.
	shared_ptr<Cplugin> pluginy_; /// Obiekt zarz¹dzaj¹cy plugginami.
	shared_ptr<Gra> instancjaGry_; /// Obiekt prezentuj¹cy instancjê gry.

	string nazwaPlikuOpcji_; /// Nazwa pliku z opcjami.
	string nazwaPlikuDanych_; /// Opcja: Nazwa pliku z danymi.
	string jezykAplikacji_; /// Opcja: Jêzyk apllikacji.
	string folderPluginow_; /// Opcja: lokalizacja folderu z pluginami.

	SymInitializeS symInitialize_; /// Metoda pomocnicza przy zrzucaniu œladu stosu.
	SymFromAddrS symFromAddr_; /// Metoda pomocnicza przy zrzucaniu œladu stosu.
	HMODULE uchwyt_; /// Uchwyt blioteki pomocniczej.
	bool czyZainicjalizowanaBiblioteka_; /// Informacja czy uda³osiê za³adowaæ bibliotekê pomocnicz¹.

	Identyfikator idEkranuStartowego_;
};
