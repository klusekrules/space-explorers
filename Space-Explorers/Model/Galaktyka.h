#pragma once
#include "UkladSloneczny.h"
#include <unordered_map>

namespace SpEx{
	/**
	* \brief Klasa reprezezntuj�ca galaktyk�.
	*
	* Klasa reprezentuje galaktyk�. Przechowuje informacje o przynale�nyc uk�adach.
	* \note Klasa nie jest u�ywna.
	* \author Daniel Wojdak
	* \version 2
	* \date 14-07-2014
	*/
	class Galaktyka :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
		friend class ZarzadcaLokacji;
		friend class GeneratorUkladow;
	public:
		typedef std::unordered_map< STyp::Identyfikator, std::shared_ptr<UkladSloneczny>, STyp::IdTypeHash > UkladySloneczne; /// Typ listy uk�ad�w s�onecznych.

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] identyfikator - Identyfikator galaktyki.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		Galaktyka(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Galaktyka() = default;

		/**
		* \brief Metoda pobieraj�ca identyfikator.
		*
		* Metoda pobiera identyfikator obiektu.
		* \return Identyfikator obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		const STyp::Identyfikator& pobierzIdentyfikator()const;

		/**
		* \brief Metoda pobieraj�ca uk�ad.
		*
		* Metoda zwracaj�ca uk�ad o podanym identyfikatorze.
		* \param[in] identyfikator - Numer identyfikuj�cy uk�ad.
		* \return Wska�nik na uklad s�oneczny lub nullptr je�eli nie znaleziono uk�adu.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		std::shared_ptr<UkladSloneczny> pobierzUklad(const STyp::Identyfikator& identyfikator) const;

		/**
		* \brief Metoda dodaj�ca ukad do listy.
		*
		* Metoda dodaje do listy uk�ad przekazany jako wska�nik.
		* \param[in] uklad - wskaznik na uklad.
		* \return true je�eli uda si� doda� uk�ad, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		bool dodajUklad(std::shared_ptr<UkladSloneczny> uklad);

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
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
		* \date 18-10-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
		* \return Napis zawieraj�cy opis klasy.
		*/
		std::string napis() const override;

	private:

		int iloscUkladow_ = 0; /// Liczba uk�ad�w przynale�nych do galaktyki

		STyp::Identyfikator identyfikator_; /// Identyfikator galaktyki.

		UkladySloneczne uklady_; /// Lista uk�ad�w.
	};
}
