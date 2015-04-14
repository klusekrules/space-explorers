#pragma once
#include <set>
#include "TypyProste\TypyProste.h"
#include "Singleton.h"

namespace SpEx{

	/**
	* \brief Klasa waliduj�ca dane.
	*
	* Klasa s�u�y do walidacji sp�jno�ci danych.
	* \author Daniel Wojdak
	* \version 1
	* \date 08-07-2014
	*/
	class Walidator	: 
		public se::Singleton<Walidator>
	{
		friend class se::Singleton<Walidator>;
	public:
		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor
		*/
		virtual ~Walidator() = default;
		
		/**
		* \brief Metoda dodaj�ca identyfikator.
		*
		* Metoda dodaje identyfikator do zbioru nowych identyfikator�w
		* \param[in] id - Identyfikator planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		void dodajNowyIdentyfikatorPlanety(const STyp::Identyfikator& id);

		/**
		* \brief Metoda dodaj�ca identyfikator.
		*
		* Metoda dodaje identyfikator do zbioru uzytych identyfikator�w.
		* \param[in] id - Identyfikator planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		void dodajUzytyIdentyfikatorPlanety(const STyp::Identyfikator& id);

		/**
		* \brief Metoda czyszcz�ca obiekt.
		*
		* Metoda czy�ci obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		void wyczysc();

		/**
		* \brief Metoda waliduj�ca.
		*
		* Metoda wykonuje walidacje przekazanych danych do obiektu.
		* \return Zwr�cona zostaje warto�� true, je�eli walidacja zako�czy si� powodzeniem. W przeciwnym wypadku zostanie zwr�cona warto�� false.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		bool waliduj()const;

	private:
		std::set<STyp::Identyfikator> zbiorNowychIdPlanet; /// Zbi�r nowych identyfikator�w.
		std::set<STyp::Identyfikator> zbiorUzytychIdPlanet; /// Zbi�r u�ytych identyfikator�w.
	};
};
