#pragma once
#include "Info.h"
#include "Ladownia.h"
#include "PodstawoweParametry.h"
namespace SpEx{
	/**
	* \brief Klasa opisuj¹ca ³adownie statku.
	*
	* Klasa zawiera podstawowe informacje o ³adownii statku.
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
		* \param[in] maksymalnaObjetosc - Podstatwowa maksymlana obiejêtoœæ ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		LadowniaInfo(const STyp::Objetosc& maksymalnaObjetosc);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		explicit LadowniaInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Konstruktor kopiuj¹cy.
		*
		* Konstruktor kopiuj¹cy.
		* \param[in] obiekt - Obiekt Ÿród³owy.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		LadowniaInfo(const LadowniaInfo& obiekt);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~LadowniaInfo() = default;

		/**
		* \brief Metoda wyliczaj¹ca maksymaln¹ pojemnoœæ ³adowni.
		*
		* Metoda wylicza objêtoœæ wzglêdem parametrów podanych podczas wywo³ania.
		* \param[in] parametry - Wymagane parametry do wykonania obliczeñ.
		* \return Maksymalna objêtoœæ ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Objetosc pobierzPojemnoscMaksymalna(const PodstawoweParametry& parametry) const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;
	private:

		STyp::Objetosc pojemnoscMaksymalna_; /// Pojemnoœæ maksymalna.
		std::shared_ptr<SZmi::ZmianaInterfejs> przyrostPojemnosciMaksymalnej_; /// Obiekt wyliczaj¹cy zmianê pojemnoœci maksymalnej.
	};
}
