#pragma once
#include "FuncTransf\ZmianaInterfejs.h"
#include "Info.h"
#include "Obrazenia.h"
#include "PodstawoweParametry.h"
#include "WyjatekParseraXML.h"

/* Wy�aczono losowe generowanie parametr�w.

std::mt19937& getGenerator()const;

std::mt19937& JednostkaAtakujacaInfo::getGenerator()const{
return gen;
}
mutable std::random_device rd;
mutable std::mt19937 gen;

const double JednostkaAtakujaca::srednia = 0.8;
const double JednostkaAtakujaca::odchylenie = 0.10;

(std::normal_distribution<>(srednia,odchylenie))(jednostkaAtakujacaInfo.getGenerator())
*/


/**
* \brief Klasa dodaj�ca atrybuty i metody jednostki atakuj�cej.
*
* Klasa zawiera niezb�dne atrybuty dla obiekt�w, kt�re b�d� s�u�y�y do walki.
* Rozsze�a interfejs o metody wyliczaj�ce atrybuty.
* \author Daniel Wojdak
* \version 1
* \date 24-07-2013
*/
class JednostkaAtakujacaInfo :
	public Info,
	virtual public LoggerInterface
{
public:
	/**
	* \brief Konstruktor.
	*
	* \param[in] info - referencja do obiektu opisowego.
	* \param[in] atak - podstawowny atak obiektu
	* \param[in] pancerz - podstawowy pancerz obiektu
	* \param[in] oslona - postawowa oslona obiektu
	*/
	JednostkaAtakujacaInfo(const Info& info, const Obrazenia& atak,const Obrazenia& pancerz, const Obrazenia& oslona ) throw();

	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	explicit JednostkaAtakujacaInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Konstruktor kopiuj�cy.
	* 
	* \param[in] obiekt - Obiekt �r�d�owy.
	*/
	JednostkaAtakujacaInfo( const JednostkaAtakujacaInfo& obiekt );

	/**
	* \brief Destruktor.
	*/
	virtual ~JednostkaAtakujacaInfo();

	/**
	* \brief Metoda zwraca warto�� obra�e� ataku
	*
	* Metoda zwraca obra�enia jakie mo�e zada� obiekt.
	* \param[in] parametry - Podstawowe parametry niezb�dne do wyliczenia obra�e�.
	* \return Warto�� obra�e� ataku.
	*/
	Obrazenia pobierzAtak(const PodstawoweParametry& parametry ) const;	

	/**
	* \brief Metoda zwraca warto�� obra�e� pancerza
	*
	* Metoda zwraca obra�enia jakie mo�e przyj�� pancerz.
	* \param[in] parametry - Podstawowe parametry niezb�dne do wyliczenia obra�e�.
	* \return Warto�� obra�e� pancerza.
	*/
	Obrazenia pobierzPancerz(const PodstawoweParametry& parametry ) const;	

	/**
	* \brief Metoda zwraca warto�� obra�e� oslony
	*
	* Metoda zwraca obra�enia jakie mo�e przyj�� os�ona.
	* \param[in] parametry - Podstawowe parametry niezb�dne do wyliczenia obra�e�.
	* \return Warto�� obra�e� oslony.
	*/
	Obrazenia pobierzOslone(const PodstawoweParametry& parametry ) const;

	/**
	* Przeci��ona funkcja generuj�ca tekstowy opis klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override;

private:
	Obrazenia atak_; /// Podstawowa warto�� ataku obiektu.
	shared_ptr<ZmianaInterfejs> zmianaAtaku_; /// Procentowa zmiana ataku wzgl�dem warto�ci podstawowej. Domy�lnie 1.0 - 100% warto�ci podstawowej.

	Obrazenia pancerz_; /// Podstawowa warto�� pancerza obiektu.
	shared_ptr<ZmianaInterfejs> zmianaPancerza_; /// Procentowa zmiana pancerza wzgl�dem warto�ci podstawowej. Domy�lnie 1.0 - 100% warto�ci podstawowej.

	Obrazenia oslona_; /// Podstawowa warto�� os�ony obiektu.
	shared_ptr<ZmianaInterfejs> zmianaOslony_; /// Procentowa zmiana os�ony wzgl�dem warto�ci podstawowej. Domy�lnie 1.0 - 100% warto�ci podstawowej.
};
