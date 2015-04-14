#pragma once
#include "PodstawoweParametry.h"
#include "Zmiana\ZmianaInterfejs.h"
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

namespace SpEx{
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
		virtual public SLog::LoggerInterface
	{
	public:
		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] atak - podstawowny atak obiektu
		* \param[in] pancerz - podstawowy pancerz obiektu
		* \param[in] oslona - postawowa oslona obiektu
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaAtakujacaInfo(const STyp::Obrazenia& atak, const STyp::Obrazenia& pancerz, const STyp::Obrazenia& oslona) throw();

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		explicit JednostkaAtakujacaInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Konstruktor kopiuj¹cy.
		*
		* Konstruktor kopiuj¹cy.
		* \param[in] obiekt - Obiekt Ÿród³owy.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaAtakujacaInfo(const JednostkaAtakujacaInfo& obiekt);

		/**
		* \brief Domyslny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~JednostkaAtakujacaInfo() = default;

		/**
		* \brief Metoda zwraca wartoœæ obra¿eñ ataku
		*
		* Metoda zwraca obra¿enia jakie mo¿e zadaæ obiekt.
		* \param[in] parametry - Podstawowe parametry niezbêdne do wyliczenia obra¿eñ.
		* \return Wartoœæ obra¿eñ ataku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Obrazenia pobierzAtak(const PodstawoweParametry& parametry) const;

		/**
		* \brief Metoda zwraca wartoœæ obra¿eñ pancerza
		*
		* Metoda zwraca obra¿enia jakie mo¿e przyj¹æ pancerz.
		* \param[in] parametry - Podstawowe parametry niezbêdne do wyliczenia obra¿eñ.
		* \return Wartoœæ obra¿eñ pancerza.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Obrazenia pobierzPancerz(const PodstawoweParametry& parametry) const;

		/**
		* \brief Metoda zwraca wartoœæ obra¿eñ oslony
		*
		* Metoda zwraca obra¿enia jakie mo¿e przyj¹æ os³ona.
		* \param[in] parametry - Podstawowe parametry niezbêdne do wyliczenia obra¿eñ.
		* \return Wartoœæ obra¿eñ oslony.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Obrazenia pobierzOslone(const PodstawoweParametry& parametry) const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	private:
		STyp::Obrazenia atak_; /// Podstawowa wartoœæ ataku obiektu.
		std::shared_ptr<SZmi::ZmianaInterfejs> zmianaAtaku_; /// Procentowa zmiana ataku wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.

		STyp::Obrazenia pancerz_; /// Podstawowa wartoœæ pancerza obiektu.
		std::shared_ptr<SZmi::ZmianaInterfejs> zmianaPancerza_; /// Procentowa zmiana pancerza wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.

		STyp::Obrazenia oslona_; /// Podstawowa wartoœæ os³ony obiektu.
		std::shared_ptr<SZmi::ZmianaInterfejs> zmianaOslony_; /// Procentowa zmiana os³ony wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.
	};
}
