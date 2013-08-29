#pragma once
#include "ObiektInfo.h"
#include "JednostkaAtakujacaInfo.h"
#include "Obrona.h"

/**
* \brief Klasa opisowa dla obrony
*
* Klasa gromadzi wszytkie niezb�dne klasy bazowe dla obiektu biznesowego typu obrona.
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
	* \param[in] hangarInfo - Referencja do obiektu opisuj�cego.
	*/
	ObronaInfo(	const ObiektInfo& obiektInfo , const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo ) throw();

	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	explicit ObronaInfo( TiXmlElement* wezel );
	
	/**
	* \brief Destruktor.
	*/
	virtual ~ObronaInfo();

	/**
	* Metoda zwracaj�ca Identyfikator obiektu.
	* \return Identyfikator obiektu.
	*/
	const Identyfikator& pobierzIdentyfikator() const;

	/**
	* \brief Metoda tworz�ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu dla podanej planety.
	* \param[in] ilosc - ilo�� obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Metoda zwraca wska�nika na obiekt.
	*/
	Obrona* tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const override;

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
	bool tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc ) const override;
};

