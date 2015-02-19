#pragma once
#pragma warning( disable : 4290 )
//#pragma warning( disable : 4996 )
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <locale>
#include "plugin\plugin.h"
#include "Gra.h"
#include "Singleton.h"
#include "UstawieniaAplikacji.h"
#include "Fabrykator.h"
#include "ZarzadcaZasobow.h"
#include "ZarzadcaUzytkownikow.h"

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

namespace SpEx {

	/**
	* \brief Klasa reprezentuj¹ca aplikacje.
	*
	* G³ówna klasa programu. Reprezentuje ca³¹ apliakcje.
	* \author Daniel Wojdak
	* \version 6
	* \date 27-11-2014
	*/
	class Aplikacja:
		public se::Singleton<Aplikacja>,
		virtual public SLog::LoggerInterface
	{
		friend class TestyJednostkowe;
		friend class se::Singleton<Aplikacja>;
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
		* \brief Metoda zapisuj¹ca stan gry.
		*
		* \return Zwraca wartoœæ true, je¿eli uda siê zapisaæ dane, false w przeciwnym wypadku.
		*/
		bool zapiszGre();

		/**
		* \brief Metoda wczytuj¹ca stan gry.
		*
		* Metoda wczytuje dane opisowe obiektów oraz parametry zarz¹dcy pamiêci. Metoda waliduje wczytane dane.
		* \param[in] root - G³ówny wêze³ zawieraj¹cy dane obiektów opisuj¹cych.
		* \return Zwraca wartoœæ true, je¿eli uda siê wczytaæ stan gry, false w przeciwnym wypadku.
		*/
		bool wczytajGre(std::shared_ptr<SPar::ParserElement> root);
		
		/**
		* \brief Metoda pobieraj¹ca œlad stosu.
		*
		* Metoda generuje œlad stosu aktualnego w¹tku, w wktórym zosta³a wywo³ana.
		* \return Napis zawieraj¹cy œlad stosu.
		*/
		std::string pobierzSladStosu() const;

		std::string pobierzDebugInfo() const;
		/**
		* \brief Metoda czyœci wczytane dane.
		*
		* Metoda tworzy now¹ instancje gry, usuwaj¹c star¹ bez zapisania danych. Usuwa równie¿ informacje galaktykach, uk³adach s³onecznych oraz planetach, bez zapisywania aktualnych danych.
		*/
		void wyczyscDane();

		/**
		* \brief Metoda pobieraj¹ca instacjê gry.
		*
		* \return Referencja do obiektu gry.
		*/
		inline Gra& pobierzGre() const{
			return *instancjaGry_;
		}
		
		/**
		* \brief Metoda pobieraj¹ca zarz¹dcê lokacji.
		*
		* \return Referencja do obiektu zarz¹dcy.
		*/
		inline ZarzadcaLokacji& pobierzZarzadceLokacji(){
			return zarzadcaLokacji_;
		}

		inline UstawieniaAplikacji& pobierzUstawieniaAplikacji(){
			return ustawienia_;
		}

		/**
		* \brief Destruktor.
		*/
		~Aplikacja();

		SLog::Log& logger_; /// Instancja loggera.
		
		Fabrykator fabrykator_; /// Instacja obiektu przechowuj¹cego zbiór fabryk.

		ZarzadcaZasobow zarzadcaZasobow_; /// Zarz¹dca zasobów.

		ZarzadcaUzytkownikow zarzadcaUzytkownikow_; /// Zarz¹dca u¿ytkowników.

		/**
		* \brief Metoda tworz¹ca tekstowy opis obiektu.
		*
		* Metoda generuje czytelny tekstowy opis obiektu.
		* \return Opis obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 27-11-2014
		*/
		std::string napis() const override;
	private:

		/**
		* \brief Konstruktor.
		*
		* Metoda wyrzuca wyj¹tek kiedy wyst¹pi b³¹d przy inicjalizacji aplikacji.
		*/
		Aplikacja();

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

		std::shared_ptr<SPlu::Cplugin> pluginy_; /// Obiekt zarz¹dzaj¹cy plugginami.
		std::shared_ptr<Gra> instancjaGry_; /// Obiekt prezentuj¹cy instancjê gry.

		SymInitializeS symInitialize_; /// Metoda pomocnicza przy zrzucaniu œladu stosu.
		SymFromAddrS symFromAddr_; /// Metoda pomocnicza przy zrzucaniu œladu stosu.
		HMODULE uchwyt_; /// Uchwyt blioteki pomocniczej.
		bool czyZainicjalizowanaBiblioteka_; /// Informacja czy uda³osiê za³adowaæ bibliotekê pomocnicz¹.

		ZarzadcaLokacji zarzadcaLokacji_; /// Obiekt zarz¹dzaj¹cy lokacjami.
		
		std::string plikKonfiguracyjny_; /// Adres pliku z danymi konfiguracyjnymi. Domyœlnie options.xml z katalogu z plikiem wykonywalnym.
		UstawieniaAplikacji ustawienia_; /// Klasa wczytuj¹ca ustawienia z pliku konfiguracyjnego.
	};
}
