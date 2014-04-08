#pragma once
#include <set>
#include "TypyProste\TypyProste.h"
#include "Singleton.h"

namespace SpEx{
	class Walidator	: 
		public se::Singleton<Walidator>
	{
		friend class se::Singleton<Walidator>;
	public:
		virtual ~Walidator() = default;
		
		void dodajNowyIdentyfikatorPlanety(const STyp::Identyfikator &);
		void dodajUzytyIdentyfikatorPlanety(const STyp::Identyfikator &);

		void wyczysc();

		bool waliduj()const;

	private:
		std::set<STyp::Identyfikator> zbiorNowychIdPlanet;
		std::set<STyp::Identyfikator> zbiorUzytychIdPlanet;
		Walidator() = default;
		Walidator(const Walidator&) = delete;
		Walidator& operator=(const Walidator&) = delete;
	};
};
