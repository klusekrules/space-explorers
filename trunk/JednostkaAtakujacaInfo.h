#pragma once
#include "FuncTransf\ZmianaInterfejs.h"
#include "Info.h"
#include "Obrazenia.h"
#include "PodstawoweParametry.h"
#include "WyjatekParseraXML.h"

/* Wy³aczono losowe generowanie parametrów.

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
* \brief Klasa dodaj¹ca atrybuty i metody jednostki atakuj¹cej.
*
* Klasa zawiera niezbêdne atrybuty dla obiektów, które bêd¹ s³u¿y³y do walki.
* Rozsze¿a interfejs o metody wyliczaj¹ce atrybuty.
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
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit JednostkaAtakujacaInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Konstruktor kopiuj¹cy.
	* 
	* \param[in] obiekt - Obiekt Ÿród³owy.
	*/
	JednostkaAtakujacaInfo( const JednostkaAtakujacaInfo& obiekt );

	/**
	* \brief Destruktor.
	*/
	virtual ~JednostkaAtakujacaInfo();

	/**
	* \brief Metoda zwraca wartoœæ obra¿eñ ataku
	*
	* Metoda zwraca obra¿enia jakie mo¿e zadaæ obiekt.
	* \param[in] parametry - Podstawowe parametry niezbêdne do wyliczenia obra¿eñ.
	* \return Wartoœæ obra¿eñ ataku.
	*/
	Obrazenia pobierzAtak(const PodstawoweParametry& parametry ) const;	

	/**
	* \brief Metoda zwraca wartoœæ obra¿eñ pancerza
	*
	* Metoda zwraca obra¿enia jakie mo¿e przyj¹æ pancerz.
	* \param[in] parametry - Podstawowe parametry niezbêdne do wyliczenia obra¿eñ.
	* \return Wartoœæ obra¿eñ pancerza.
	*/
	Obrazenia pobierzPancerz(const PodstawoweParametry& parametry ) const;	

	/**
	* \brief Metoda zwraca wartoœæ obra¿eñ oslony
	*
	* Metoda zwraca obra¿enia jakie mo¿e przyj¹æ os³ona.
	* \param[in] parametry - Podstawowe parametry niezbêdne do wyliczenia obra¿eñ.
	* \return Wartoœæ obra¿eñ oslony.
	*/
	Obrazenia pobierzOslone(const PodstawoweParametry& parametry ) const;

	/**
	* Przeci¹¿ona funkcja generuj¹ca tekstowy opis klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis() const override;

private:
	Obrazenia atak_; /// Podstawowa wartoœæ ataku obiektu.
	shared_ptr<ZmianaInterfejs> zmianaAtaku_; /// Procentowa zmiana ataku wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.

	Obrazenia pancerz_; /// Podstawowa wartoœæ pancerza obiektu.
	shared_ptr<ZmianaInterfejs> zmianaPancerza_; /// Procentowa zmiana pancerza wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.

	Obrazenia oslona_; /// Podstawowa wartoœæ os³ony obiektu.
	shared_ptr<ZmianaInterfejs> zmianaOslony_; /// Procentowa zmiana os³ony wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.
};
