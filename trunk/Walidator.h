#pragma once
#include <set>
#include "TypyProste\TypyProste.h"
#include "Singleton.h"

namespace SpEx{

	/**
	* \brief Klasa waliduj¹ca dane.
	*
	* Klasa s³u¿y do walidacji spójnoœci danych.
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
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor
		*/
		virtual ~Walidator() = default;
		
		/**
		* \brief Metoda dodaj¹ca identyfikator.
		*
		* Metoda dodaje identyfikator do zbioru nowych identyfikatorów
		* \param[in] id - Identyfikator planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		void dodajNowyIdentyfikatorPlanety(const STyp::Identyfikator& id);

		/**
		* \brief Metoda dodaj¹ca identyfikator.
		*
		* Metoda dodaje identyfikator do zbioru uzytych identyfikatorów.
		* \param[in] id - Identyfikator planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		void dodajUzytyIdentyfikatorPlanety(const STyp::Identyfikator& id);

		/**
		* \brief Metoda czyszcz¹ca obiekt.
		*
		* Metoda czyœci obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		void wyczysc();

		/**
		* \brief Metoda waliduj¹ca.
		*
		* Metoda wykonuje walidacje przekazanych danych do obiektu.
		* \return Zwrócona zostaje wartoœæ true, je¿eli walidacja zakoñczy siê powodzeniem. W przeciwnym wypadku zostanie zwrócona wartoœæ false.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		bool waliduj()const;

	private:
		std::set<STyp::Identyfikator> zbiorNowychIdPlanet; /// Zbiór nowych identyfikatorów.
		std::set<STyp::Identyfikator> zbiorUzytychIdPlanet; /// Zbiór u¿ytych identyfikatorów.
	};
};
