#pragma once
#include "Bazowa.h"
#include "Ilosc.h"

/**
* \brief Klasa reprezentuj�ca licznik.
*
* Klasa s�u��ca do generowania unikalnych identyfikator�w dla planet, flot itp.
* \author Daniel Wojdak
* \version 1
* \date 22-07-2013
*/
class Licznik:
	public Bazowa,
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:

	/**
	* \brief Konstruktor.
	*
	* Konstruktor tworzy obiekt na podstawie identyfikatora i warto�ci licznika.
	* \param[in] identyfikator - Identyfikator licznika.
	* \param[in] wartoscPoczatkowa - Warto�� pocz�tkowa licznika.
	*/
	Licznik( const Identyfikator& identyfikator, const Ilosc& wartoscPoczatkowa);

	/**
	* \brief Konstruktor.
	*
	* Konstruktor tworzy obiekt na podstawie identyfikatora. Warto�c licznika ustawiona jest na 0.
	* \param[in] identyfikator - Identyfikator licznika.
	*/
	explicit Licznik( const Identyfikator& identyfikator );

	/**
	* \brief Konstruktor domy�lny.
	*/
	Licznik();

	/**
	* \brief Metoda pobieraj�ca warto��.
	*
	* Metoda pobiera warto�� licznika a nast�pnie inkrementuje licznik.
	* \return Warto�� licznika z przed inkrementacji.
	*/
	Ilosc operator()();

	/**
	* \brief Metoda pobieraj�ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca warto�� licznika.
	*/
	Ilosc pobierzWartosc()const;

	/**
	* \brief Metoda resetuj�ca obiekt.
	*
	* Metoda ustawia warto�� domy�ln� atrybutu obiektu.
	* \warning Warto�� domy�lana atrybutu jest r�wna 0.
	*/
	void resetujWartosc();

	/**
	* \brief Metoda ustawiaj�ca atrybut.
	*
	* Metoda ustawiaj�ca atrybut obiektu.
	* \param[in] wartosc - Nowa warto�� licznika.
	*/
	void ustawWartosc( const Ilosc& wartosc );

	/**
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
	* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( tinyxml2::XMLElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	* \warning Metoda nie modyfikuje w�z�a.
	* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
	*/
	bool odczytaj( tinyxml2::XMLElement* wezel ) override;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	std::string napis() const override;

private:
	Ilosc wartoscLicznika_;/// Warto�� licznika.
};
