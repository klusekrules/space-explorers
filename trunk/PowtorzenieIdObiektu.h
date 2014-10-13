#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	class PowtorzenieIdObiektu :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idPowtorzeniaIdObiektu;
		PowtorzenieIdObiektu(const STyp::Tekst&, const STyp::Tekst&, const STyp::Ilosc&, const STyp::Tekst& debug, const STyp::Identyfikator&, const STyp::Tekst&);
		virtual ~PowtorzenieIdObiektu() = default;

		const STyp::Identyfikator& pobierzIdentyfikatorObiektu() const;

		std::string napis() const override;
	private:
		STyp::Identyfikator identyfikatorObiektu_;
	};
};
