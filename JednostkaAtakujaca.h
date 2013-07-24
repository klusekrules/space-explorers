#pragma once
#include "JednostkaAtakujacaInfo.h"
#include "Obrazenia.h"
#include "Fluktuacja.h"
#include "PodstawoweParametry.h"

/**
* \brief Klasa reprezentuj�ca jednostk� atakuj�c�.
*
* Klasa zawieraj�ca interfejs jednostki atakuj�cej, zawiera metody wyliczaj�ce obra�enia zadawane, 
* obra�enia otrzymywane oraz obra�enia odbijane.
* \author Daniel Wojdak
* \version 1
* \date 24-07-2013
*/
class JednostkaAtakujaca :
	virtual public PodstawoweParametry,
	virtual public LoggerInterface
{
public:	

	/**
	* \brief Konstruktor.
	*
	* \param[in] poziom - Poziom tworzonych obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisuj�cego.
	*/
	JednostkaAtakujaca( const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo );

	/**
	* \brief Konstruktor.
	*
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
	* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisuj�cego.
	*/
	JednostkaAtakujaca( const PodstawoweParametry& podstawoweParametry, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo );

	/**
	* \brief Destruktor.
	*/
	virtual ~JednostkaAtakujaca();

	/**
	* Metoda atak s�u�y do wyliczania obra�e� zadawanych przez obiekt.
	* \return Obra�enia zadane przez obiekt.
	*/
	virtual Obrazenia pobierzAtak() const;	

	/**
	* Metoda obliczaj�ca obra�enia mo�liwe do przyj�cia przez pancerz.
	* \return Obra�enia, kt�re mo�e przyj�� pancerz.
	*/
	virtual Obrazenia pobierzPancerz() const;

	/**
	* Metoda obliczaj�ca obra�enia mo�liwe do przyj�cia przez oslone.
	* \return Obra�enia, kt�re mo�e przyj�� os�ona.
	*/
	virtual Obrazenia pobierzOslone() const;

	/**
	* Przeci��ona funkcja generuj�ca tekstowy opis klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override;

protected:
	const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo_; /// Wska�nik na klas� opisuj�c�. Wymagany do poprawnego dzia�ania.
};
