#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	class BladStukturyStanu :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idBladStukturyStanu;
		BladStukturyStanu(const STyp::Tekst&, const STyp::Tekst&, const STyp::Ilosc&, const STyp::Tekst& debug, const STyp::Identyfikator&, const STyp::Tekst&);
		virtual ~BladStukturyStanu() = default; 
		const STyp::Identyfikator& pobierzIdentyfikatorStanu() const;

		std::string napis() const override;
	private:
		STyp::Identyfikator identyfikatorStanu_;
	};
};
