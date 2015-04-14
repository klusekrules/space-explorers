#pragma once
#include "Info.h"
#include "Hangar.h"
#include "Zmiana\ZmianaInterfejs.h"

namespace SpEx{
	/**
	* \brief Klasa opisowa obiektu hangaru.
	*
	* Klasa opisowa obiektu hangaru.
	* \author Daniel Wojdak
	* \version 2
	* \date 11-03-2014
	*/
	class HangarInfo :
		virtual public SLog::LoggerInterface
	{
	public:
		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] maksymalnaObjetosc - Podstatwowa maksymlana obiej�to�� hangaru.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		HangarInfo(const STyp::Powierzchnia& maksymalnaObjetosc);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		explicit HangarInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* Konstruktor kopiuj�cy.
		* \param[in] obiekt - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		HangarInfo(const HangarInfo& obiekt);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~HangarInfo() = default;

		/**
		* \brief Metoda pobieraj�ca maksymaln� obj�to�� przewo�onych statk�w w hangarze.
		*
		* Metoda wylicza ile statk�w mo�e zmie�cici� si� w hangarze.
		* \param[in] parametry - Referencja do podstawowych parametr�w obiektu dla kt�rego wyliczany jest atrybut.
		* \return Maksymalna obj�to�� statk�w znajduj�cych si� w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Powierzchnia pobierzMaksymalnaIloscPrzewozonychStatkow(const PodstawoweParametry& parametry) const;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

	private:
		STyp::Powierzchnia pojemnoscMaksymalna_; /// Maksymalna obj�to�� przewo�onych statk�w
		std::shared_ptr<SZmi::ZmianaInterfejs> przyrostPojemnosciMaksymalnej_; /// Sprzytny wska�nik na obiekt wyliczaj�cy zmian� maksymalnej obj�to�ci przewo�onych statk�w.
	};
}
