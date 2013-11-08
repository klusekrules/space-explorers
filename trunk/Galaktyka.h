#pragma once
#include "Bazowa.h"
#include "UkladSloneczny.h"
#include <unordered_map>

/**
* \brief Klasa reprezezntuj�ca galaktyk�.
*
* Klasa reprezentuje galaktyk�. Przechowuje informacje o przynale�nyc uk�adach. 
* \note Klasa nie jest u�ywna.
* \author Daniel Wojdak
* \version 1
* \date 18-10-2013
*/
class Galaktyka :
	virtual public LoggerInterface,
	public Serializacja,
	public Bazowa
{
	friend class ZarzadcaPamieci;
	friend class GeneratorUkladow;
public:
	typedef unordered_map< Identyfikator, shared_ptr<UkladSloneczny>, IdTypeHash > UkladySloneczne; /// Typ listy uk�ad�w s�onecznych.

	/**
	* \brief Konstruktor.
	*
	* \param[in] identyfikator - Identyfikator galaktyki.
	*/
	Galaktyka(const Identyfikator& identyfikator);

	/**
	* \brief Destruktor.
	*/
	virtual ~Galaktyka();

	/**
	* \brief Metoda pobieraj�ca uk�ad.
	*
	* Metoda zwracaj�ca uk�ad o podanym identyfikatorze.
	* \param[in] identyfikator - Numer identyfikuj�cy uk�ad.
	* \return Wska�nik na uklad s�oneczny lub nullptr je�eli nie znaleziono uk�adu.
	*/
	shared_ptr<UkladSloneczny> pobierzUklad( const Identyfikator& identyfikator ) const;

	/**
	* \brief Metoda dodaj�ca ukad do listy.
	*
	* Metoda dodaje do listy uk�ad przekazany jako wska�nik.
	* \param[in] uklad - wskaznik na uklad.
	* \return true je�eli uda si� doda� uk�ad, false w przeciwnym wypadku.
	*/
	bool dodajUklad( shared_ptr<UkladSloneczny> uklad );

	/**
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
	* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( TiXmlElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	* \warning Metoda nie modyfikuje w�z�a.
	* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
	*/
	bool odczytaj( TiXmlElement* wezel ) override;

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	std::string napis() const override;

private:

	int iloscUkladow_; /// Liczba uk�ad�w przynale�nych do galaktyki

	UkladySloneczne uklady_; /// Lista uk�ad�w.
};
