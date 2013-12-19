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
	* \param[in] maksymalnaObjetosc - Podstatwowa maksymlana obiejêtoœæ hangaru.
	* \param[in] info - Obiekt opisuj¹cy.
	*/
	HangarInfo( const Objetosc& maksymalnaObjetosc, const Info& info ) throw();

	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit HangarInfo( tinyxml2::XMLElement* wezel );

	/**
	* \brief Konstruktor kopiuj¹cy.
	* 
	* \param[in] obiekt - Obiekt Ÿród³owy.
	*/
	HangarInfo( const HangarInfo& obiekt );

	/**
	* \brief Destruktor.
	*/
	virtual ~HangarInfo(void);
	
	/**
	* \brief Metoda pobieraj¹ca maksymaln¹ objêtoœæ przewo¿onych statków w hangarze.
	*
	* Metoda wylicza ile statków mo¿e zmieœciciæ siê w hangarze.
	* \param[in] parametry - Referencja do podstawowych parametrów obiektu dla którego wyliczany jest atrybut.
	* \return Maksymalna objêtoœæ statków znajduj¹cych siê w hangarze.
	*/
	Objetosc pobierzMaksymalnaIloscPrzewozonychStatkow( const PodstawoweParametry& parametry ) const;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;

private:
	Objetosc pojemnoscMaksymalna_; /// Maksymalna objêtoœæ przewo¿onych statków
	shared_ptr<ZmianaInterfejs> przyrostPojemnosciMaksymalnej_; /// Sprzytny wskaŸnik na obiekt wyliczaj¹cy zmianê maksymalnej objêtoœci przewo¿onych statków.

};

