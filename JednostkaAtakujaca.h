#pragma once
#include "JednostkaAtakujacaInfo.h"
#include "Obrazenia.h"
#include "Fluktuacja.h"
#include "PodstawoweParametry.h"

/**
* \brief Klasa reprezentuj¹ca jednostkê atakuj¹c¹.
*
* Klasa zawieraj¹ca interfejs jednostki atakuj¹cej, zawiera metody wyliczaj¹ce obra¿enia zadawane, 
* obra¿enia otrzymywane oraz obra¿enia odbijane.
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
	* \param[in] poziom - Poziom tworzonych obiektów.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisuj¹cego.
	*/
	JednostkaAtakujaca( const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo );

	/**
	* \brief Konstruktor.
	*
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
	* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisuj¹cego.
	*/
	JednostkaAtakujaca( const PodstawoweParametry& podstawoweParametry, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo );

	/**
	* \brief Destruktor.
	*/
	virtual ~JednostkaAtakujaca();

	/**
	* Metoda atak s³u¿y do wyliczania obra¿eñ zadawanych przez obiekt.
	* \return Obra¿enia zadane przez obiekt.
	*/
	virtual Obrazenia pobierzAtak() const;	

	/**
	* Metoda obliczaj¹ca obra¿enia mo¿liwe do przyjêcia przez pancerz.
	* \return Obra¿enia, które mo¿e przyj¹æ pancerz.
	*/
	virtual Obrazenia pobierzPancerz() const;

	/**
	* Metoda obliczaj¹ca obra¿enia mo¿liwe do przyjêcia przez oslone.
	* \return Obra¿enia, które mo¿e przyj¹æ os³ona.
	*/
	virtual Obrazenia pobierzOslone() const;

	/**
	* Przeci¹¿ona funkcja generuj¹ca tekstowy opis klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis() const override;

protected:
	const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo_; /// WskaŸnik na klasê opisuj¹c¹. Wymagany do poprawnego dzia³ania.
};
