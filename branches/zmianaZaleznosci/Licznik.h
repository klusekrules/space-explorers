#pragma once
#include "Bazowa.h"
#include "Ilosc.h"

/**
* \brief Klasa reprezentuj¹ca licznik.
*
* Klasa s³u¿¹ca do generowania unikalnych identyfikatorów dla planet, flot itp.
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
	* Konstruktor tworzy obiekt na podstawie identyfikatora i wartoœci licznika.
	* \param[in] identyfikator - Identyfikator licznika.
	* \param[in] wartoscPoczatkowa - Wartoœæ pocz¹tkowa licznika.
	*/
	Licznik( const Identyfikator& identyfikator, const Ilosc& wartoscPoczatkowa);

	/**
	* \brief Konstruktor.
	*
	* Konstruktor tworzy obiekt na podstawie identyfikatora. Wartoœc licznika ustawiona jest na 0.
	* \param[in] identyfikator - Identyfikator licznika.
	*/
	explicit Licznik( const Identyfikator& identyfikator );

	/**
	* \brief Konstruktor domyœlny.
	*/
	Licznik();

	/**
	* \brief Metoda pobieraj¹ca wartoœæ.
	*
	* Metoda pobiera wartoœæ licznika a nastêpnie inkrementuje licznik.
	* \return Wartoœæ licznika z przed inkrementacji.
	*/
	Ilosc operator()();

	/**
	* \brief Metoda pobieraj¹ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca wartoœæ licznika.
	*/
	Ilosc pobierzWartosc()const;

	/**
	* \brief Metoda resetuj¹ca obiekt.
	*
	* Metoda ustawia wartoœæ domyœln¹ atrybutu obiektu.
	* \warning Wartoœæ domyœlana atrybutu jest równa 0.
	*/
	void resetujWartosc();

	/**
	* \brief Metoda ustawiaj¹ca atrybut.
	*
	* Metoda ustawiaj¹ca atrybut obiektu.
	* \param[in] wartosc - Nowa wartoœæ licznika.
	*/
	void ustawWartosc( const Ilosc& wartosc );

	/**
	* \brief Metoda zapisuj¹ca.
	*
	* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
	* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
	* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( tinyxml2::XMLElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj¹ca.
	*
	* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
	* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
	* \warning Metoda nie modyfikuje wêz³a.
	* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
	*/
	bool odczytaj( tinyxml2::XMLElement* wezel ) override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	std::string napis() const override;

private:
	Ilosc wartoscLicznika_;/// Wartoœæ licznika.
};
