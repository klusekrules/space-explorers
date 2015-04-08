#pragma once
#include "JednostkaAtakujacaInfo.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	/**
	* \brief Klasa reprezentuj¹ca jednostkê atakuj¹c¹.
	*
	* Klasa zawieraj¹ca interfejs jednostki atakuj¹cej, zawiera metody wyliczaj¹ce obra¿enia zadawane,
	* obra¿enia otrzymywane oraz obra¿enia odbijane.
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
		* \param[in] poziom - Poziom tworzonych obiektów.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaAtakujaca(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
		* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaAtakujaca(const PodstawoweParametry& podstawoweParametry, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destrutkor.
		*/
		virtual ~JednostkaAtakujaca() = default;

		/**
		* \brief Metoda wyliczaj¹c atak jednostki.
		*
		* Metoda atak s³u¿y do wyliczania obra¿eñ zadawanych przez obiekt.
		* \return Obra¿enia zadane przez obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Obrazenia pobierzAtak() const;

		/**
		* \brief Metoda wyliczaj¹ca pancerz jednostki.
		*
		* Metoda obliczaj¹ca obra¿enia mo¿liwe do przyjêcia przez pancerz.
		* \return Obra¿enia, które mo¿e przyj¹æ pancerz.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Obrazenia pobierzPancerz() const;

		/**
		* \brief Metoda wyliczaj¹ca os³onê jednostki.
		*
		* Metoda obliczaj¹ca obra¿enia mo¿liwe do przyjêcia przez oslone.
		* \return Obra¿enia, które mo¿e przyj¹æ os³ona.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Obrazenia pobierzOslone() const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	protected:
		const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo_; /// WskaŸnik na klasê opisuj¹c¹. Wymagany do poprawnego dzia³ania.
	};
}
