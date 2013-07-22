#pragma once
#include "Logger\LoggerInterface.h"
#include "Identyfikator.h"
#include "Poziom.h"
#include "Serializacja.h"


/**
* \brief Klasa zawieraj¹ca podstawowe parametry.
*
* Przechowywane przez tê klasê atrybuty, s¹ podstawowymi parametrami
* potrzebnymi do wyliczenia wartoœci atrybutów obiektów pochodnych.
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
	* Podstawowy konstruktor obiektu. Ustawia poziom i identyfikator planety, do której przypisany jest dany obiekt.
	* \param[in] poziom - Poziom obiektu.
	* \param[in] identyfikatorPlanety - Identyfikator planety zawieraj¹cej obiekt.
	*/
	PodstawoweParametry( const Poziom& poziom, const Identyfikator& identyfikatorPlanety );

	/**
	* \brief Destruktor.
	*/
	virtual ~PodstawoweParametry(void);

	/**
	* \brief Metoda pobieraj¹ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca poziom obiektu.
	*/
	const Poziom& pobierzPoziom() const;

	/**
	* \brief Metoda ustawiaj¹ca atrybut.
	*
	* Metoda ustawiaj¹ca atrybut obiektu.
	* \param[in] poziom - Nowa wartoœæ poziomu obiektu.
	*/
	void ustawPoziom( const Poziom& poziom );

	/**
	* \brief Metoda pobieraj¹ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca identyfiaktor planety rodzica obiektu.
	*/
	const Identyfikator& pobierzIdentyfikatorPlanety() const;

	/**
	* \brief Metoda ustawiaj¹ca atrybut.
	*
	* Metoda ustawiaj¹ca atrybut obiektu.
	* \param[in] identyfikatorPlanety - Nowa wartoœæ identyfikatora planety rodzica obiektu.
	*/
	void ustawIdentyfikatorPlanety( const Identyfikator& identyfikatorPlanety );

	/**
	* \brief Metoda zwiêkszaj¹ca poziom obiektu.
	*
	* Metoda zwiêksza poziom obiektu o 1.
	*/
	void wzrostPoziomu();

	/**
	* \brief Metoda ustawia poziom i identyfikator planety rodzica.
	*
	* Metoda przypisuje wartoœci atrybutów z obiektu podanego jako parametr do obiektu docelowego.
	* \param[in] podstawoweParametry - Obiekt zawieraj¹cy atrybuty, które maj¹ zostaæ przypisane do obiektu docelowego.
	*/
	void ustawKontekst( const PodstawoweParametry& podstawoweParametry );

	/**
	* \brief Metoda zapisuj¹ca.
	*
	* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
	* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
	* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( TiXmlElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj¹ca.
	*
	* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
	* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
	* \warning Metoda nie modyfikuje wêz³a.
	* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
	*/
	bool odczytaj( TiXmlElement* wezel ) override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;

private:
	Poziom poziom_;/// Atrybut poziomu obiektu.
	Identyfikator identyfikatorPlanety_;/// Atrybut identyfikatora planety rodzica obiektu.
};
