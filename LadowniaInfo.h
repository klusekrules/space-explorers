#pragma once
#include "FuncTransf\ZmianaInterfejs.h"
#include "Info.h"
#include "Ladownia.h"
#include "WyjatekParseraXML.h"
#include "PodstawoweParametry.h"

/**
* \brief Klasa opisuj�ca �adownie statku.
* 
* Klasa zawiera podstawowe informacje o �adownii statku.
* \author Daniel Wojdak
* \version 1
* \date 24-07-2013
*/
class LadowniaInfo :
	public Info,
	virtual public LoggerInterface
{
public:

	/**
	* \brief Konstruktor.
	*
	* \param[in] maksymalnaObjetosc - Podstatwowa maksymlana obiej�to�� �adowni.
	* \param[in] info - Obiekt opisuj�cy.
	*/
	LadowniaInfo( const Objetosc& maksymalnaObjetosc, const Info& info ) throw();

	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	explicit LadowniaInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Konstruktor kopiuj�cy.
	* 
	* \param[in] obiekt - Obiekt �r�d�owy.
	*/
	LadowniaInfo( const LadowniaInfo& obiekt );

	/**
	* \brief Destruktor.
	*/
	virtual ~LadowniaInfo();

	/**
	* \brief Metoda wyliczaj�ca maksymaln� pojemno�� �adowni.
	*
	* Metoda wylicza obj�to�� wzgl�dem parametr�w podanych podczas wywo�ania.
	* \param[in] parametry - Wymagane parametry do wykonania oblicze�.
	* \return Maksymalna obj�to�� �adowni.
	*/
	Objetosc pobierzPojemnoscMaksymalna( const PodstawoweParametry& parametry ) const;
	
	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;
private:
	
	Objetosc pojemnoscMaksymalna_; /// Pojemno�� maksymalna.
	shared_ptr<ZmianaInterfejs> przyrostPojemnosciMaksymalnej_; /// Obiekt wyliczaj�cy zmian� pojemno�ci maksymalnej.
};
