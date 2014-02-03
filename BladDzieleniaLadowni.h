#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{

	/**
	* Wyj�tek informuje, �e nie uda�o si� podzieli� �adowni wed�ug podanych wymaga�.
	*/
	class BladDzieleniaLadowni :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idBladDzieleniaLadowni;

		BladDzieleniaLadowni(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& tLadownia);
		virtual ~BladDzieleniaLadowni() = default;

		const STyp::Tekst& getLadownia() const;
		void setLadownia(const STyp::Tekst& tLadownia);

		STyp::Tekst generujKomunikat() const override;

		std::string napis() const override;

	private:
		STyp::Tekst ladownia;
		static const STyp::Tekst tytulBladDzieleniaLadowni;
		static const STyp::Tekst trescBladDzieleniaLadowni;
	};
}
