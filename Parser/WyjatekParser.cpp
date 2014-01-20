#include "WyjatekParser.h"
#include "Logger\Logger.h"

namespace SPar{
	WyjatekParser::WyjatekParser(
		const STyp::Tekst& plik,
		const STyp::Ilosc& linia,
		const STyp::Tekst& sladStosu,
		const ParserAtrybut* atrybut,
		const STyp::Tekst& tekst
		)
		: Wyjatek(
		plik,
		linia,
		sladStosu,
		STyp::Identyfikator(0xFF010001), //TODO: U¿yæ sta³ej.
		STyp::Tekst("Wyj¹tek Parsera ( ParserAtrybut )!"),//TODO: U¿yæ sta³ej.
		STyp::Tekst(tekst.isEmpty() ? (STyp::Tekst("Wydruk elementu z b³êdnym atrybutem:") + STyp::Tekst(atrybut ? atrybut->error() : "nullptr")) : (tekst + STyp::Tekst(atrybut ? atrybut->error() : "nullptr")))) //TODO: U¿yæ sta³ej.
	{
	}

	WyjatekParser::WyjatekParser(
		const STyp::Tekst& plik,
		const STyp::Ilosc& linia,
		const STyp::Tekst& sladStosu,
		const ParserElement* element,
		const STyp::Tekst& tekst
		)
		: Wyjatek(
		plik,
		linia,
		sladStosu,
		STyp::Identyfikator(0xFF010002),//TODO: U¿yæ sta³ej.
		STyp::Tekst("Wyj¹tek Parsera ( ParserElement )!"),//TODO: U¿yæ sta³ej.
		STyp::Tekst(tekst.isEmpty() ? (STyp::Tekst("Wydruk b³êdnego wêz³em:") + STyp::Tekst(element ? element->error() : "nullptr")) : (tekst + STyp::Tekst(element ? element->error() : "nullptr"))))//TODO: U¿yæ sta³ej.
	{
	}

	WyjatekParser::WyjatekParser(
		const STyp::Tekst& plik,
		const STyp::Ilosc& linia,
		const STyp::Tekst& sladStosu,
		const ParserDokument* dokument,
		const STyp::Tekst& tekst
		) : Wyjatek(
		plik,
		linia,
		sladStosu,
		STyp::Identyfikator(0xFF010003),//TODO: U¿yæ sta³ej.
		STyp::Tekst("Wyj¹tek Parsera ( ParserDokument )!"),//TODO: U¿yæ sta³ej.
		STyp::Tekst(tekst.isEmpty() ? STyp::Tekst("Wydruk b³êdu z dokumentu:") + STyp::Tekst(dokument ? dokument->error() : "nullptr") : tekst + STyp::Tekst(dokument ? dokument->error() : "nullptr")))//TODO: U¿yæ sta³ej.
	{
	}

	std::string WyjatekParser::napis() const {
		SLog::Logger str(NAZWAKLASY(WyjatekParser));
		str.dodajKlase(Wyjatek::napis());
		return std::move(str.napis());
	}
}
