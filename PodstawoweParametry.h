#pragma once
#include "Logger\LoggerInterface.h"
#include "Identyfikator.h"
#include "Poziom.h"
#include "Serializacja.h"


/**
* \brief Klasa zawieraj�ca podstawowe parametry.
*
* Przechowywane przez t� klas� atrybuty, s� podstawowymi parametrami
* potrzebnymi do wyliczenia warto�ci atrybut�w obiekt�w pochodnych.
* \author Daniel Wojdak
* \version 1
* \date 22-07-2013
*/
class PodstawoweParametry :	
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:

	/**
	* \brief Konstruktor
	*
	* Podstawowy konstruktor obiektu. Ustawia poziom i identyfikator planety, do kt�rej przypisany jest dany obiekt.
	* \param[in] poziom - Poziom obiektu.
	* \param[in] identyfikatorPlanety - Identyfikator planety zawieraj�cej obiekt.
	*/
	PodstawoweParametry( const Poziom& poziom, const Identyfikator& identyfikatorPlanety );

	/**
	* \brief Destruktor.
	*/
	virtual ~PodstawoweParametry(void);

	/**
	* \brief Metoda pobieraj�ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca poziom obiektu.
	*/
	const Poziom& pobierzPoziom() const;

	/**
	* \brief Metoda ustawiaj�ca atrybut.
	*
	* Metoda ustawiaj�ca atrybut obiektu.
	* \param[in] poziom - Nowa warto�� poziomu obiektu.
	*/
	void ustawPoziom( const Poziom& poziom );

	/**
	* \brief Metoda pobieraj�ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca identyfiaktor planety rodzica obiektu.
	*/
	const Identyfikator& pobierzIdentyfikatorPlanety() const;

	/**
	* \brief Metoda ustawiaj�ca atrybut.
	*
	* Metoda ustawiaj�ca atrybut obiektu.
	* \param[in] identyfikatorPlanety - Nowa warto�� identyfikatora planety rodzica obiektu.
	*/
	void ustawIdentyfikatorPlanety( const Identyfikator& identyfikatorPlanety );

	/**
	* \brief Metoda zwi�kszaj�ca poziom obiektu.
	*
	* Metoda zwi�ksza poziom obiektu o 1.
	*/
	void wzrostPoziomu();

	/**
	* \brief Metoda ustawia poziom i identyfikator planety rodzica.
	*
	* Metoda przypisuje warto�ci atrybut�w z obiektu podanego jako parametr do obiektu docelowego.
	* \param[in] podstawoweParametry - Obiekt zawieraj�cy atrybuty, kt�re maj� zosta� przypisane do obiektu docelowego.
	*/
	void ustawKontekst( const PodstawoweParametry& podstawoweParametry );

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
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;

private:
	Poziom poziom_;/// Atrybut poziomu obiektu.
	Identyfikator identyfikatorPlanety_;/// Atrybut identyfikatora planety rodzica obiektu.
};
