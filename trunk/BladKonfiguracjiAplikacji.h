#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	class BladKonfiguracjiAplikacji :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idBladKonfiguracjiAplikacji;

		BladKonfiguracjiAplikacji(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Tekst& stos, const STyp::Tekst& komunikat);
		virtual ~BladKonfiguracjiAplikacji() = default;

		std::string napis() const override;
	};
};
