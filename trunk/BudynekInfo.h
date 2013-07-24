#pragma once
#include "Budynek.h"
#include "parser\ticpp.h"
#include "ObiektInfo.h"
#include "PodstawoweParametry.h"

/**
* \brief Klasa opisowa budynku.
*
* Klasa zawieraj¹ca komplet atrybutów i metod opisuj¹cych budynek.
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
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	BudynekInfo( TiXmlElement* wezel );

	/**
	* \brief Destruktor.
	*/
	virtual ~BudynekInfo();

	/**
	* \brief Metoda wyliczaj¹ca zapotrzebowanie.
	*
	* Metoda wylicza na podstawie przekazanych parametrów zapotrzebowanie budynku na zasoby.
	* \param[in] parametry - Parametry obiektu wymagane do wykonania obliczeñ.
	* \return Lista elementów zapotrzebowania obiektu.
	*/
	Wymagania::PrzetworzonaCena PobierzZapotrzebowanie( const PodstawoweParametry& parametry )const;

	/**
	* \brief Metoda wyliczaj¹ca produkcjê.
	*
	* Metoda wylicza na podstawie przekazanych parametrów produkcjê budynku.
	* \param[in] parametry - Parametry obiektu wymagane do wykonania obliczeñ.
	* \return Lista elementów produkcji obiektu.
	*/
	Wymagania::PrzetworzonaCena PobierzProdukcje( const PodstawoweParametry& parametry )const;

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu dla podanej planety.
	* \param[in] ilosc - nieu¿ywana
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Metoda zwraca wskaŸnika na obiekt.
	*/
	Budynek* tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis()const override;
protected:

	Wymagania::ListaCen zapotrzebowanie_; /// Lista bazowych elementów zapotrzebowania.
	Wymagania::ListaCen produkcja_; /// Lista bazowych elementów produkcji.

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
	bool tworz( const Gra& gra, Planeta& planeta, const Ilosc& ilosc ) const override;
};

