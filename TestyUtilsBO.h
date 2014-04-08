#pragma once
#include <memory>
#include "TypyProste\TypyProste.h"
#include "Parser\ParserInterfejs.h"

class TestyUtilsBO
{
public:
	TestyUtilsBO() = default;
	~TestyUtilsBO() = default;

	static std::shared_ptr<SPar::ParserDokument> dane();

	static std::shared_ptr<SPar::ParserElement> tworzSurowiec(SPar::ParserElement& root,
		const STyp::Identyfikator& id,
		const STyp::Tekst& nazwa,
		const STyp::Tekst& obrazek,
		const STyp::Tekst& opis,
		const STyp::Masa& masa,
		const STyp::Objetosc& objetosc,
		const STyp::Bool& przyrostowy);

	static std::shared_ptr<SPar::ParserElement> tworzStatek(SPar::ParserElement& root,
		const STyp::Identyfikator& id,
		const STyp::Tekst& nazwa,
		const STyp::Tekst& obrazek,
		const STyp::Tekst& opis,
		const STyp::Masa& masa,
		const STyp::Powierzchnia& powierzchnia,
		const STyp::Bool& przewozonyWHangarze);

	static std::shared_ptr<SPar::ParserElement> tworzBudynek(SPar::ParserElement& root,
		const STyp::Identyfikator& id,
		const STyp::Tekst& nazwa,
		const STyp::Tekst& obrazek,
		const STyp::Tekst& opis,
		const STyp::Powierzchnia& powierzchnia);

	static std::shared_ptr<SPar::ParserElement> tworzTechnologie(SPar::ParserElement& root,
		const STyp::Identyfikator& id,
		const STyp::Tekst& nazwa,
		const STyp::Tekst& obrazek,
		const STyp::Tekst& opis);
	
	static std::shared_ptr<SPar::ParserElement> tworzObrone(SPar::ParserElement& root,
		const STyp::Identyfikator& id,
		const STyp::Tekst& nazwa,
		const STyp::Tekst& obrazek,
		const STyp::Tekst& opis,
		const STyp::Powierzchnia& powierzchnia);

	static std::shared_ptr<SPar::ParserElement> tworzJednostkaAtakujaca(SPar::ParserElement& statek,
		const STyp::Obrazenia& atak,
		const STyp::Obrazenia& obrona,
		const STyp::Obrazenia& tarcza);

	static std::shared_ptr<SPar::ParserElement> tworzJednostkaLatajaca(SPar::ParserElement& statek,
		const STyp::Identyfikator& idSilnika,
		const STyp::Moc& mocSilnika,
		const STyp::ZuzyciePaliwa& zuzuciePaliwa,
		const STyp::Masa& masaSilnika,
		const STyp::Fluktuacja& sprawnoscSilnika);

	static std::shared_ptr<SPar::ParserElement> tworzHangar(SPar::ParserElement& statek,
		const STyp::Powierzchnia& powierzchniaHangaru);

	static std::shared_ptr<SPar::ParserElement> tworzLadownia(SPar::ParserElement& statek,
		const STyp::Objetosc& objetoscLadowni);

	static std::shared_ptr<SPar::ParserElement> tworzKryterium(SPar::ParserElement& obiekt,
		const STyp::Identyfikator& id,
		const STyp::Poziom& poziom);

	static std::shared_ptr<SPar::ParserElement> tworzKryterium(SPar::ParserElement& obiekt,
		const STyp::Identyfikator& id,
		const STyp::Ilosc& ilosc);

	static std::shared_ptr<SPar::ParserElement> tworzZapotrzebowanie(SPar::ParserElement& obiekt,
		const STyp::Identyfikator& id,
		const STyp::Ilosc& ilosc);

	static std::shared_ptr<SPar::ParserElement> tworzProdukcje(SPar::ParserElement& obiekt,
		const STyp::Identyfikator& id,
		const STyp::Ilosc& ilosc);

	static std::shared_ptr<SPar::ParserElement> tworzZmiana(SPar::ParserElement& root,
		const STyp::Identyfikator& id,
		const STyp::Tekst& atrybutFor);

	static std::shared_ptr<SPar::ParserElement> tworzZmiana(SPar::ParserElement& root,
		const STyp::Identyfikator& id);

	static std::shared_ptr<SPar::ParserElement> tworzParam(SPar::ParserElement& root,
		const STyp::Identyfikator& id,
		const STyp::Wartosc& atrybutFor);
};

