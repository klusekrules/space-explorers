#pragma once
#include "ObiektBazowyInfo.h"
#include "Technologia.h"

/**
* \brief Klasa opisowa technologii.
*
* Klasa opisowa technologii.
* \author Daniel Wojdak
* \version 1
* \date 25-07-2013
*/
class TechnologiaInfo : 
	public ObiektBazowyInfo,
	virtual public LoggerInterface
{
public:
	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit TechnologiaInfo( tinyxml2::XMLElement* wezel );
	
	/**
	* \brief Destruktor.
	*/
	virtual ~TechnologiaInfo();

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu dla podanej planety.
	* \param[in] ilosc - nieu¿ywana
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Metoda zwraca wskaŸnika na obiekt.
	*/
	Technologia* tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const override;

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu dla podanej planety.
	* \param[in] ilosc - nieu¿ywana
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Metoda zwraca wskaŸnika na obiekt.
	*/
	Technologia* tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety, const Poziom& poziom ) const override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis()const override;
private:

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
	*
	*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
	* \param[in] gra - Referencja do obiektu gry.
	* \param[in] planeta - Referencja do obiektu planety
	* \param[in] ilosc - Iloœæ tworzonych obiektów.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
	*/
	bool tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc, const Poziom& poziom ) const override;
};
