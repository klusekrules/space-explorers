#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	class BladKonfiguracjiEkranu :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idBladKonfiguracjiEkranu;

		BladKonfiguracjiEkranu(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Identyfikator& ekran, const STyp::Tekst& komunikat);
		virtual ~BladKonfiguracjiEkranu() = default;

		const STyp::Identyfikator& pobierzIdEkranu() const;
		
		std::string napis() const override;
	private:
		STyp::Identyfikator identyfikatorEkranu_;
	};
};
