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
	* Nie usuwa ich z czasem ¿ycia programu
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
		* \brief Struktura pomocnicza przechowujaca wczytan¹ planetê.
		*
		* Struktura przechowuje planetê, je¿eli zosta³a wczytana oraz identyfikator uk³adu rodzica.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		struct ObjPlaneta{
			STyp::Identyfikator idUkladu_; /// Identyfikator uk³adu. U¿ywane do wczytania odpowiedniego uk³adu do za³adowania planety.
			std::shared_ptr< Planeta > planeta_; /// wskaŸnik na planetê.
		};

		/**
		* \brief Struktura pomocnicza przechowujaca wczytany uk³ad.
		*
		* Struktura przechowuje uk³ad, je¿eli zosta³ wczytany, identyfikator galaktyki rodzica oraz przynale¿ne planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		struct ObjUklad{
			STyp::Identyfikator idGalaktyki_; /// Identyfikator Galaktyki. Aktualnie nie u¿ywany.
			std::shared_ptr< UkladSloneczny > uklad_; /// wskaŸnik do uk³adu.
			std::vector< STyp::Identyfikator > planety_; /// Lista przynaleznych planet. U¿ywane przy zapisie informacji do pliku.
		};

		/**
		* \brief Struktura pomocnicza przechowujaca wczytan¹ galaktykê.
		*
		* Struktura przechowuje galaktykê, je¿eli zosta³a wczytana oraz przynale¿ne uk³ady.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		struct ObjGalakatyka{
			std::shared_ptr< Galaktyka > galaktyka_; /// wskaŸnika na galaktykê. Nieu¿ywany.
			std::vector< STyp::Identyfikator > uklady_; /// Lista uk³adów przynaleznych. Potrzebna do zapisu danych.
		};

		typedef std::unordered_map< STyp::Identyfikator, ObjGalakatyka > Galaktyki; /// Typ listy wszystkich galaktyk.
		typedef std::unordered_map< STyp::Identyfikator, ObjUklad > UkladySloneczne; /// Typ listy wszystkich ukladów.
		typedef std::unordered_map< STyp::Identyfikator, ObjPlaneta > Planety; /// Typ listy wszystkich Planet.

		/**
		* \brief Konstruktor.
		*/
		ZarzadcaPamieci() = default;

		/**
		* \brief Metoda zwracaj¹ca wskaŸnik na planetê.
		*
		* Metoda zwraca wskaŸnik na planetê o wskazanym identyfikatorze.
		* Je¿eli planeta nie jest wczytana, metoda wczytuje ca³y uk³ad i zwraca planetê.
		* \param[in] identyfikator - Identyfikator planety.
		* \return WskaŸnik na planetê je¿eli planeta zosta³a znaleziona, nullptr w przeciwnym wypadku.
		*/
		std::shared_ptr< Planeta > pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczba galaktyk.
		*
		* Metoda zwraca liczba galaktyk zarz¹dzancyh przez zarz¹dcê pamiêci.
		* \return Liczba galaktyk.
		*/
		int pobierzIloscGalaktyk() const;

		/**
		* \brief Metoda generuje now¹ galaktykê.
		*
		* Metoda generuje now¹ galaktykê. Zapisuje dane uk³adów do pliku. Nie zapisuje struktury galaktyki,
		* oznacza to ¿e dopiero po zapisie stanu gry ca³oœæ informacji bêdzie zapisana do pliku.
		* \return true je¿eli siê powiedzie, false w przeciwnym wypadku.
		*/
		bool generujNowaGalaktyke();

		/**
		* \brief Destruktor.
		*/
		virtual ~ZarzadcaPamieci() = default;

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
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
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

	private:

		/**
		* \brief Metoda wczytuje uk³ad z pliku do pamiêci.
		*
		* Metoda wczytuje uk³ad o podanym identyfikatorze z pliku w formacie {identyfikator}.xml
		* \param[in] identyfikator - Numer identyfikuj¹cy uk³ad s³oneczny.
		* \return true je¿eli uda siê wczytaæ, false w przeciwnym wypaku.
		*/
		bool wczytajUkladSloneczny(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda wczytuje zapisuje do pliku.
		*
		* Metoda zapisuje uk³ad do pliku w formacie {identyfikator}.xml
		* \param[in] uklad - wskaŸnik na uk³ad s³oneczny.
		* \return true je¿eli uda siê zapisaæ, false w przeciwnym wypaku.
		*/
		bool zapiszUkladSloneczny(std::shared_ptr<UkladSloneczny> uklad) const;

		GeneratorUkladow generator_; /// Obiekt generuj¹cy lokacje.

		Galaktyki galaktyki_; /// Lista galaktyk.
		UkladySloneczne ukladySloneczne_; /// Lista uk³adów.
		Planety planety_; /// Lista planet.

	};
}
