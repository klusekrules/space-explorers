#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	class NiezaimplementowanaMetoda :
		public STyp::Wyjatek,
		virtual public SLog::LoggerInterface
	{
	public:
		static const STyp::Identyfikator idNiezaimplementowanaMetoda;
		static const STyp::Tekst tytulNiezaimplementowanaMetoda;
		static const STyp::Tekst trescNiezaimplementowanaMetoda;
		NiezaimplementowanaMetoda(const STyp::Tekst&, const STyp::Tekst&, const STyp::Ilosc&);
		virtual ~NiezaimplementowanaMetoda() = default;
		std::string napis() const override;
	};
}
