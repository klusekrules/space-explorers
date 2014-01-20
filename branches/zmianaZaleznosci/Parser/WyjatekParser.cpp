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
		STyp::Identyfikator(0xFF010001), //TODO: U�y� sta�ej.
		STyp::Tekst("Wyj�tek Parsera ( ParserAtrybut )!"),//TODO: U�y� sta�ej.
		STyp::Tekst(tekst.isEmpty() ? (STyp::Tekst("Wydruk elementu z b��dnym atrybutem:") + STyp::Tekst(atrybut ? atrybut->error() : "nullptr")) : (tekst + STyp::Tekst(atrybut ? atrybut->error() : "nullptr")))) //TODO: U�y� sta�ej.
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
		STyp::Identyfikator(0xFF010002),//TODO: U�y� sta�ej.
		STyp::Tekst("Wyj�tek Parsera ( ParserElement )!"),//TODO: U�y� sta�ej.
		STyp::Tekst(tekst.isEmpty() ? (STyp::Tekst("Wydruk b��dnego w�z�em:") + STyp::Tekst(element ? element->error() : "nullptr")) : (tekst + STyp::Tekst(element ? element->error() : "nullptr"))))//TODO: U�y� sta�ej.
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
		STyp::Identyfikator(0xFF010003),//TODO: U�y� sta�ej.
		STyp::Tekst("Wyj�tek Parsera ( ParserDokument )!"),//TODO: U�y� sta�ej.
		STyp::Tekst(tekst.isEmpty() ? STyp::Tekst("Wydruk b��du z dokumentu:") + STyp::Tekst(dokument ? dokument->error() : "nullptr") : tekst + STyp::Tekst(dokument ? dokument->error() : "nullptr")))//TODO: U�y� sta�ej.
	{
	}

	std::string WyjatekParser::napis() const {
		SLog::Logger str(NAZWAKLASY(WyjatekParser));
		str.dodajKlase(Wyjatek::napis());
		return std::move(str.napis());
	}
}
