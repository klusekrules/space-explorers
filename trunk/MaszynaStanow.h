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
	* \brief Klasa maszyny stanów.
	*
	* Klasa obs³ugujê zdarzenia oraz zarz¹dza stanami. W metodzie tej klasy jest zaimplementowana g³ówna pêtla z obs³ug¹ zdarzeñ.
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
		* \brief Klasa stanu dla skryptów.
		*
		* Klasa stanu dla skryptów, u³awiaj¹ca przepisywanie informacji oraz zabezpiecza przez niekontrolowan¹ zmian¹.
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
			* \brief Metoda pobieraj¹ca dane zdarzenia.
			*
			* Metoda pobieraj¹ca dane zdarzenia.
			* \param[out] zdarzenie - Referencja do obiektu gdzie zostan¹ zapisane dane.
			* \return Zwracana jest wartoœc true, je¿eli zdarzenie jest poprawne. Wartoœæ false jest zwracana w przeciwnym wypadku.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			bool pobierzZdarzenie(struct Zdarzenie_t& zdarzenie);

			/**
			* \brief Metoda pobieraj¹ca dane poprzedniego stanu.
			*
			* Metoda pobieraj¹ca dane poprzedniego stanu.
			* \param[out] stan - Referencja do obiektu gdzie zostan¹ zapisane dane.
			* \return Zwracana jest wartoœc true, je¿eli poprzedni stan jest poprawny. Wartoœæ false jest zwracana w przeciwnym wypadku.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			bool pobierzPoprzedniStan(struct Stan_t& stan);

			/**
			* \brief Metoda pobieraj¹ca dane aktualnego stanu.
			*
			* Metoda pobieraj¹ca dane aktualnego stanu.
			* \param[out] stan - Referencja do obiektu gdzie zostan¹ zapisane dane.
			* \return Zwracana jest wartoœc true, je¿eli aktualny stan jest poprawny. Wartoœæ false jest zwracana w przeciwnym wypadku.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			bool pobierzAktualnyStan(struct Stan_t& stan);

			/**
			* \brief Metoda pobieraj¹ca dane nastêpnego stanu.
			*
			* Metoda pobieraj¹ca dane nastêpnego stanu.
			* \param[out] stan - Referencja do obiektu gdzie zostan¹ zapisane dane.
			* \return Zwracana jest wartoœc true, je¿eli nastêpny stan jest poprawny. Wartoœæ false jest zwracana w przeciwnym wypadku.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			bool pobierzNastepnyStan(struct Stan_t& stan);

			/**
			* \brief Metoda ustawiaj¹ca nowy stan nastêpny.
			*
			* Metoda ustawia nowy stan nastêpny dla aktualnego zdarzenia.
			* \param[in] id - Identyfikator nowego stanu.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			void ustawNowyStanNastepny(const STyp::Identyfikator& id);

			/**
			* \brief Metoda ustawiaj¹ca nowy numer dodatkowy.
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
			Zdarzenie* komunikat_ = nullptr; /// WskaŸnik do obiektu zdarzenia.
			bool poprawne_zdarzenie_; /// Atrybut informuje czy stan poprzedni jest poprawny merytorycznie.

			/**
			* \brief Metoda ustawiaj¹ca zdarzenie.
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
			* \brief Metoda ustawiaj¹ca poprzedni stan.
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
			* \brief Metoda ustawiaj¹ca aktualny stan.
			*
			* Metoda ustawia aktualny stan.
			* \param[in] stan - Nowy aktualny stan.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			void ustawAktualny(const Stan& stan);

			struct Stan_t nastepny_; /// Informacje o stanie nastêpnym.
			bool poprawne_nastepny_; /// Atrybut informuje czy stan nastêpny jest poprawny merytorycznie.

			/**
			* \brief Metoda ustawiaj¹ca nastêpny stan.
			*
			* Metoda ustawia nastêpny stan.
			* \param[in] stan - Nowy nastêpny stan.
			* \author Daniel Wojdak
			* \version 1
			* \date 09-07-2014
			*/
			void ustawNastepny(const Stan& stan);
		};

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		~MaszynaStanow() = default;

		/**
		* \brief Metoda inicjuj¹ca obiekt.
		*
		* Metoda Inicjalizuje obiekt klasy maszyny stanów.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		void inicjalizuj();

		/**
		* \brief Metoda pêtli g³ównej.
		*
		* Metoda wykonuj¹ca pêtlê g³ówn¹ aplikacji. Wywo³uje metody zmieniaj¹ce stan aplikacji oraz obs³uguj¹ce zdarzenia.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void start();
		
		/**
		* \brief Metoda pobieraj¹ca stos ekranów oraz aktualny stan.
		*
		* Metoda pobiera stos ekranów oraz aktualny stan aplikacji.
		* \param[out] stos - Stos z ekranami do wyœwietlenia.
		* \return Aktualny stan aplikacji.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		Stan pobierzStan(OknoGry::StosEkranow& stos) const;

		/**
		* \brief Metoda pobieraj¹ca aktualny stan.
		*
		* Metoda pobiera aktualny stan aplikacji.
		* \return Aktualny stan aplikacji.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		Stan pobierzStan() const;

		/**
		* \brief Metoda wstawiaj¹ca zdarzenie.
		*
		* Metoda wstawia zdarzenie, przekazane przez parametr, na koniec kolejki.
		* \param[in] komunikat - Zdarzenie wstawiane do kolejki.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void kolejkujZdarzenie(const Zdarzenie &komunikat);

		/**
		* \brief Metoda wstawiaj¹ca zdarzenie.
		*
		* Metoda wstawia zdarzenie, przekazane przez parametr, na pocz¹tek kolejki.
		* \param[in] komunikat - Zdarzenie wstawiane do kolejki.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void wstawZdarzenie(const Zdarzenie &komunikat);

		/**
		* \brief Metoda wstawiaj¹ca ekran.
		*
		* Metoda wstawia ekran, przekazane przez parametr, na koniec kolejki.
		* \param[in] id - Identyfikator ekranu.
		* \return Zwracana jest wartoœæ true, je¿eli operacja siê powiedzie. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool kolejkujEkran(int id);

		/**
		* \brief Metoda zdejmuj¹ca ekran.
		*
		* Metoda zdejmuje ekran z koñca kolejki.
		* \return Zwracana jest wartoœæ true, je¿eli operacja siê powiedzie. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool zdejmijEkran();
		
		/**
		* \brief Metoda czyœci stos ekranów.
		*
		* Metoda usuwa wszystkie ekrany ze stosu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void wyczyscKolejkeEkranow();

		/**
		* \brief Metoda inicjuj¹ca zamykanie.
		*
		* Metoda inicjuje zamykanie aplikacji, informuj¹c w¹tek graficzny, aby siê zakoñczy³.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void inicjujZamykanie();

		/**
		* \brief Metoda zlecaj¹ca zadanie.
		*
		* Metoda zleca wykonanie zadania puli w¹tków.
		* \param[in] zadanie - Zadanie do wykonania.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void dodajZadanie(Zadanie& zadanie);

		StanDlaSkryptu stanDlaSkryptu_; /// Stan aplikacji dla skryptów.

		/**
		* \brief Metoda pobiera obiekt zarz¹dzaj¹cy GUI.
		*
		* Metoda pobiera obiekt, który zarz¹dza ca³ym GUI.
		* \return Referencja do obiektu zarz¹dzaj¹cym GUI.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		OknoGry& pobierzOknoGry();

	private:

		OknoGry watekGraficzny_; /// Obiekt obs³uguj¹cy interfejs u¿ytkownika.

		std::map<STyp::Identyfikator, std::shared_ptr<StanInfo> > wszystkieStany_; /// Lista wszystkich stanów.
		STyp::Identyfikator idStanuPoczatkowy_; /// Stan pocz¹tkowy aplikacji.

		Stan stan_; /// Aktualny stan aplikacji.
		OknoGry::StosEkranow stosEkranow_; /// Stos ekranów.
		mutable std::recursive_mutex mutexStanu_; /// Mutex wy³acznoœci dostêpu do stanu.

		Stan stanNastepny_; /// Nastêpny stan aplikacji.

		std::list<Zdarzenie> kolejkaZdarzen_; /// Kolejka zdarzeñ.
		mutable std::mutex mutexZdarzen_; /// Mutex wy³acznoœci dostêpu do kolejki zdarzeñ.
		
		std::atomic_bool wlaczone; /// Atrybut infomuj¹cy o poprawnym zainicjalizowaniu w¹tku graficznego oraz informuj¹cy o dzia³aniu pêtli g³ównej aplikacji.

		MenadzerWatkow pulaWatkow_; /// Obiekt zarz¹dzaj¹cy pul¹ w¹tków.

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
		* \brief Metoda sprawdzaj¹ca spójnoœæ wczytanych stanów.
		*
		* Metoda sprawdza czy wczytane staney s¹ spójne. Porównuje liste stanów z odwo³aniami do stanów.
		* \author Daniel Wojdak
		* \version 1
		* \date 02-10-2014
		*/
		void walidujStany() const;

		/**
		* \brief Metoda obs³uguj¹ca kolejkê zdarzeñ.
		*
		* Metoda obs³uguje kolejkê zdarzeñ.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void obslugaZdarzenia();

		/**
		* \brief Metoda wyœwietlaj¹ca komunikat logów.
		*
		* Metoda s³u¿y do wyœwietlania komunikatów logów na ustawionym wid¿ecie, który jest do tego przenaczony.
		* \param[in] typ - Typ komunikatu loguj¹ce.
		* \param[in] komunikat - Komunikat do wyœwietlenia.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void dodajKomunikatLogow(SLog::Log::TypLogow typ, const std::string& komunikat);

		/**
		* \brief Metoda obs³uguj¹ca przejœæia miêdzy stanami.
		*
		* Metoda obs³uguje przejœcia miêdzy stanami.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		void przejdzDoNastepnegoStanu();

		/**
		* \brief Metoda pobiera zdarzenie.
		*
		* Metoda pobiera zdarzenie z kolejki.
		* \param[out] komunikat - Zdarzenie oczekuj¹ce w kolejce.
		* \return Zwracana jest wartoœæ true, je¿eli pobrano zdarzenie z kolejki. Zwracana jest wartoœæ false, je¿eli kolejka jest pusta.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool pobierzKomunikat(Zdarzenie &komunikat);

		/**
		* \brief Metoda pobiera opis zdarzenia.
		*
		* Metoda pobiera opis zdarzenia z listy wszystkich opisów zdarzeñ wczytanych do aplikacji.
		* \param[in] id - Identyfikator stanu.
		* \return WskaŸnik na opis zdarzenia lub nullptr.
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
