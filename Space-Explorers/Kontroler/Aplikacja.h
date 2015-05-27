#pragma once
#pragma warning( disable : 4290 )
//#pragma warning( disable : 4996 )
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <locale>
#include <memory>
#include <random>
#include "Narzedzia\Singleton.h"
#include "Narzedzia\UstawieniaAplikacji.h"
#include "Eksport\TypyEksportowane.h"
// ----------------------------

namespace SPar{
	class ParserElement;
}

namespace SpEx {
	class Konsola;
	class ZarzadcaPluginow;
	class Fabrykator;
	class Gra;
	class IProxyBO;
	class ZarzadcaLokacji;
	class ZarzadcaUzytkownikow;
	class ZarzadcaZasobow;
}

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
		
		std::string pobierzDebugInfo() const;
		/**
		* \brief Metoda czy�ci wczytane dane.
		*
		* Metoda tworzy now� instancje gry, usuwaj�c star� bez zapisania danych. Usuwa r�wnie� informacje galaktykach, uk�adach s�onecznych oraz planetach, bez zapisywania aktualnych danych.
		*/
		void nowaGra();

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

		std::shared_ptr<Konsola> konsola_;

		std::shared_ptr<IProxyBO> proxy_;

		__int64 pobierzNumerLosowy();
		
		/**
		* \brief Metoda wyrzuca do loggera podstwowe dane identyfikuj�ce wersje aplikacji.
		*/
		void logApInfo() const;


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

		void rejestrujParametryKonsoli();

		void rejestrujKontrolkiDoTGUI();

		void rejestrujTypyZasobow();

		void rejestrujTypySkryptow();

		void rejestrujMetodyRPC();

		void konfigurujLogger();

		void konfigurujKonsole();

		void inicjalizujWinsock();

		void ustawPlikLogow();

		std::shared_ptr<ZarzadcaPluginow> zarzadcaPluginow_; /// Obiekt zarz�dzaj�cy plugginami.
		std::shared_ptr<Gra> instancjaGry_; /// Obiekt prezentuj�cy instancj� gry.
		std::shared_ptr<Fabrykator> fabrykator_; /// Instacja obiektu przechowuj�cego zbi�r fabryk.
		std::shared_ptr<ZarzadcaZasobow> zarzadcaZasobow_; /// Zarz�dca zasob�w.
		std::shared_ptr<ZarzadcaUzytkownikow> zarzadcaUzytkownikow_; /// Zarz�dca u�ytkownik�w.
		std::shared_ptr<ZarzadcaLokacji> zarzadcaLokacji_; /// Obiekt zarz�dzaj�cy lokacjami.

		bool czyKonsola_;
		
		struct OpcjeParametru{
			OpcjeParametru(unsigned char iloscParametrow, std::function<bool(std::vector<char*>)> funkcja)
				: iloscParametrow_(iloscParametrow), funkcja_(funkcja){}

			unsigned char iloscParametrow_ = 0;
			std::function<bool(std::vector<char*>)> funkcja_;
		};
		std::map< std::string, OpcjeParametru> parametryUruchomieniowe_;

		std::string plikKonfiguracyjny_; /// Adres pliku z danymi konfiguracyjnymi. Domy�lnie options.xml z katalogu z plikiem wykonywalnym.
		UstawieniaAplikacji ustawienia_; /// Klasa wczytuj�ca ustawienia z pliku konfiguracyjnego.

		std::mt19937_64 generator_;
		std::uniform_int_distribution <__int64> dystrybutor_;
	};
}
