#pragma once
#include <memory>
#include <unordered_map>
#include "Galaktyka.h"
#include "GeneratorUkladow.h"
#include <vector>

namespace SpEx{
	/**
	* \brief Klasa zarzadzajaca lokacjami
	*
	* Klasa zarzadza wczytanymi lokacjami. Wczytuje na tylko uzywane planety i uklady.
	* Nie usuwa ich z czasem �ycia programu
	* \todo Usuwanie nieuzywanych lokacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 18-10-2013
	*/
	class ZarzadcaPamieci :
		virtual public Serializacja
	{
	public:
		/**
		* \brief Struktura pomocnicza przechowujaca wczytan� planet�.
		*
		* Struktura przechowuje planet�, je�eli zosta�a wczytana oraz identyfikator uk�adu rodzica.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		struct ObjPlaneta{
			STyp::Identyfikator idUkladu_; /// Identyfikator uk�adu. U�ywane do wczytania odpowiedniego uk�adu do za�adowania planety.
			std::shared_ptr< Planeta > planeta_; /// wska�nik na planet�.
		};

		/**
		* \brief Struktura pomocnicza przechowujaca wczytany uk�ad.
		*
		* Struktura przechowuje uk�ad, je�eli zosta� wczytany, identyfikator galaktyki rodzica oraz przynale�ne planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		struct ObjUklad{
			STyp::Identyfikator idGalaktyki_; /// Identyfikator Galaktyki. Aktualnie nie u�ywany.
			std::shared_ptr< UkladSloneczny > uklad_; /// wska�nik do uk�adu.
			std::vector< STyp::Identyfikator > planety_; /// Lista przynaleznych planet. U�ywane przy zapisie informacji do pliku.
		};

		/**
		* \brief Struktura pomocnicza przechowujaca wczytan� galaktyk�.
		*
		* Struktura przechowuje galaktyk�, je�eli zosta�a wczytana oraz przynale�ne uk�ady.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		struct ObjGalakatyka{
			std::shared_ptr< Galaktyka > galaktyka_; /// wska�nika na galaktyk�. Nieu�ywany.
			std::vector< STyp::Identyfikator > uklady_; /// Lista uk�ad�w przynaleznych. Potrzebna do zapisu danych.
		};

		typedef std::unordered_map< STyp::Identyfikator, ObjGalakatyka > Galaktyki; /// Typ listy wszystkich galaktyk.
		typedef std::unordered_map< STyp::Identyfikator, ObjUklad > UkladySloneczne; /// Typ listy wszystkich uklad�w.
		typedef std::unordered_map< STyp::Identyfikator, ObjPlaneta > Planety; /// Typ listy wszystkich Planet.

		/**
		* \brief Konstruktor.
		*/
		ZarzadcaPamieci() = default;

		/**
		* \brief Metoda zwracaj�ca wska�nik na planet�.
		*
		* Metoda zwraca wska�nik na planet� o wskazanym identyfikatorze.
		* Je�eli planeta nie jest wczytana, metoda wczytuje ca�y uk�ad i zwraca planet�.
		* \param[in] identyfikator - Identyfikator planety.
		* \return Wska�nik na planet� je�eli planeta zosta�a znaleziona, nullptr w przeciwnym wypadku.
		*/
		std::shared_ptr< Planeta > pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczba galaktyk.
		*
		* Metoda zwraca liczba galaktyk zarz�dzancyh przez zarz�dc� pami�ci.
		* \return Liczba galaktyk.
		*/
		int pobierzIloscGalaktyk() const;

		/**
		* \brief Metoda generuje now� galaktyk�.
		*
		* Metoda generuje now� galaktyk�. Zapisuje dane uk�ad�w do pliku. Nie zapisuje struktury galaktyki,
		* oznacza to �e dopiero po zapisie stanu gry ca�o�� informacji b�dzie zapisana do pliku.
		* \return true je�eli si� powiedzie, false w przeciwnym wypadku.
		*/
		bool generujNowaGalaktyke();

		/**
		* \brief Destruktor.
		*/
		virtual ~ZarzadcaPamieci() = default;

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
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
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

	private:

		/**
		* \brief Metoda wczytuje uk�ad z pliku do pami�ci.
		*
		* Metoda wczytuje uk�ad o podanym identyfikatorze z pliku w formacie {identyfikator}.xml
		* \param[in] identyfikator - Numer identyfikuj�cy uk�ad s�oneczny.
		* \return true je�eli uda si� wczyta�, false w przeciwnym wypaku.
		*/
		bool wczytajUkladSloneczny(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda wczytuje zapisuje do pliku.
		*
		* Metoda zapisuje uk�ad do pliku w formacie {identyfikator}.xml
		* \param[in] uklad - wska�nik na uk�ad s�oneczny.
		* \return true je�eli uda si� zapisa�, false w przeciwnym wypaku.
		*/
		bool zapiszUkladSloneczny(std::shared_ptr<UkladSloneczny> uklad) const;

		GeneratorUkladow generator_; /// Obiekt generuj�cy lokacje.

		Galaktyki galaktyki_; /// Lista galaktyk.
		UkladySloneczne ukladySloneczne_; /// Lista uk�ad�w.
		Planety planety_; /// Lista planet.

	};
}
