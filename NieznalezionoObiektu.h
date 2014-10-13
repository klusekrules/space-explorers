#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	/**
	* Wyj¹tek infomuje, ¿e obiekt nie zosta³ znaleziony.
	*/
	class NieznalezionoObiektu :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idNieznalezionoObiektu;

		NieznalezionoObiektu(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Tekst& tNazwa);
		virtual ~NieznalezionoObiektu(void) = default;

		const STyp::Tekst& getIdentyfikator() const;
		void setIdentyfikator(const STyp::Tekst&);

		STyp::Tekst generujKomunikat() const override;

		std::string napis() const override;

	private:
		STyp::Tekst identyfikator;

		static const STyp::Tekst tytulNieznalezionoObiektu;
		static const STyp::Tekst trescNieznalezionoObiektu;
	};
}
