#pragma once
#include "PodstawoweParametry.h"
#include "Zmiana\ZmianaInterfejs.h"
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

namespace SpEx{
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
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		explicit JednostkaAtakujacaInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* Konstruktor kopiuj�cy.
		* \param[in] obiekt - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaAtakujacaInfo(const JednostkaAtakujacaInfo& obiekt);

		/**
		* \brief Domyslny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~JednostkaAtakujacaInfo() = default;

		/**
		* \brief Metoda zwraca warto�� obra�e� ataku
		*
		* Metoda zwraca obra�enia jakie mo�e zada� obiekt.
		* \param[in] parametry - Podstawowe parametry niezb�dne do wyliczenia obra�e�.
		* \return Warto�� obra�e� ataku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Obrazenia pobierzAtak(const PodstawoweParametry& parametry) const;

		/**
		* \brief Metoda zwraca warto�� obra�e� pancerza
		*
		* Metoda zwraca obra�enia jakie mo�e przyj�� pancerz.
		* \param[in] parametry - Podstawowe parametry niezb�dne do wyliczenia obra�e�.
		* \return Warto�� obra�e� pancerza.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Obrazenia pobierzPancerz(const PodstawoweParametry& parametry) const;

		/**
		* \brief Metoda zwraca warto�� obra�e� oslony
		*
		* Metoda zwraca obra�enia jakie mo�e przyj�� os�ona.
		* \param[in] parametry - Podstawowe parametry niezb�dne do wyliczenia obra�e�.
		* \return Warto�� obra�e� oslony.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Obrazenia pobierzOslone(const PodstawoweParametry& parametry) const;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

	private:
		STyp::Obrazenia atak_; /// Podstawowa warto�� ataku obiektu.
		std::shared_ptr<SZmi::ZmianaInterfejs> zmianaAtaku_; /// Procentowa zmiana ataku wzgl�dem warto�ci podstawowej. Domy�lnie 1.0 - 100% warto�ci podstawowej.

		STyp::Obrazenia pancerz_; /// Podstawowa warto�� pancerza obiektu.
		std::shared_ptr<SZmi::ZmianaInterfejs> zmianaPancerza_; /// Procentowa zmiana pancerza wzgl�dem warto�ci podstawowej. Domy�lnie 1.0 - 100% warto�ci podstawowej.

		STyp::Obrazenia oslona_; /// Podstawowa warto�� os�ony obiektu.
		std::shared_ptr<SZmi::ZmianaInterfejs> zmianaOslony_; /// Procentowa zmiana os�ony wzgl�dem warto�ci podstawowej. Domy�lnie 1.0 - 100% warto�ci podstawowej.
	};
}
