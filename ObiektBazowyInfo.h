#pragma once
#include "Info.h"
#include "Poziom.h"

class ObiektBazowy;
class Planeta;

/**
* \brief Klasa bazowa obiektu opisuj¹cego.
*
* Klasa bazowa dla obiektu opisuj¹cego. Zawiera poziom domyœlny obiektu, rozsze¿a interfejs o tworzenie egzemplarza obiektu.
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
	* \param[in] poziom - Poziom domyœlny.
	*/
	ObiektBazowyInfo( const Info& info , const Poziom& poziom ) throw();

	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit ObiektBazowyInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu o podanej iloœci i dla podanej planety.
	* \param[in] ilosc - Iloœæ tworzonych obiektów.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Metoda zwraca poziom domyœlny obiektu.
	*/
	virtual ObiektBazowy* tworzEgzemplarz( const Ilosc& ilosc , const Identyfikator& identyfikatorPlanety ) const;

	/**
	* \brief Metoda pobieraj¹ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca poziom domyœlny obiektu.
	*/
	const Poziom& pobierzPoziom()const;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;

private:

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
	*
	*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
	* \param[in] gra - Referencja do obiektu gry.
	* \param[in] planeta - Referencja do obiektu planety
	* \param[in] ilosc - Iloœæ tworzonych obiektów.
	* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
	*/
	virtual bool tworz( const Gra& gra , Planeta& planeta , const Ilosc& ilosc ) const;

	Poziom poziom_;/// Domyœlny poziom obiektu tworzonego na bazie opisu.
};
