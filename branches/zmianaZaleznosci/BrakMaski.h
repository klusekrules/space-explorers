#pragma once
#include "WyjatekParseraXML.h"

namespace SpEx{
	/**
	* Wyj¹tek informuje o braku elementu o podanej masce we wczytanych danych.
	*/
	class BrakMaski :
		virtual public SLog::LoggerInterface,
		public WyjatekParseraXML
	{
	public:
		static const STyp::Identyfikator idBrakMaski;

		BrakMaski(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& = STyp::Tekst());
		BrakMaski(const BrakMaski&);
		virtual ~BrakMaski() = default;

		const STyp::Tekst& getNazwaMaski() const;
		void setNazwaMaski(const STyp::Tekst&);

		STyp::Tekst generujKomunikat() const override;

		std::string napis() const override;

	private:
		STyp::Tekst nazwaMaski;

		static const STyp::Tekst tytulBrakMaski;
		static const STyp::Tekst trescBrakMaski;
	};
}
