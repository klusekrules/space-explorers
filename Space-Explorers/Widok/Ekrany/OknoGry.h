#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Logger\Log.h"
#include "Szkielet\EkranSzablon.h"
#include "Kontroler\Wielowatkowosc\Zadanie.h"
//#include "Widok\Tgui\LogListGui.h"
#include <future>

namespace SpEx{
	/**
	* \brief G³ówna klasa zarz¹dzaj¹ca oknem gry.
	*
	* Klasa zarz¹dza ekranami. Klasa wykonuje siê w osobnym w¹tku dla którego to s¹ tworzone okna.
	* \warning Uwaga!!! Klasa ma specyficzn¹ kombinajcê metod w³asnych oraz maszyny stanów, aby zosta³a zainicjalizowana poprawnie. Nazle¿y zwróciæ na to uwagê przy dokonywaniu zmian w okolicahc sposobu inicjalizacji okien lub maszyny stanów.
	* \author Daniel Wojdak
	* \version 2
	* \date 27-11-2014
	*/
	class OknoGry :
		public Watek,
		virtual public SLog::LoggerInterface
	{
	public:
		typedef std::shared_ptr< EkranSzablon > EkranPtr; /// Typ wskaŸnika do ekranu.
		typedef std::vector< EkranPtr > StosEkranow; /// Stos ekranów do wyœwietlenia.

		/**
		* \brief Konstruktor.
		* 
		* Metoda inicjalizuje wszystkie wymagane pola. Tworzy w¹tek w którym ma wykonywaæ siê metoda wykonuj. 
		* \param[in] wstrzymany - Je¿eli podana wartoœæ wynosi true w¹tek bêdzie wstrzymany odrazu po stworzeniu. Zostanie wznowiony po wykonaniu metody odblokuj.
		*/
		OknoGry(bool wstrzymany);

		/**
		* \brief Metoda inicjalizuj¹ca zamykanie.
		*
		* Metoda inicjalizuje zamykanie w¹tku. Czas potrzebny do poprawnego zamkniêcia jest nie okreœlony. Zale¿ny od iloœci zadañ do wykonania jakie oczekuj¹ w kolejce.
		* Istnieje metoda sprawdzaj¹ca czy w¹tek siê zakoñczy³ oraz czekaj¹ca na zakoñczenie w¹tku.
		*/
		void zakmnij();

		/**
		* \brief Metoda blokuj¹ca w¹tek po inicjalizacji.
		*
		* Metoda ustawiaj¹ca flagê która blokuje w¹tek po inicjalizacji. 
		* Nale¿y jej u¿yæ przed odblokowaniem w¹tku. Aby odblokowaæ w¹tek po inicjalizacji nale¿y u¿yæ metody uruchom.
		* \warning Uwaga!!! Nie nale¿y u¿ywaæ tej metody po zainicjalizowaniu. Spowoduje ona zablokowanie w¹tku wywo³uj¹cego tê metodê.
		*/
		void zatrzymajPoInicjalizacji();

		/**
		* \brief Metoda sprawdzaj¹ca czy okno zosta³o zainicjalizowane.
		* 
		* Metoda zwraca informacje o tym czy okno gry zosta³o ju¿ zainicjalizowane. Metoda blokuje w¹tek wywo³uj¹cy do czasu zakoñczenia inicjalizacji.
		* \return Zostanie zwrócona wartoœæ true, kiedy okno bêdzie zainicjalizowane poprawnie. Zostanie zwrócona wartoœæ false w wypadku gdy wyst¹pi b³¹d podczas inicjalizacji.
		*/
		bool czekajNaInicjalizacje();

		/**
		* \brief Metoda odblokowuj¹ca w¹tek po inicjalizacji.
		*
		* Metoda odblokowuj¹ w¹tek okna po poprawnie zakoñczonej inicjalizacji.
		*/
		void uruchom();

		/**
		* \brief Metoda pobieraj¹ca ekran.
		*
		* Metoda zwraca wskaŸnik do ekranu o identyfikatorze podanym w parametrze.
		* \param[in] id - Identyfikator ekranu do pobrania.
		* \return Zwraca wartoœæ nullptr je¿eli nieznaleziono ekranu lub wskaŸnik do ekranu je¿eli taki isnieje.
		*/
		EkranPtr pobierzEkran(const STyp::Identyfikator& id);

		/**
		* \brief Metoda pobieraj¹ca stos ekranów.
		*
		* Metoda zwraca aktualnie wyœwietlany stos ekranów.
		* \return Referencja do aktualnie wyœwietlanego stosu ekranów.
		*/
		StosEkranow& pobierzStosEkranow();

		/**
		* \brief Metoda ponownie konfiguruje ekran.
		*
		* Metoda ponownie konfiguruje ekran o podanym identyfikatorze. 
		* \param[in] id - Identyfikator ekranu do prze³adowania.
		* \note Je¿eli ekran o podanym id nie jest aktualnie wczytany, a znajduje siê w pliku, nie zostanie za³adowany do aplikacji.
		* \note Je¿eli ekran o podanym id jest aktualnie wczytany, a nie znajduje siê w pliku, pozostanie niezmieniony.
		*/
		void przeladujEkran( const STyp::Identyfikator& id );
		
		/**
		* \brief Metoda dodanie zadanie do wykonania.
		*
		* Metoda dodaje zadanie do wykonania w w¹tku rysuj¹cym okna. 
		* Zadanie bêdzie wykonane miêdzy wywo³aniami rysowania okna.
		* \param[in] zadanie - Zadanie jakie ma zostaæ wykonane w w¹tku graficznym.
		* \warning Uwaga!!! Nie nale¿y znacznie obci¹¿¹æ w¹tku rysuj¹cego okna, poniewa¿ mo¿e to spowodowaæ spadek p³ynnoœci gry. Nale¿y dodawaæ zadania do tej kolejki tylko w ostatecznoœci.
		*/
		void dodajZadanie(SpEx::Zadanie& zadanie);

		/**
		* \brief Metoda wstrzymuj¹ca rysowanie okien.
		*
		* Metoda wstrzymuje rysowanie okien po zakoñczeniu aktualnie rozpoczêtego rysowania. 
		* Metoda nie blokuje wykonywania zadañ przypisanych do kolejki.
		*/
		void pause();

		/**
		* \brief Metoda pobieraj¹ca infomacje o wstrzymaniu rysowania.
		*
		* Metoda zwraca informacje czy w¹tek graficzny wstrzyma³ rysowanie okien.
		* \return Zwraca wartoœæ true, je¿eli rysowanie okien jest wstrzymane. Zwraca false w przeciwnym wypadku.
		*/
		bool isPause() const;

		/**
		* \brief Metoda odblokowuj¹ca rysowanie okien.
		*
		* Metoda odblokowuje rysowanie okien w w¹tku graficznym.
		*/
		void unpause();
		
		/**
		* \brief Metoda dodaje komunikat logów.
		*
		* Metoda wyœwietla komunikat logów w globalnej kontrolce komunikatów.
		*/
		void wyswietlWiadomoscWGUI(unsigned int typ, const std::string& tresc);
		
		/**
		* \brief Destruktor.
		*/
		virtual ~OknoGry(void) = default;

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

		sf::RenderWindow oknoGlowne_; /// G³ówne okno aplikacji.
		sf::Shader testShadera_; /// Testowy shader

		std::atomic_bool przetwarzanie_; /// Informacja o wykonywaniu pêtli g³ównej w¹tku.
		std::promise<bool> inicjalizacja_; /// Przypisanie informacji o wyniku inicjalizacji.
		std::future<bool> inicjalizacjaWynik_; /// Wynik inicjalizacji.
		mutable std::mutex mutexUruchom_; /// Blokada po inicjalizacji.
		mutable std::mutex mutexInicjalizacja_; /// Blokada inicjalizacji.

		std::atomic_bool boolPauza_; /// Zmienna ustawiaj¹ca pauze.
		std::mutex mutexPauza_; /// Mutex dostêpu do zmiennej.

		mutable std::recursive_mutex mutexListaEkranow_; /// Mutex dostêpu do listy ekranów.
		std::map< STyp::Identyfikator, EkranPtr > listaEkranow_; /// Lista wszystkich ekranów.
		mutable std::mutex listaZadanMux_; /// Mutex dostêpu do zadañ.
		std::list< SpEx::Zadanie > listaZadan_; /// Kolejka zadañ.
		StosEkranow stosEkranow_; /// Stos ekranów.

		/**
		* \brief Metoda w¹tku.
		*
		* G³ówna metoda w¹tku.
		*/
		void wykonuj() override;

		/**
		* \brief Metoda inicjalizuj¹ca.
		*
		* Metoda wczytuje dane z plików oraz inicjalizuje ekrany.
		* \return Zwraca wartoœæ true je¿eli inicjalizacja siê powiedzie, zwraca wartoœæ false w przeciwnym wypadku.
		*/
		bool inicjalizacja();

		/**
		* \brief Metoda wychwytuj¹ca zdarzenia.
		*
		* Metoda wychwytuje zdarzenia systemowe i wykonuje akcje zwi¹zane z tymi zdarzeniami.
		* \param[in] stan - Aktualny stan dla którego nastêpuje przetwarzanie.
		*/
		void obslugaZdarzen(Stan& stan);

		/**
		* \brief Metoda uaktualniaj¹ca dane.
		*
		* Metoda uaktualnia parametry ekranu dla podanego stanu. Wywo³ywana jest metoda uaktualnij dla ekranów na stosie.
		* \param[in] stan - Aktualny stan dla którego nastêpuje przetwarzanie.
		*/
		void uaktualnianie(Stan& stan);

		/**
		* \brief Metoda odrysowuj¹ca okno.
		*
		* Metoda odrysowuje ekrany znajduj¹ce siê na stosie ekranów.
		*/
		void odmaluj();

		/**
		* \brief Metoda oblicza zmianê czasu.
		*
		* Metoda oblicza zmianê czasu od ostatniego wywo³ania pêtli.
		* \param[in] punktCzasu - aktualnie pobrany czas.
		* \return Up³yw czasu miêdzy ostatnim pomiarem, a aktualnie przekazanym punktem czasu.
		*/
		Stan::KrokCzasu obliczZmianeCzasu(std::chrono::high_resolution_clock::time_point punktCzasu);

		/**
		* \brief Metoda wczytuje ekrany z pliku.
		*
		* Metoda ³aduje do pamiêci listê ekranów z pliku.
		* \return Zwraca wartoœæ true je¿eli wczytywanie ekranów siê powiedzie, false w przeciwnym wypadku.
		*/
		bool wczytajEkrany();

		/**
		* \brief Metoda usuwa ekrany.
		*
		* Metoda usuwa wszytkie ekrany z listy ekranów.
		*/
		void usunWszystkieEkrany();

		/**
		* \brief Metoda wyswietla informacje.
		*
		* Metoda wyœwietla wersje software przydatne przy debugowaniu.
		*/
		void logujInfo();
	};
};
