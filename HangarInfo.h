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
		* \param[in] maksymalnaObjetosc - Podstatwowa maksymlana obiejêtoœæ hangaru.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		HangarInfo(const STyp::Powierzchnia& maksymalnaObjetosc);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		explicit HangarInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Konstruktor kopiuj¹cy.
		*
		* Konstruktor kopiuj¹cy.
		* \param[in] obiekt - Obiekt Ÿród³owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		HangarInfo(const HangarInfo& obiekt);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~HangarInfo() = default;

		/**
		* \brief Metoda pobieraj¹ca maksymaln¹ objêtoœæ przewo¿onych statków w hangarze.
		*
		* Metoda wylicza ile statków mo¿e zmieœciciæ siê w hangarze.
		* \param[in] parametry - Referencja do podstawowych parametrów obiektu dla którego wyliczany jest atrybut.
		* \return Maksymalna objêtoœæ statków znajduj¹cych siê w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Powierzchnia pobierzMaksymalnaIloscPrzewozonychStatkow(const PodstawoweParametry& parametry) const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	private:
		STyp::Powierzchnia pojemnoscMaksymalna_; /// Maksymalna objêtoœæ przewo¿onych statków
		std::shared_ptr<SZmi::ZmianaInterfejs> przyrostPojemnosciMaksymalnej_; /// Sprzytny wskaŸnik na obiekt wyliczaj¹cy zmianê maksymalnej objêtoœci przewo¿onych statków.
	};
}
