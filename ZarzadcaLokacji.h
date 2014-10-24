#pragma once
#include "Galaktyka.h"
#include "GeneratorUkladow.h"
#include <functional>
#include "UstawieniaAplikacji.h"
#include <mutex>
#include <atomic>

namespace SpEx {
	/**
	* \brief Klasa zarzadzajaca lokacjami
	*
	* Klasa zarzadza wczytanymi lokacjami. Wczytuje na tylko uzywane planety i uklady.
	* Nie usuwa ich z czasem �ycia programu
	* \author Daniel Wojdak
	* \version 3
	* \date 20-10-2014
	* \todo Usuwanie nieuzywanych lokacji.
	*/
	class ZarzadcaLokacji :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:
		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		ZarzadcaLokacji() = default;

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		~ZarzadcaLokacji() = default;

		/**
		* \brief Struktura pomocnicza przechowujaca wczytan� planet�.
		*
		* Struktura przechowuje planet�, je�eli zosta�a wczytana oraz identyfikator uk�adu rodzica.
		* \author Daniel Wojdak
		* \version 2
		* \date 22-09-2014
		*/
		struct ObjPlaneta{
			STyp::Identyfikator idUkladu_; /// Identyfikator uk�adu. U�ywane do wczytania odpowiedniego uk�adu do za�adowania planety.
			std::shared_ptr< Planeta > planeta_; /// wska�nik na planet�.
			std::atomic_bool wolna_; /// Informacja o przynaleznosci planety do gracza.
			std::once_flag& flaga_inicjalizacji_ukladu; /// Flaga inicjalizacji. 
		};

		/**
		* \brief Struktura pomocnicza przechowujaca wczytany uk�ad.
		*
		* Struktura przechowuje uk�ad, je�eli zosta� wczytany, identyfikator galaktyki rodzica oraz przynale�ne planety.
		* \author Daniel Wojdak
		* \version 2
		* \date 22-09-2014
		*/
		struct ObjUklad{
			STyp::Identyfikator idGalaktyki_; /// Identyfikator Galaktyki. Aktualnie nie u�ywany.
			std::shared_ptr< UkladSloneczny > uklad_; /// wska�nik do uk�adu.
			std::vector< STyp::Identyfikator > planety_; /// Lista przynaleznych planet. U�ywane przy zapisie informacji do pliku.
			std::once_flag flaga_inicjalizacji_ukladu; /// Flaga inicjalizacji. 
		};

		/**
		* \brief Struktura pomocnicza przechowujaca wczytan� galaktyk�.
		*
		* Struktura przechowuje galaktyk�, je�eli zosta�a wczytana oraz przynale�ne uk�ady.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		struct ObjGalakatyka{
			std::shared_ptr< Galaktyka > galaktyka_; /// wska�nika na galaktyk�. Nieu�ywany.
			std::vector< STyp::Identyfikator > uklady_; /// Lista uk�ad�w przynaleznych. Potrzebna do zapisu danych.
		};

		typedef std::unordered_map< STyp::Identyfikator, ObjGalakatyka, STyp::IdTypeHash > Galaktyki; /// Typ listy wszystkich galaktyk.
		typedef std::unordered_map< STyp::Identyfikator, ObjUklad, STyp::IdTypeHash > UkladySloneczne; /// Typ listy wszystkich uklad�w.
		typedef std::unordered_map< STyp::Identyfikator, ObjPlaneta, STyp::IdTypeHash > Planety; /// Typ listy wszystkich Planet.

		/**
		* \brief Metoda zwracaj�ca wska�nik na planet�.
		*
		* Metoda zwraca wska�nik na planet� o wskazanym identyfikatorze.
		* Je�eli planeta nie jest wczytana, metoda wczytuje ca�y uk�ad i zwraca planet�.
		* \param[in] identyfikator - Identyfikator planety.
		* \return Wska�nik na planet� je�eli planeta zosta�a znaleziona, nullptr w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr< Planeta > pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwracaj�ca wska�nik na planet�.
		*
		* Metoda zwraca wska�nik na planet� o wskazanym identyfikatorze. Planeta jest oznaczana jako zaj�ta.
		* Je�eli planeta nie jest wczytana, metoda wczytuje ca�y uk�ad i zwraca planet�.
		* \param[in] identyfikator - Identyfikator planety.
		* \return Wska�nik na planet� je�eli planeta zosta�a znaleziona, nullptr w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr< Planeta > pobierzIZarezerwujPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwracaj�ca wska�nik na planet�.
		*
		* Metoda zwraca wska�nik na pierwsz� woln� planet�. Planeta jest oznaczana jako zaj�ta.
		* Je�eli planeta nie jest wczytana, metoda wczytuje ca�y uk�ad i zwraca planet�.
		* \return Wska�nik na planet� je�eli planeta zosta�a znaleziona, nullptr w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr< Planeta > pobierzIZarezerwujPlanete();

		/**
		* \brief Metoda zmienia oznaczenie planety.
		*
		* Metoda zmienia oznaczenie planety jako woln�.
		* \param[in] identyfikator - Identyfikator planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		void anulujRezerwacjePlanety(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczba galaktyk.
		*
		* Metoda zwraca liczba galaktyk zarz�dzancyh przez zarz�dc� pami�ci.
		* \return Liczba galaktyk.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		int pobierzIloscGalaktyk() const;

		/**
		* \brief Metoda generuje now� galaktyk�.
		*
		* Metoda generuje now� galaktyk�. Zapisuje dane uk�ad�w do pliku. Nie zapisuje struktury galaktyki,
		* oznacza to �e dopiero po zapisie stanu gry ca�o�� informacji b�dzie zapisana do pliku.
		* \return true je�eli si� powiedzie, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		bool generujNowaGalaktyke();

		/**
		* \brief Metoda czy�ci dane zarz�dcy.
		*
		* Metoda czy�ci dane zarz�dcy.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		void wyczyscDane();

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

		/**
		* \brief Metoda odczytuj�ca.
		*
		* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
		* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
		* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
		* \warning Metoda nie modyfikuje w�z�a.
		* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* \brief Metoda inicjuj�ca dane zarz�dcy.
		*
		* Metoda pobiera dane i inicjuje obiekt zarz�dcy na podstawie danych przekazanych przez parametry.
		* \param[in] ustawienia - Obiekt zawierajacy ustawienia apliakcji.
		* \param[in] stos - Funkcja tworz�ca �lad stosu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		void zaladujUstawienia(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos);
		
		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 20-10-2014
		*/
		std::string napis() const override;

	private:
		/**
		* \brief Metoda wczytuje uk�ad z pliku do pami�ci.
		*
		* Metoda wczytuje uk�ad o podanym identyfikatorze z pliku w formacie {identyfikator}.xml
		* \param[in] identyfikator - Numer identyfikuj�cy uk�ad s�oneczny.
		* \return true je�eli uda si� wczyta�, false w przeciwnym wypaku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		bool wczytajUkladSloneczny(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda wczytuje zapisuje do pliku.
		*
		* Metoda zapisuje uk�ad do pliku w formacie {identyfikator}.xml
		* \param[in] uklad - wska�nik na uk�ad s�oneczny.
		* \return true je�eli uda si� zapisa�, false w przeciwnym wypaku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		bool zapiszUkladSloneczny(std::shared_ptr<UkladSloneczny> uklad) const;

		/**
		* \brief Metoda generuje adres pliku uk�adu.
		*
		* Metoda generuje adres pliku do zapisu dok�adnych danych planet w uk�adzie o podanym w parametrze identyfikatorze.
		* \param[in] identyfikator - identyfikator uk�adu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::string generujNazwePlikuUkladuSlonecznego(const STyp::Identyfikator& identyfikator) const;

		GeneratorUkladow generator_; /// Obiekt generuj�cy planety, uk�ady, galaktyki.
		Galaktyki galaktyki_; /// Lista galaktyk.
		UkladySloneczne ukladySloneczne_; /// Lista uk�ad�w.
		Planety planety_; /// Lista planet.
		std::string folderPlikuUkladu_; /// Adres folderu z plikami opisuj�cymi planety.

	};
};
