#pragma once
#include "FuncTransf\ZmianaInterfejs.h"
#include "Info.h"
#include "Ladownia.h"
#include "WyjatekParseraXML.h"
#include "PodstawoweParametry.h"

/**
* \brief Klasa opisuj¹ca ³adownie statku.
* 
* Klasa zawiera podstawowe informacje o ³adownii statku.
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
	* \param[in] maksymalnaObjetosc - Podstatwowa maksymlana obiejêtoœæ ³adowni.
	* \param[in] info - Obiekt opisuj¹cy.
	*/
	LadowniaInfo( const Objetosc& maksymalnaObjetosc, const Info& info ) throw();

	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit LadowniaInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Konstruktor kopiuj¹cy.
	* 
	* \param[in] obiekt - Obiekt Ÿród³owy.
	*/
	LadowniaInfo( const LadowniaInfo& obiekt );

	/**
	* \brief Destruktor.
	*/
	virtual ~LadowniaInfo();

	/**
	* \brief Metoda wyliczaj¹ca maksymaln¹ pojemnoœæ ³adowni.
	*
	* Metoda wylicza objêtoœæ wzglêdem parametrów podanych podczas wywo³ania.
	* \param[in] parametry - Wymagane parametry do wykonania obliczeñ.
	* \return Maksymalna objêtoœæ ³adowni.
	*/
	Objetosc pobierzPojemnoscMaksymalna( const PodstawoweParametry& parametry ) const;
	
	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;
private:
	
	Objetosc pojemnoscMaksymalna_; /// Pojemnoœæ maksymalna.
	shared_ptr<ZmianaInterfejs> przyrostPojemnosciMaksymalnej_; /// Obiekt wyliczaj¹cy zmianê pojemnoœci maksymalnej.
};
