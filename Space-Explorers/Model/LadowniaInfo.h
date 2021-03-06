#pragma once
#include "Info.h"
#include "Ladownia.h"
#include "PodstawoweParametry.h"
namespace SpEx{
	/**
	* \brief Klasa opisuj�ca �adownie statku.
	*
	* Klasa zawiera podstawowe informacje o �adownii statku.
	* \author Daniel Wojdak
	* \version 1
	* \date 24-07-2013
	*/
	class LadowniaInfo :
		virtual public SLog::LoggerInterface
	{
	public:

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] maksymalnaObjetosc - Podstatwowa maksymlana obiej�to�� �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		LadowniaInfo(const STyp::Objetosc& maksymalnaObjetosc);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		explicit LadowniaInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* Konstruktor kopiuj�cy.
		* \param[in] obiekt - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		LadowniaInfo(const LadowniaInfo& obiekt);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~LadowniaInfo() = default;

		/**
		* \brief Metoda wyliczaj�ca maksymaln� pojemno�� �adowni.
		*
		* Metoda wylicza obj�to�� wzgl�dem parametr�w podanych podczas wywo�ania.
		* \param[in] parametry - Wymagane parametry do wykonania oblicze�.
		* \return Maksymalna obj�to�� �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Objetosc pobierzPojemnoscMaksymalna(const PodstawoweParametry& parametry) const;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;
	private:

		STyp::Objetosc pojemnoscMaksymalna_; /// Pojemno�� maksymalna.
		std::shared_ptr<SZmi::ZmianaInterfejs> przyrostPojemnosciMaksymalnej_; /// Obiekt wyliczaj�cy zmian� pojemno�ci maksymalnej.
	};
}
