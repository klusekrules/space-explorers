#pragma once
#include "Main.h"
#include <Windows.h>
#include "Biblioteki.h"
#include "plugin\plugin.h"
#include "Gra.h"
#include "Singleton.h"
#include "UstawieniaAplikacji.h"

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
	* \brief Klasa reprezentuj�ca aplikacje.
	*
	* G��wna klasa programu. Reprezentuje ca�� apliakcje.
	* \author Daniel Wojdak
	* \version 1
	* \date 26-07-2013
	*/
	class Aplikacja:
		public se::Singleton<Aplikacja>
	{
		friend class TestyJednostkowe;
		friend class se::Singleton<Aplikacja>;
	public:

		/**
		* Ilo�� argument�w przekazanych w linii komend.
		*/
		static int iloscArgumentow;

		/**
		* Argumenty przekazane w linii komend
		*/
		static char** argumenty;

		/**
		* \brief Metoda �aduj�ca dane gry.
		*
		* \return true je�eli uda si� wczyta� dane, false w przeciwnym wypadku.
		*/
		bool wczytajDane( std::shared_ptr<SPar::ParserElement> root );

		/**
		* \brief Metoda zapisuj�ca stan gry.
		*
		* \return true je�eli uda si� zapisac gr�, false w przeciwnym wypadku.
		*/
		bool zapiszGre(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda wczytuj�ca stan gry.
		*
		* \return true je�eli uda si� wczyta� stan gry, false w przeciwnym wypadku.
		*/
		bool wczytajGre(std::shared_ptr<SPar::ParserElement> root);
		
		/**
		* \brief Metoda pobieraj�ca �la stosu.
		*
		* \return Napis zawieraj�cy �lad stosu.
		*/
		std::string pobierzSladStosu() const;

		void wyczyscDane();

		/**
		* \brief Metoda pobieraj�ca instacj� gry.
		*
		* \return Referencja do obiektu gry.
		*/
		inline Gra& pobierzGre() const{
			return *instancjaGry_;
		}
		
		inline ZarzadcaPamieci& pobierzZarzadce(){
			return zarzadca_;
		}
		
		/**
		* \brief Destruktor.
		*/
		~Aplikacja();

		SLog::Log& logger_; /// Instancja loggera.

		SZmi::ZmianaFabryka fabrykaZmian_; /// Instancja fabryki zmian.

	private:

		/**
		* \brief Konstruktor.
		*
		* Metoda wyrzuca wyj�tek kiedy wyst�pi b��d przy inicjalizacji aplikacji.
		*/
		Aplikacja();

		/**
		* \brief Metoda wcztuj�ca opcje aplikacji.
		*
		* \return true je�eli uda si� wczyta� opcje, false w przeciwnym wypadku.
		*/
		bool zaladujOpcje();

		/**
		* \brief Metoda przetwarzaj�ca argumenty linii komend
		*
		* Metoda odczytuje i przetwarza wszysktie argumenty przekazane w linii komend. Ustawia odpowiednie opcje programu.
		*/
		bool przetworzArgumenty();

		/**
		* \brief Metoda wyrzuca do loggera podstwowe dane identyfikuj�ce wersje aplikacji.
		*/
		void logApInfo() const;

		std::shared_ptr<SPlu::Cplugin> pluginy_; /// Obiekt zarz�dzaj�cy plugginami.
		std::shared_ptr<Gra> instancjaGry_; /// Obiekt prezentuj�cy instancj� gry.

		SymInitializeS symInitialize_; /// Metoda pomocnicza przy zrzucaniu �ladu stosu.
		SymFromAddrS symFromAddr_; /// Metoda pomocnicza przy zrzucaniu �ladu stosu.
		HMODULE uchwyt_; /// Uchwyt blioteki pomocniczej.
		bool czyZainicjalizowanaBiblioteka_; /// Informacja czy uda�osi� za�adowa� bibliotek� pomocnicz�.

		STyp::Identyfikator idEkranuStartowego_;
		
		ZarzadcaPamieci zarzadca_; /// Obiekt zarz�dzaj�cy lokacjami.

		std::string plikKonfiguracyjny_;
		UstawieniaAplikacji ustawienia_;
	};
}
