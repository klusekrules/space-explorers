#pragma once
#include "UkladSloneczny.h"
#include <unordered_map>

namespace SpEx{
	/**
	* \brief Klasa reprezezntuj¹ca galaktykê.
	*
	* Klasa reprezentuje galaktykê. Przechowuje informacje o przynale¿nyc uk³adach.
	* \note Klasa nie jest u¿ywna.
	* \author Daniel Wojdak
	* \version 1
	* \date 18-10-2013
	*/
	class Galaktyka :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
		friend class ZarzadcaPamieci;
		friend class GeneratorUkladow;
	public:
		typedef std::unordered_map< STyp::Identyfikator, std::shared_ptr<UkladSloneczny> > UkladySloneczne; /// Typ listy uk³adów s³onecznych.

		/**
		* \brief Konstruktor.
		*
		* \param[in] identyfikator - Identyfikator galaktyki.
		*/
		Galaktyka(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Destruktor.
		*/
		virtual ~Galaktyka() = default;

		const STyp::Identyfikator& pobierzIdentyfikator()const;

		/**
		* \brief Metoda pobieraj¹ca uk³ad.
		*
		* Metoda zwracaj¹ca uk³ad o podanym identyfikatorze.
		* \param[in] identyfikator - Numer identyfikuj¹cy uk³ad.
		* \return WskaŸnik na uklad s³oneczny lub nullptr je¿eli nie znaleziono uk³adu.
		*/
		std::shared_ptr<UkladSloneczny> pobierzUklad(const STyp::Identyfikator& identyfikator) const;

		/**
		* \brief Metoda dodaj¹ca ukad do listy.
		*
		* Metoda dodaje do listy uk³ad przekazany jako wskaŸnik.
		* \param[in] uklad - wskaznik na uklad.
		* \return true je¿eli uda siê dodaæ uk³ad, false w przeciwnym wypadku.
		*/
		bool dodajUklad(std::shared_ptr<UkladSloneczny> uklad);

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

		/**
		* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
		* \return Napis zawieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	private:

		int iloscUkladow_; /// Liczba uk³adów przynale¿nych do galaktyki

		STyp::Identyfikator identyfikator_;

		UkladySloneczne uklady_; /// Lista uk³adów.
	};
}
