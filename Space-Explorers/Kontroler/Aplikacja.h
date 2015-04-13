#pragma once
#pragma warning( disable : 4290 )
//#pragma warning( disable : 4996 )
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <locale>
#include <memory>
#include <random>
#include "Utils\Singleton.h"
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


// ----------------------------

namespace SPar{
	class ParserElement;
}

namespace SpEx {
	class Konsola;
	class ZarzadcaPluginow;
	class Fabrykator;
	class Gra;
	class ZarzadcaLokacji;
	class ZarzadcaUzytkownikow;
	class ZarzadcaZasobow;
}
// ----------------------------


namespace SpEx {

	/**
	* \brief Klasa reprezentuj�ca aplikacje.
	*
	* G��wna klasa programu. Reprezentuje ca�� apliakcje.
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
		* Ilo�� argument�w przekazanych w linii komend.
		*/
		static int iloscArgumentow;

		/**
		* Argumenty przekazane w linii komend
		*/
		static char** argumenty;

		/**
		* \brief Metoda zapisuj�ca stan gry.
		*
		* \return Zwraca warto�� true, je�eli uda si� zapisa� dane, false w przeciwnym wypadku.
		*/
		bool zapiszGre();

		/**
		* \brief Metoda wczytuj�ca stan gry.
		*
		* Metoda wczytuje dane opisowe obiekt�w oraz parametry zarz�dcy pami�ci. Metoda waliduje wczytane dane.
		* \param[in] root - G��wny w�ze� zawieraj�cy dane obiekt�w opisuj�cych.
		* \return Zwraca warto�� true, je�eli uda si� wczyta� stan gry, false w przeciwnym wypadku.
		*/
		bool wczytajGre(std::shared_ptr<SPar::ParserElement> root);
		
		/**
		* \brief Metoda pobieraj�ca �lad stosu.
		*
		* Metoda generuje �lad stosu aktualnego w�tku, w wkt�rym zosta�a wywo�ana.
		* \return Napis zawieraj�cy �lad stosu.
		*/
		std::string pobierzSladStosu() const;

		std::string pobierzDebugInfo() const;
		/**
		* \brief Metoda czy�ci wczytane dane.
		*
		* Metoda tworzy now� instancje gry, usuwaj�c star� bez zapisania danych. Usuwa r�wnie� informacje galaktykach, uk�adach s�onecznych oraz planetach, bez zapisywania aktualnych danych.
		*/
		void wyczyscDane();

		/**
		* \brief Metoda pobieraj�ca instacj� gry.
		*
		* \return Referencja do obiektu gry.
		*/
		inline Gra& pobierzGre() const{
			return *instancjaGry_;
		}
		
		/**
		* \brief Metoda pobieraj�ca zarz�dc� lokacji.
		*
		* \return Referencja do obiektu zarz�dcy.
		*/
		inline ZarzadcaLokacji& pobierzZarzadceLokacji(){
			return *zarzadcaLokacji_;
		}

		inline UstawieniaAplikacji& pobierzUstawieniaAplikacji(){
			return ustawienia_;
		}

		inline Fabrykator& pobierzFabrykator(){
			return *fabrykator_;
		}

		inline ZarzadcaZasobow& pobierzZarzadceZasobow(){
			return *zarzadcaZasobow_;
		}

		inline ZarzadcaUzytkownikow& pobierzZarzadceUzytkownikow(){
			return *zarzadcaUzytkownikow_;
		}

		inline ZarzadcaPluginow& pobierzZarzadcePluginow(){
			return *zarzadcaPluginow_;
		}
		/**
		* \brief Destruktor.
		*/
		virtual ~Aplikacja();

		SLog::Log& logger_; /// Instancja loggera.
		
		__int64 pobierzNumerLosowy();

		void wykonajPolecenie(const std::string&);

		void start();

		/**
		* \brief Metoda tworz�ca tekstowy opis obiektu.
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

		void rejestrujParametryKonsoli();
		std::shared_ptr<Konsola> konsola_;
		std::shared_ptr<ZarzadcaPluginow> zarzadcaPluginow_; /// Obiekt zarz�dzaj�cy plugginami.
		std::shared_ptr<Gra> instancjaGry_; /// Obiekt prezentuj�cy instancj� gry.
		std::shared_ptr<Fabrykator> fabrykator_; /// Instacja obiektu przechowuj�cego zbi�r fabryk.
		std::shared_ptr<ZarzadcaZasobow> zarzadcaZasobow_; /// Zarz�dca zasob�w.
		std::shared_ptr<ZarzadcaUzytkownikow> zarzadcaUzytkownikow_; /// Zarz�dca u�ytkownik�w.
		std::shared_ptr<ZarzadcaLokacji> zarzadcaLokacji_; /// Obiekt zarz�dzaj�cy lokacjami.

		std::map< std::string, std::function<void(std::string)>> poleceniaKonsoli_;
		bool czyKonsola_;

		enum TrybAplikacji{
			Serwer,
			Klient
		};

		TrybAplikacji tryb_;

		struct OpcjeParametru{
			OpcjeParametru(unsigned char iloscParametrow, std::function<bool(std::vector<char*>)> funkcja)
				: iloscParametrow_(iloscParametrow), funkcja_(funkcja){}

			unsigned char iloscParametrow_ = 0;
			std::function<bool(std::vector<char*>)> funkcja_;
		};
		std::map< std::string, OpcjeParametru> parametryUruchomieniowe_;

		SymInitializeS symInitialize_; /// Metoda pomocnicza przy zrzucaniu �ladu stosu.
		SymFromAddrS symFromAddr_; /// Metoda pomocnicza przy zrzucaniu �ladu stosu.
		HMODULE uchwyt_; /// Uchwyt blioteki pomocniczej.
		bool czyZainicjalizowanaBiblioteka_; /// Informacja czy uda�osi� za�adowa� bibliotek� pomocnicz�.

		
		std::string plikKonfiguracyjny_; /// Adres pliku z danymi konfiguracyjnymi. Domy�lnie options.xml z katalogu z plikiem wykonywalnym.
		UstawieniaAplikacji ustawienia_; /// Klasa wczytuj�ca ustawienia z pliku konfiguracyjnego.

		std::mt19937_64 generator_;
		std::uniform_int_distribution <__int64> dystrybutor_;
	};
}
