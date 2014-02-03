#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{

	/**
	* Wyj¹tek informuje, ¿e nie uda³o siê podzieliæ ³adowni wed³ug podanych wymagañ.
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
