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
		* \param[in] poziom - Poziom tworzonych obiekt�w.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisuj�cego.
		*/
		JednostkaAtakujaca(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo);

		/**
		* \brief Konstruktor.
		*
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
		* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisuj�cego.
		*/
		JednostkaAtakujaca(const PodstawoweParametry& podstawoweParametry, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo);

		/**
		* \brief Destruktor.
		*/
		virtual ~JednostkaAtakujaca() = default;

		/**
		* Metoda atak s�u�y do wyliczania obra�e� zadawanych przez obiekt.
		* \return Obra�enia zadane przez obiekt.
		*/
		virtual STyp::Obrazenia pobierzAtak() const;

		/**
		* Metoda obliczaj�ca obra�enia mo�liwe do przyj�cia przez pancerz.
		* \return Obra�enia, kt�re mo�e przyj�� pancerz.
		*/
		virtual STyp::Obrazenia pobierzPancerz() const;

		/**
		* Metoda obliczaj�ca obra�enia mo�liwe do przyj�cia przez oslone.
		* \return Obra�enia, kt�re mo�e przyj�� os�ona.
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
