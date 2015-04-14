#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	/**
	* Porównywane surowce maj¹ ró¿ne typy.
	*/
	class NiezgodnyTypSurowca :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:

		static const STyp::Identyfikator idNiezgodnyTypSurowca;

		NiezgodnyTypSurowca(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Identyfikator&, const STyp::Identyfikator&);
		virtual ~NiezgodnyTypSurowca() = default;

		std::string napis() const override;

	private:
		static const STyp::Tekst tytulNiezgodnyTypSurowcaDomyslny;
		static const STyp::Tekst trescNiezgodnyTypSurowcaDomyslny;

	};
}
