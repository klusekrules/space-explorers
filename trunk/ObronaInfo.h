#pragma once
#include "ObiektInfo.h"
#include "JednostkaAtakujacaInfo.h"
#include "Obrona.h"

/**
* \brief Klasa opisowa dla obrony
*
* Klasa gromadzi wszytkie niezbêdne klasy bazowe dla obiektu biznesowego typu obrona.
* \author Daniel Wojdak
* \version 1
* \date 29-08-2013
*/
class ObronaInfo:	
	public ObiektInfo,
	public JednostkaAtakujacaInfo,
	virtual public LoggerInterface
{
public:
	/**
	* \brief Konstruktor.
	* \param[in] obiektInfo - Referencja do obiektu opisujacego.
	* \param[in] jednostkaLatajacaInfo - Referencja do obiektu opisujacego.
	* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisujacego.
	* \param[in] ladowniaInfo - Referencja do obiektu opisujacego.
	* \param[in] hangarInfo - Referencja do obiektu opisuj¹cego.
	*/
	ObronaInfo(	const ObiektInfo& obiektInfo , const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo ) throw();

	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit ObronaInfo( TiXmlElement* wezel );
	
	/**
	* \brief Destruktor.
	*/
	virtual ~ObronaInfo();

	/**
	* Metoda zwracaj¹ca Identyfikator obiektu.
	* \return Identyfikator obiektu.
	*/
	const Identyfikator& pobierzIdentyfikator() const;

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu dla podanej planety.
	* \param[in] ilosc - iloœæ obiektów.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Metoda zwraca wskaŸnika na obiekt.
	*/
	Obrona* tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const override;

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
	bool tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc ) const override;
};

