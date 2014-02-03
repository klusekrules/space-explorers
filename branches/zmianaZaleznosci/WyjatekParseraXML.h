#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	/**
	* Klasa bazowa dla wyj¹tków generowanych przez modu³ parsuj¹cy xml.
	*/
	class WyjatekParseraXML :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idWyjatekParseraXML;
		static const STyp::Tekst trescBladStrukturyXml;

		WyjatekParseraXML(const WyjatekParseraXML&);
		WyjatekParseraXML(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const std::exception&, const STyp::Tekst& = STyp::Tekst());
		virtual ~WyjatekParseraXML() = default;

		const STyp::Tekst& getPowod() const;
		void setPowod(const STyp::Tekst&);

		STyp::Tekst generujKomunikat() const override;

		std::string napis() const override;

	private:
		STyp::Tekst powod;

		static const STyp::Tekst tytulWyjatekParseraXML;
		static const STyp::Tekst trescWyjatekParseraXML;
	};
}
