#pragma once
#include "Budynek.h"
#include "parser\ticpp.h"
#include "ObiektInfo.h"
#include "PodstawoweParametry.h"

/**
* \brief Klasa opisowa budynku.
*
* Klasa zawieraj�ca komplet atrybut�w i metod opisuj�cych budynek.
* \author Daniel Wojdak
* \version 1
* \date 24-07-2013
*/
class BudynekInfo :
	public ObiektInfo,
	virtual public LoggerInterface
{
public:

	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	BudynekInfo( TiXmlElement* wezel );

	/**
	* \brief Destruktor.
	*/
	virtual ~BudynekInfo();

	/**
	* \brief Metoda wyliczaj�ca zapotrzebowanie.
	*
	* Metoda wylicza na podstawie przekazanych parametr�w zapotrzebowanie budynku na zasoby.
	* \param[in] parametry - Parametry obiektu wymagane do wykonania oblicze�.
	* \return Lista element�w zapotrzebowania obiektu.
	*/
	Wymagania::PrzetworzonaCena PobierzZapotrzebowanie( const PodstawoweParametry& parametry )const;

	/**
	* \brief Metoda wyliczaj�ca produkcj�.
	*
	* Metoda wylicza na podstawie przekazanych parametr�w produkcj� budynku.
	* \param[in] parametry - Parametry obiektu wymagane do wykonania oblicze�.
	* \return Lista element�w produkcji obiektu.
	*/
	Wymagania::PrzetworzonaCena PobierzProdukcje( const PodstawoweParametry& parametry )const;

	/**
	* \brief Metoda tworz�ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu dla podanej planety.
	* \param[in] ilosc - nieu�ywana
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Metoda zwraca wska�nika na obiekt.
	*/
	Budynek* tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const override;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis()const override;
protected:

	Wymagania::ListaCen zapotrzebowanie_; /// Lista bazowych element�w zapotrzebowania.
	Wymagania::ListaCen produkcja_; /// Lista bazowych element�w produkcji.

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
	bool tworz( const Gra& gra, Planeta& planeta, const Ilosc& ilosc ) const override;
};

