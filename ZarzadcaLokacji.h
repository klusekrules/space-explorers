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
	* Nie usuwa ich z czasem ¿ycia programu
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
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		ZarzadcaLokacji() = default;

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		~ZarzadcaLokacji() = default;

		/**
		* \brief Struktura pomocnicza przechowujaca wczytan¹ planetê.
		*
		* Struktura przechowuje planetê, je¿eli zosta³a wczytana oraz identyfikator uk³adu rodzica.
		* \author Daniel Wojdak
		* \version 2
		* \date 22-09-2014
		*/
		struct ObjPlaneta{
			STyp::Identyfikator idUkladu_; /// Identyfikator uk³adu. U¿ywane do wczytania odpowiedniego uk³adu do za³adowania planety.
			std::shared_ptr< Planeta > planeta_; /// wskaŸnik na planetê.
			std::atomic_bool wolna_; /// Informacja o przynaleznosci planety do gracza.
			std::once_flag& flaga_inicjalizacji_ukladu; /// Flaga inicjalizacji. 
		};

		/**
		* \brief Struktura pomocnicza przechowujaca wczytany uk³ad.
		*
		* Struktura przechowuje uk³ad, je¿eli zosta³ wczytany, identyfikator galaktyki rodzica oraz przynale¿ne planety.
		* \author Daniel Wojdak
		* \version 2
		* \date 22-09-2014
		*/
		struct ObjUklad{
			STyp::Identyfikator idGalaktyki_; /// Identyfikator Galaktyki. Aktualnie nie u¿ywany.
			std::shared_ptr< UkladSloneczny > uklad_; /// wskaŸnik do uk³adu.
			std::vector< STyp::Identyfikator > planety_; /// Lista przynaleznych planet. U¿ywane przy zapisie informacji do pliku.
			std::once_flag flaga_inicjalizacji_ukladu; /// Flaga inicjalizacji. 
		};

		/**
		* \brief Struktura pomocnicza przechowujaca wczytan¹ galaktykê.
		*
		* Struktura przechowuje galaktykê, je¿eli zosta³a wczytana oraz przynale¿ne uk³ady.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		struct ObjGalakatyka{
			std::shared_ptr< Galaktyka > galaktyka_; /// wskaŸnika na galaktykê. Nieu¿ywany.
			std::vector< STyp::Identyfikator > uklady_; /// Lista uk³adów przynaleznych. Potrzebna do zapisu danych.
		};

		typedef std::unordered_map< STyp::Identyfikator, ObjGalakatyka, STyp::IdTypeHash > Galaktyki; /// Typ listy wszystkich galaktyk.
		typedef std::unordered_map< STyp::Identyfikator, ObjUklad, STyp::IdTypeHash > UkladySloneczne; /// Typ listy wszystkich ukladów.
		typedef std::unordered_map< STyp::Identyfikator, ObjPlaneta, STyp::IdTypeHash > Planety; /// Typ listy wszystkich Planet.

		/**
		* \brief Metoda zwracaj¹ca wskaŸnik na planetê.
		*
		* Metoda zwraca wskaŸnik na planetê o wskazanym identyfikatorze.
		* Je¿eli planeta nie jest wczytana, metoda wczytuje ca³y uk³ad i zwraca planetê.
		* \param[in] identyfikator - Identyfikator planety.
		* \return WskaŸnik na planetê je¿eli planeta zosta³a znaleziona, nullptr w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr< Planeta > pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwracaj¹ca wskaŸnik na planetê.
		*
		* Metoda zwraca wskaŸnik na planetê o wskazanym identyfikatorze. Planeta jest oznaczana jako zajêta.
		* Je¿eli planeta nie jest wczytana, metoda wczytuje ca³y uk³ad i zwraca planetê.
		* \param[in] identyfikator - Identyfikator planety.
		* \return WskaŸnik na planetê je¿eli planeta zosta³a znaleziona, nullptr w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr< Planeta > pobierzIZarezerwujPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwracaj¹ca wskaŸnik na planetê.
		*
		* Metoda zwraca wskaŸnik na pierwsz¹ woln¹ planetê. Planeta jest oznaczana jako zajêta.
		* Je¿eli planeta nie jest wczytana, metoda wczytuje ca³y uk³ad i zwraca planetê.
		* \return WskaŸnik na planetê je¿eli planeta zosta³a znaleziona, nullptr w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr< Planeta > pobierzIZarezerwujPlanete();

		/**
		* \brief Metoda zmienia oznaczenie planety.
		*
		* Metoda zmienia oznaczenie planety jako woln¹.
		* \param[in] identyfikator - Identyfikator planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		void anulujRezerwacjePlanety(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczba galaktyk.
		*
		* Metoda zwraca liczba galaktyk zarz¹dzancyh przez zarz¹dcê pamiêci.
		* \return Liczba galaktyk.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		int pobierzIloscGalaktyk() const;

		/**
		* \brief Metoda generuje now¹ galaktykê.
		*
		* Metoda generuje now¹ galaktykê. Zapisuje dane uk³adów do pliku. Nie zapisuje struktury galaktyki,
		* oznacza to ¿e dopiero po zapisie stanu gry ca³oœæ informacji bêdzie zapisana do pliku.
		* \return true je¿eli siê powiedzie, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		bool generujNowaGalaktyke();

		/**
		* \brief Metoda czyœci dane zarz¹dcy.
		*
		* Metoda czyœci dane zarz¹dcy.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		void wyczyscDane();

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

		/**
		* \brief Metoda odczytuj¹ca.
		*
		* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
		* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
		* \warning Metoda nie modyfikuje wêz³a.
		* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* \brief Metoda inicjuj¹ca dane zarz¹dcy.
		*
		* Metoda pobiera dane i inicjuje obiekt zarz¹dcy na podstawie danych przekazanych przez parametry.
		* \param[in] ustawienia - Obiekt zawierajacy ustawienia apliakcji.
		* \param[in] stos - Funkcja tworz¹ca œlad stosu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		void zaladujUstawienia(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos);
		
		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 20-10-2014
		*/
		std::string napis() const override;

	private:
		/**
		* \brief Metoda wczytuje uk³ad z pliku do pamiêci.
		*
		* Metoda wczytuje uk³ad o podanym identyfikatorze z pliku w formacie {identyfikator}.xml
		* \param[in] identyfikator - Numer identyfikuj¹cy uk³ad s³oneczny.
		* \return true je¿eli uda siê wczytaæ, false w przeciwnym wypaku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		bool wczytajUkladSloneczny(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda wczytuje zapisuje do pliku.
		*
		* Metoda zapisuje uk³ad do pliku w formacie {identyfikator}.xml
		* \param[in] uklad - wskaŸnik na uk³ad s³oneczny.
		* \return true je¿eli uda siê zapisaæ, false w przeciwnym wypaku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		bool zapiszUkladSloneczny(std::shared_ptr<UkladSloneczny> uklad) const;

		/**
		* \brief Metoda generuje adres pliku uk³adu.
		*
		* Metoda generuje adres pliku do zapisu dok³adnych danych planet w uk³adzie o podanym w parametrze identyfikatorze.
		* \param[in] identyfikator - identyfikator uk³adu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::string generujNazwePlikuUkladuSlonecznego(const STyp::Identyfikator& identyfikator) const;

		GeneratorUkladow generator_; /// Obiekt generuj¹cy planety, uk³ady, galaktyki.
		Galaktyki galaktyki_; /// Lista galaktyk.
		UkladySloneczne ukladySloneczne_; /// Lista uk³adów.
		Planety planety_; /// Lista planet.
		std::string folderPlikuUkladu_; /// Adres folderu z plikami opisuj¹cymi planety.

	};
};
