#pragma once
#include "JednostkaAtakujacaInfo.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	/**
	* \brief Klasa reprezentuj�ca jednostk� atakuj�c�.
	*
	* Klasa zawieraj�ca interfejs jednostki atakuj�cej, zawiera metody wyliczaj�ce obra�enia zadawane,
	* obra�enia otrzymywane oraz obra�enia odbijane.
	* \author Daniel Wojdak
	* \version 1
	* \date 24-07-2013
	*/
	class JednostkaAtakujaca :
		virtual public PodstawoweParametry,
		virtual public SLog::LoggerInterface
	{
	public:

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] poziom - Poziom tworzonych obiekt�w.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaAtakujaca(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
		* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaAtakujaca(const PodstawoweParametry& podstawoweParametry, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destrutkor.
		*/
		virtual ~JednostkaAtakujaca() = default;

		/**
		* \brief Metoda wyliczaj�c atak jednostki.
		*
		* Metoda atak s�u�y do wyliczania obra�e� zadawanych przez obiekt.
		* \return Obra�enia zadane przez obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Obrazenia pobierzAtak() const;

		/**
		* \brief Metoda wyliczaj�ca pancerz jednostki.
		*
		* Metoda obliczaj�ca obra�enia mo�liwe do przyj�cia przez pancerz.
		* \return Obra�enia, kt�re mo�e przyj�� pancerz.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Obrazenia pobierzPancerz() const;

		/**
		* \brief Metoda wyliczaj�ca os�on� jednostki.
		*
		* Metoda obliczaj�ca obra�enia mo�liwe do przyj�cia przez oslone.
		* \return Obra�enia, kt�re mo�e przyj�� os�ona.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Obrazenia pobierzOslone() const;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

	protected:
		const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo_; /// Wska�nik na klas� opisuj�c�. Wymagany do poprawnego dzia�ania.
	};
}
