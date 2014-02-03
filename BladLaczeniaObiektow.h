#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	/**
	* Wyj�tek informuje, �e nie uda�o sie po��czy� obiekt�w.
	*/
	class BladLaczeniaObiektow :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idBladLaczeniaObiektow;

		BladLaczeniaObiektow(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& obiektA, const STyp::Tekst& obiektB);
		virtual ~BladLaczeniaObiektow() = default;

		const STyp::Tekst& getObiektA() const;
		void setObiektA(const STyp::Tekst&);

		const STyp::Tekst& getObiektB() const;
		void setObiektB(const STyp::Tekst&);

		STyp::Tekst generujKomunikat() const override;

		std::string napis() const override;

	private:
		STyp::Tekst obiektA;
		STyp::Tekst obiektB;

		static const STyp::Tekst tytulBladLaczeniaObiektow;
		static const STyp::Tekst trescBladLaczeniaObiektow;
	};
}
