#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	class NieznalezionoPliku :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idNieznalezionoPliku;
		NieznalezionoPliku(const STyp::Tekst&, const STyp::Tekst&, const STyp::Ilosc&, const STyp::Tekst&, const STyp::Tekst&);
		virtual ~NieznalezionoPliku() = default;

		const STyp::Tekst& pobierzNazwePliku() const;

		std::string napis() const override;
	private:
		STyp::Tekst nazwaPliku_;
	};
};
