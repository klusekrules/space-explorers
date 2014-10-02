#pragma once
#include "Logger\\Log.h"
#include "OknoGry.h"
#include "StanInfo.h"
#include "Zdarzenie.h"
#include "Stan.h"
#include "Singleton.h"
#include "TypyEksportowne.h"
#include "MenadzerWatkow.h"

namespace SpEx{

	/**
	* \brief Klasa maszyny stan�w.
	*
	* Klasa obs�uguj� zdarzenia oraz zarz�dza stanami. W metodzie tej klasy jest zaimplementowana g��wna p�tla z obs�ug� zdarze�.
	* \author Daniel Wojdak
	* \version 3
	* \date 02-10-2014
	*/
	class MaszynaStanow
		: public se::Singleton<MaszynaStanow>
	{
		friend class se::Singleton<MaszynaStanow>;
	public:
		
		/**
		* \brief Klasa stanu dla skrypt�w.
		*
		* Klasa stanu dla skrypt�w, u�awiaj�ca przepisywanie informacji oraz zabezpiecza przez niekontrolowan� zmian�.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		class StanDlaSkryptu{
			friend class MaszynaStanow;
		public:

			/**
			* \brief Konstruktor.
			*
			* Konstruktor.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			StanDlaSkryptu();

			/**
			* \brief Metoda pobieraj�ca dane zdarzenia.
			*
			* Metoda pobieraj�ca dane zdarzenia.
			* \param[out] zdarzenie - Referencja do obiektu gdzie zostan� zapisane dane.
			* \return Zwracana jest warto�c true, je�eli zdarzenie jest poprawne. Warto�� false jest zwracana w przeciwnym wypadku.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			bool pobierzZdarzenie(struct Zdarzenie_t& zdarzenie);

			/**
			* \brief Metoda pobieraj�ca dane poprzedniego stanu.
			*
			* Metoda pobieraj�ca dane poprzedniego stanu.
			* \param[out] stan - Referencja do obiektu gdzie zostan� zapisane dane.
			* \return Zwracana jest warto�c true, je�eli poprzedni stan jest poprawny. Warto�� false jest zwracana w przeciwnym wypadku.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			bool pobierzPoprzedniStan(struct Stan_t& stan);

			/**
			* \brief Metoda pobieraj�ca dane aktualnego stanu.
			*
			* Metoda pobieraj�ca dane aktualnego stanu.
			* \param[out] stan - Referencja do obiektu gdzie zostan� zapisane dane.
			* \return Zwracana jest warto�c true, je�eli aktualny stan jest poprawny. Warto�� false jest zwracana w przeciwnym wypadku.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			bool pobierzAktualnyStan(struct Stan_t& stan);

			/**
			* \brief Metoda pobieraj�ca dane nast�pnego stanu.
			*
			* Metoda pobieraj�ca dane nast�pnego stanu.
			* \param[out] stan - Referencja do obiektu gdzie zostan� zapisane dane.
			* \return Zwracana jest warto�c true, je�eli nast�pny stan jest poprawny. Warto�� false jest zwracana w przeciwnym wypadku.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			bool pobierzNastepnyStan(struct Stan_t& stan);

			/**
			* \brief Metoda ustawiaj�ca nowy stan nast�pny.
			*
			* Metoda ustawia nowy stan nast�pny dla aktualnego zdarzenia.
			* \param[in] id - Identyfikator nowego stanu.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			void ustawNowyStanNastepny(const STyp::Identyfikator& id);

			/**
			* \brief Metoda ustawiaj�ca nowy numer dodatkowy.
			*
			* Metoda ustawia nowy numer dodatkowy dla aktualnego zdarzenia.
			* \param[in] numer - Nowy numer dodatkowy.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			void ustawNowyNumerNastepny(int numer);
			
		private:
			struct Zdarzenie_t zdarzenie_; /// Informacje o zdarzeniu.
			Zdarzenie* komunikat_ = nullptr; /// Wska�nik do obiektu zdarzenia.
			bool poprawne_zdarzenie_; /// Atrybut informuje czy stan poprzedni jest poprawny merytorycznie.

			/**
			* \brief Metoda ustawiaj�ca zdarzenie.
			*
			* Metoda ustawia zdarzenie.
			* \param[in] zdarzenie - Nowe zdarzenie.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			void ustawZdarzenie(const Zdarzenie& zdarzenie);

			struct Stan_t poprzedni_; /// Informacje o stanie poprzednim.
			bool poprawne_poprzedni_; /// Atrybut informuje czy stan poprzedni jest poprawny merytorycznie.

			/**
			* \brief Metoda ustawiaj�ca poprzedni stan.
			*
			* Metoda ustawia poprzedni stan.
			* \param[in] stan - Nowy poprzedni stan.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			void ustawPoprzedni(const Stan& stan);

			struct Stan_t aktualny_; /// Informacje o stanie aktualnym.
			bool poprawne_aktualny_; /// Atrybut informuje czy stan aktualny jest poprawny merytorycznie.

			/**
			* \brief Metoda ustawiaj�ca aktualny stan.
			*
			* Metoda ustawia aktualny stan.
			* \param[in] stan - Nowy aktualny stan.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			void ustawAktualny(const Stan& stan);

			struct Stan_t nastepny_; /// Informacje o stanie nast�pnym.
			bool poprawne_nastepny_; /// Atrybut informuje czy stan nast�pny jest poprawny merytorycznie.

			/**
			* \brief Metoda ustawiaj�ca nast�pny stan.
			*
			* Metoda ustawia nast�pny stan.
			* \param[in] stan - Nowy nast�pny stan.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			void ustawNastepny(const Stan& stan);
		};

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		~MaszynaStanow() = default;

		/**
		* \brief Metoda inicjuj�ca obiekt.
		*
		* Metoda Inicjalizuje obiekt klasy maszyny stan�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		void inicjalizuj();

		/**
		* \brief Metoda p�tli g��wnej.
		*
		* Metoda wykonuj�ca p�tl� g��wn� aplikacji. Wywo�uje metody zmieniaj�ce stan aplikacji oraz obs�uguj�ce zdarzenia.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void start();
		
		/**
		* \brief Metoda pobieraj�ca stos ekran�w oraz aktualny stan.
		*
		* Metoda pobiera stos ekran�w oraz aktualny stan aplikacji.
		* \param[out] stos - Stos z ekranami do wy�wietlenia.
		* \return Aktualny stan aplikacji.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		Stan pobierzStan(OknoGry::StosEkranow& stos) const;

		/**
		* \brief Metoda pobieraj�ca aktualny stan.
		*
		* Metoda pobiera aktualny stan aplikacji.
		* \return Aktualny stan aplikacji.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		Stan pobierzStan() const;

		/**
		* \brief Metoda wstawiaj�ca zdarzenie.
		*
		* Metoda wstawia zdarzenie, przekazane przez parametr, na koniec kolejki.
		* \param[in] komunikat - Zdarzenie wstawiane do kolejki.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void kolejkujZdarzenie(const Zdarzenie &komunikat);

		/**
		* \brief Metoda wstawiaj�ca zdarzenie.
		*
		* Metoda wstawia zdarzenie, przekazane przez parametr, na pocz�tek kolejki.
		* \param[in] komunikat - Zdarzenie wstawiane do kolejki.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void wstawZdarzenie(const Zdarzenie &komunikat);

		/**
		* \brief Metoda wstawiaj�ca ekran.
		*
		* Metoda wstawia ekran, przekazane przez parametr, na koniec kolejki.
		* \param[in] id - Identyfikator ekranu.
		* \return Zwracana jest warto�� true, je�eli operacja si� powiedzie. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool kolejkujEkran(int id);

		/**
		* \brief Metoda zdejmuj�ca ekran.
		*
		* Metoda zdejmuje ekran z ko�ca kolejki.
		* \return Zwracana jest warto�� true, je�eli operacja si� powiedzie. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool zdejmijEkran();
		
		/**
		* \brief Metoda czy�ci stos ekran�w.
		*
		* Metoda usuwa wszystkie ekrany ze stosu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void wyczyscKolejkeEkranow();

		/**
		* \brief Metoda inicjuj�ca zamykanie.
		*
		* Metoda inicjuje zamykanie aplikacji, informuj�c w�tek graficzny, aby si� zako�czy�.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void inicjujZamykanie();

		/**
		* \brief Metoda zlecaj�ca zadanie.
		*
		* Metoda zleca wykonanie zadania puli w�tk�w.
		* \param[in] zadanie - Zadanie do wykonania.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void dodajZadanie(Zadanie& zadanie);

		StanDlaSkryptu stanDlaSkryptu_; /// Stan aplikacji dla skrypt�w.

		/**
		* \brief Metoda pobiera obiekt zarz�dzaj�cy GUI.
		*
		* Metoda pobiera obiekt, kt�ry zarz�dza ca�ym GUI.
		* \return Referencja do obiektu zarz�dzaj�cym GUI.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		OknoGry& pobierzOknoGry();

	private:

		OknoGry watekGraficzny_; /// Obiekt obs�uguj�cy interfejs u�ytkownika.

		std::map<STyp::Identyfikator, std::shared_ptr<StanInfo> > wszystkieStany_; /// Lista wszystkich stan�w.
		STyp::Identyfikator idStanuPoczatkowy_; /// Stan pocz�tkowy aplikacji.

		Stan stan_; /// Aktualny stan aplikacji.
		OknoGry::StosEkranow stosEkranow_; /// Stos ekran�w.
		mutable std::recursive_mutex mutexStanu_; /// Mutex wy�aczno�ci dost�pu do stanu.

		Stan stanNastepny_; /// Nast�pny stan aplikacji.

		std::list<Zdarzenie> kolejkaZdarzen_; /// Kolejka zdarze�.
		mutable std::mutex mutexZdarzen_; /// Mutex wy�aczno�ci dost�pu do kolejki zdarze�.
		
		std::atomic_bool wlaczone; /// Atrybut infomuj�cy o poprawnym zainicjalizowaniu w�tku graficznego oraz informuj�cy o dzia�aniu p�tli g��wnej aplikacji.

		MenadzerWatkow pulaWatkow_; /// Obiekt zarz�dzaj�cy pul� w�tk�w.

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		MaszynaStanow();

		/**
		* \brief Metoda sprawdzaj�ca sp�jno�� wczytanych stan�w.
		*
		* Metoda sprawdza czy wczytane staney s� sp�jne. Por�wnuje liste stan�w z odwo�aniami do stan�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 02-10-2014
		*/
		void walidujStany() const;

		/**
		* \brief Metoda obs�uguj�ca kolejk� zdarze�.
		*
		* Metoda obs�uguje kolejk� zdarze�.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void obslugaZdarzenia();

		/**
		* \brief Metoda wy�wietlaj�ca komunikat log�w.
		*
		* Metoda s�u�y do wy�wietlania komunikat�w log�w na ustawionym wid�ecie, kt�ry jest do tego przenaczony.
		* \param[in] typ - Typ komunikatu loguj�ce.
		* \param[in] komunikat - Komunikat do wy�wietlenia.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void dodajKomunikatLogow(SLog::Log::TypLogow typ, const std::string& komunikat);

		/**
		* \brief Metoda obs�uguj�ca przej��ia mi�dzy stanami.
		*
		* Metoda obs�uguje przej�cia mi�dzy stanami.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void przejdzDoNastepnegoStanu();

		/**
		* \brief Metoda pobiera zdarzenie.
		*
		* Metoda pobiera zdarzenie z kolejki.
		* \param[out] komunikat - Zdarzenie oczekuj�ce w kolejce.
		* \return Zwracana jest warto�� true, je�eli pobrano zdarzenie z kolejki. Zwracana jest warto�� false, je�eli kolejka jest pusta.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool pobierzKomunikat(Zdarzenie &komunikat);

		/**
		* \brief Metoda pobiera opis zdarzenia.
		*
		* Metoda pobiera opis zdarzenia z listy wszystkich opis�w zdarze� wczytanych do aplikacji.
		* \param[in] id - Identyfikator stanu.
		* \return Wska�nik na opis zdarzenia lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr<StanInfo> pobierzOpisStanu(const STyp::Identyfikator& id) const;

		/**
		* \brief Metoda ustawia stan.
		*
		* Metoda zmiana aktualny stan na ten przekazany przez parametr.
		* \param[in] stan - Nowy stan aplikacji.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void ustawNastepnyStan(Stan& stan);

	};
};
