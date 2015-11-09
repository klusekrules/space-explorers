#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Logger\Log.h"
#include "Szkielet\EkranSzablon.h"
#include "Kontroler\Wielowatkowosc\Zadanie.h"
//#include "Widok\Tgui\LogListGui.h"
#include <future>

namespace SpEx{
	/**
	* \brief G��wna klasa zarz�dzaj�ca oknem gry.
	*
	* Klasa zarz�dza ekranami. Klasa wykonuje si� w osobnym w�tku dla kt�rego to s� tworzone okna.
	* \warning Uwaga!!! Klasa ma specyficzn� kombinajc� metod w�asnych oraz maszyny stan�w, aby zosta�a zainicjalizowana poprawnie. Nazle�y zwr�ci� na to uwag� przy dokonywaniu zmian w okolicahc sposobu inicjalizacji okien lub maszyny stan�w.
	* \author Daniel Wojdak
	* \version 2
	* \date 27-11-2014
	*/
	class OknoGry :
		public Watek,
		virtual public SLog::LoggerInterface
	{
	public:
		typedef std::shared_ptr< EkranSzablon > EkranPtr; /// Typ wska�nika do ekranu.
		typedef std::vector< EkranPtr > StosEkranow; /// Stos ekran�w do wy�wietlenia.

		/**
		* \brief Konstruktor.
		* 
		* Metoda inicjalizuje wszystkie wymagane pola. Tworzy w�tek w kt�rym ma wykonywa� si� metoda wykonuj. 
		* \param[in] wstrzymany - Je�eli podana warto�� wynosi true w�tek b�dzie wstrzymany odrazu po stworzeniu. Zostanie wznowiony po wykonaniu metody odblokuj.
		*/
		OknoGry(bool wstrzymany);

		/**
		* \brief Metoda inicjalizuj�ca zamykanie.
		*
		* Metoda inicjalizuje zamykanie w�tku. Czas potrzebny do poprawnego zamkni�cia jest nie okre�lony. Zale�ny od ilo�ci zada� do wykonania jakie oczekuj� w kolejce.
		* Istnieje metoda sprawdzaj�ca czy w�tek si� zako�czy� oraz czekaj�ca na zako�czenie w�tku.
		*/
		void zakmnij();

		/**
		* \brief Metoda blokuj�ca w�tek po inicjalizacji.
		*
		* Metoda ustawiaj�ca flag� kt�ra blokuje w�tek po inicjalizacji. 
		* Nale�y jej u�y� przed odblokowaniem w�tku. Aby odblokowa� w�tek po inicjalizacji nale�y u�y� metody uruchom.
		* \warning Uwaga!!! Nie nale�y u�ywa� tej metody po zainicjalizowaniu. Spowoduje ona zablokowanie w�tku wywo�uj�cego t� metod�.
		*/
		void zatrzymajPoInicjalizacji();

		/**
		* \brief Metoda sprawdzaj�ca czy okno zosta�o zainicjalizowane.
		* 
		* Metoda zwraca informacje o tym czy okno gry zosta�o ju� zainicjalizowane. Metoda blokuje w�tek wywo�uj�cy do czasu zako�czenia inicjalizacji.
		* \return Zostanie zwr�cona warto�� true, kiedy okno b�dzie zainicjalizowane poprawnie. Zostanie zwr�cona warto�� false w wypadku gdy wyst�pi b��d podczas inicjalizacji.
		*/
		bool czekajNaInicjalizacje();

		/**
		* \brief Metoda odblokowuj�ca w�tek po inicjalizacji.
		*
		* Metoda odblokowuj� w�tek okna po poprawnie zako�czonej inicjalizacji.
		*/
		void uruchom();

		/**
		* \brief Metoda pobieraj�ca ekran.
		*
		* Metoda zwraca wska�nik do ekranu o identyfikatorze podanym w parametrze.
		* \param[in] id - Identyfikator ekranu do pobrania.
		* \return Zwraca warto�� nullptr je�eli nieznaleziono ekranu lub wska�nik do ekranu je�eli taki isnieje.
		*/
		EkranPtr pobierzEkran(const STyp::Identyfikator& id);

		/**
		* \brief Metoda pobieraj�ca stos ekran�w.
		*
		* Metoda zwraca aktualnie wy�wietlany stos ekran�w.
		* \return Referencja do aktualnie wy�wietlanego stosu ekran�w.
		*/
		StosEkranow& pobierzStosEkranow();

		/**
		* \brief Metoda ponownie konfiguruje ekran.
		*
		* Metoda ponownie konfiguruje ekran o podanym identyfikatorze. 
		* \param[in] id - Identyfikator ekranu do prze�adowania.
		* \note Je�eli ekran o podanym id nie jest aktualnie wczytany, a znajduje si� w pliku, nie zostanie za�adowany do aplikacji.
		* \note Je�eli ekran o podanym id jest aktualnie wczytany, a nie znajduje si� w pliku, pozostanie niezmieniony.
		*/
		void przeladujEkran( const STyp::Identyfikator& id );
		
		/**
		* \brief Metoda dodanie zadanie do wykonania.
		*
		* Metoda dodaje zadanie do wykonania w w�tku rysuj�cym okna. 
		* Zadanie b�dzie wykonane mi�dzy wywo�aniami rysowania okna.
		* \param[in] zadanie - Zadanie jakie ma zosta� wykonane w w�tku graficznym.
		* \warning Uwaga!!! Nie nale�y znacznie obci���� w�tku rysuj�cego okna, poniewa� mo�e to spowodowa� spadek p�ynno�ci gry. Nale�y dodawa� zadania do tej kolejki tylko w ostateczno�ci.
		*/
		void dodajZadanie(SpEx::Zadanie& zadanie);

		/**
		* \brief Metoda wstrzymuj�ca rysowanie okien.
		*
		* Metoda wstrzymuje rysowanie okien po zako�czeniu aktualnie rozpocz�tego rysowania. 
		* Metoda nie blokuje wykonywania zada� przypisanych do kolejki.
		*/
		void pause();

		/**
		* \brief Metoda pobieraj�ca infomacje o wstrzymaniu rysowania.
		*
		* Metoda zwraca informacje czy w�tek graficzny wstrzyma� rysowanie okien.
		* \return Zwraca warto�� true, je�eli rysowanie okien jest wstrzymane. Zwraca false w przeciwnym wypadku.
		*/
		bool isPause() const;

		/**
		* \brief Metoda odblokowuj�ca rysowanie okien.
		*
		* Metoda odblokowuje rysowanie okien w w�tku graficznym.
		*/
		void unpause();
		
		/**
		* \brief Metoda dodaje komunikat log�w.
		*
		* Metoda wy�wietla komunikat log�w w globalnej kontrolce komunikat�w.
		*/
		void wyswietlWiadomoscWGUI(unsigned int typ, const std::string& tresc);
		
		/**
		* \brief Destruktor.
		*/
		virtual ~OknoGry(void) = default;

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

		sf::RenderWindow oknoGlowne_; /// G��wne okno aplikacji.
		sf::Shader testShadera_; /// Testowy shader

		std::atomic_bool przetwarzanie_; /// Informacja o wykonywaniu p�tli g��wnej w�tku.
		std::promise<bool> inicjalizacja_; /// Przypisanie informacji o wyniku inicjalizacji.
		std::future<bool> inicjalizacjaWynik_; /// Wynik inicjalizacji.
		mutable std::mutex mutexUruchom_; /// Blokada po inicjalizacji.
		mutable std::mutex mutexInicjalizacja_; /// Blokada inicjalizacji.

		std::atomic_bool boolPauza_; /// Zmienna ustawiaj�ca pauze.
		std::mutex mutexPauza_; /// Mutex dost�pu do zmiennej.

		mutable std::recursive_mutex mutexListaEkranow_; /// Mutex dost�pu do listy ekran�w.
		std::map< STyp::Identyfikator, EkranPtr > listaEkranow_; /// Lista wszystkich ekran�w.
		mutable std::mutex listaZadanMux_; /// Mutex dost�pu do zada�.
		std::list< SpEx::Zadanie > listaZadan_; /// Kolejka zada�.
		StosEkranow stosEkranow_; /// Stos ekran�w.

		/**
		* \brief Metoda w�tku.
		*
		* G��wna metoda w�tku.
		*/
		void wykonuj() override;

		/**
		* \brief Metoda inicjalizuj�ca.
		*
		* Metoda wczytuje dane z plik�w oraz inicjalizuje ekrany.
		* \return Zwraca warto�� true je�eli inicjalizacja si� powiedzie, zwraca warto�� false w przeciwnym wypadku.
		*/
		bool inicjalizacja();

		/**
		* \brief Metoda wychwytuj�ca zdarzenia.
		*
		* Metoda wychwytuje zdarzenia systemowe i wykonuje akcje zwi�zane z tymi zdarzeniami.
		* \param[in] stan - Aktualny stan dla kt�rego nast�puje przetwarzanie.
		*/
		void obslugaZdarzen(Stan& stan);

		/**
		* \brief Metoda uaktualniaj�ca dane.
		*
		* Metoda uaktualnia parametry ekranu dla podanego stanu. Wywo�ywana jest metoda uaktualnij dla ekran�w na stosie.
		* \param[in] stan - Aktualny stan dla kt�rego nast�puje przetwarzanie.
		*/
		void uaktualnianie(Stan& stan);

		/**
		* \brief Metoda odrysowuj�ca okno.
		*
		* Metoda odrysowuje ekrany znajduj�ce si� na stosie ekran�w.
		*/
		void odmaluj();

		/**
		* \brief Metoda oblicza zmian� czasu.
		*
		* Metoda oblicza zmian� czasu od ostatniego wywo�ania p�tli.
		* \param[in] punktCzasu - aktualnie pobrany czas.
		* \return Up�yw czasu mi�dzy ostatnim pomiarem, a aktualnie przekazanym punktem czasu.
		*/
		Stan::KrokCzasu obliczZmianeCzasu(std::chrono::high_resolution_clock::time_point punktCzasu);

		/**
		* \brief Metoda wczytuje ekrany z pliku.
		*
		* Metoda �aduje do pami�ci list� ekran�w z pliku.
		* \return Zwraca warto�� true je�eli wczytywanie ekran�w si� powiedzie, false w przeciwnym wypadku.
		*/
		bool wczytajEkrany();

		/**
		* \brief Metoda usuwa ekrany.
		*
		* Metoda usuwa wszytkie ekrany z listy ekran�w.
		*/
		void usunWszystkieEkrany();

		/**
		* \brief Metoda wyswietla informacje.
		*
		* Metoda wy�wietla wersje software przydatne przy debugowaniu.
		*/
		void logujInfo();
	};
};
