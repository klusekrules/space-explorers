#pragma once
#include "Info.h"
#include "Poziom.h"

class ObiektBazowy;
class Planeta;

/**
* \brief Klasa bazowa obiektu opisuj�cego.
*
* Klasa bazowa dla obiektu opisuj�cego. Zawiera poziom domy�lny obiektu, rozsze�a interfejs o tworzenie egzemplarza obiektu.
* \author Daniel Wojdak
* \version 1
* \date 22-07-2013
*/
class ObiektBazowyInfo:
	public Info,
	virtual public LoggerInterface
{
	friend class Gra;
public:

	/**
	* \brief Konstruktor.
	* 
	* Podstawowy konstruktor obiektu.
	* \param[in] info - Referencja do klasy Info.
	* \param[in] poziom - Poziom domy�lny.
	*/
	ObiektBazowyInfo( const Info& info , const Poziom& poziom ) throw();

	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	explicit ObiektBazowyInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Metoda tworz�ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu o podanej ilo�ci i dla podanej planety.
	* \param[in] ilosc - Ilo�� tworzonych obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Metoda zwraca poziom domy�lny obiektu.
	*/
	virtual ObiektBazowy* tworzEgzemplarz( const Ilosc& ilosc , const Identyfikator& identyfikatorPlanety ) const;

	/**
	* \brief Metoda pobieraj�ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca poziom domy�lny obiektu.
	*/
	const Poziom& pobierzPoziom()const;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;

private:

	/**
	* \brief Metoda tworz�ca egzemplarz obiektu na planecie.
	*
	*  Metoda tworzy egzemplarz obiektu na planecie. U�ywana jest podczas wywo�ywania metody wybuduj w klasie Planeta.
	* \param[in] gra - Referencja do obiektu gry.
	* \param[in] planeta - Referencja do obiektu planety
	* \param[in] ilosc - Ilo�� tworzonych obiekt�w.
	* \return Metoda zwraca true je�eli tworzenie zako�czy si� sukcesem. Zwraca false w przeciwnym wypadku.
	*/
	virtual bool tworz( const Gra& gra , Planeta& planeta , const Ilosc& ilosc ) const;

	Poziom poziom_;/// Domy�lny poziom obiektu tworzonego na bazie opisu.
};
