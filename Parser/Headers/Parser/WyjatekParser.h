#pragma once
#include "ParserInterfejs.h"
#include "TypyProste\Wyjatek.h"

namespace SPar{
	class PARSER_API WyjatekParser: 
		public STyp::Wyjatek,
		virtual public SLog::LoggerInterface
	{
	public:
		WyjatekParser(
			const STyp::Tekst& plik,
			const STyp::Tekst& funkcja,
			const STyp::Ilosc& linia,
			const STyp::Tekst& sladStosu,
			const ParserAtrybut* atrybut,
			const STyp::Tekst& tekst = STyp::Tekst()
			);

		WyjatekParser(
			const STyp::Tekst& plik,
			const STyp::Tekst& funkcja,
			const STyp::Ilosc& linia,
			const STyp::Tekst& sladStosu,
			const ParserElement* element,
			const STyp::Tekst& tekst = STyp::Tekst()
			);

		WyjatekParser(
			const STyp::Tekst& plik,
			const STyp::Tekst& funkcja,
			const STyp::Ilosc& linia,
			const STyp::Tekst& sladStosu,
			const ParserDokument* dokument,
			const STyp::Tekst& tekst = STyp::Tekst()
			);

		WyjatekParser(const WyjatekParser&) = default;
		~WyjatekParser() = default;
		const STyp::Tekst& zawartoscWezla()const;
		std::string napis() const override;
	private:
		STyp::Tekst wezel_;
	};
}
