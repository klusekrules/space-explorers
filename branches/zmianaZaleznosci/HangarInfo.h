#pragma once
#include "Info.h"
#include "Hangar.h"
#include "Objetosc.h"

class Statek;

/**
* \brief Klasa opisowa obiektu hangaru.
*
* Klasa opisowa obiektu hangaru.
*/
class HangarInfo:
	public Info,
	virtual public LoggerInterface
{
public:
	/**
	* \brief Konstruktor.
	*
	* \param[in] maksymalnaObjetosc - Podstatwowa maksymlana obiej�to�� hangaru.
	* \param[in] info - Obiekt opisuj�cy.
	*/
	HangarInfo( const Objetosc& maksymalnaObjetosc, const Info& info ) throw();

	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	explicit HangarInfo( tinyxml2::XMLElement* wezel );

	/**
	* \brief Konstruktor kopiuj�cy.
	* 
	* \param[in] obiekt - Obiekt �r�d�owy.
	*/
	HangarInfo( const HangarInfo& obiekt );

	/**
	* \brief Destruktor.
	*/
	virtual ~HangarInfo(void);
	
	/**
	* \brief Metoda pobieraj�ca maksymaln� obj�to�� przewo�onych statk�w w hangarze.
	*
	* Metoda wylicza ile statk�w mo�e zmie�cici� si� w hangarze.
	* \param[in] parametry - Referencja do podstawowych parametr�w obiektu dla kt�rego wyliczany jest atrybut.
	* \return Maksymalna obj�to�� statk�w znajduj�cych si� w hangarze.
	*/
	Objetosc pobierzMaksymalnaIloscPrzewozonychStatkow( const PodstawoweParametry& parametry ) const;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;

private:
	Objetosc pojemnoscMaksymalna_; /// Maksymalna obj�to�� przewo�onych statk�w
	shared_ptr<ZmianaInterfejs> przyrostPojemnosciMaksymalnej_; /// Sprzytny wska�nik na obiekt wyliczaj�cy zmian� maksymalnej obj�to�ci przewo�onych statk�w.

};

