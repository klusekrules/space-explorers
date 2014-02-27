#pragma once
#include "TestyJednostkowe.h"

class InicjalizacjaDanychTestowych : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(InicjalizacjaDanychTestowych);
		DODAJ_TEST(zaladujDane);
	TWORZ_PACZKE_TESTOW_END();
public:
	void zaladujDane();
	InicjalizacjaDanychTestowych() = default;
	virtual ~InicjalizacjaDanychTestowych() = default;

	std::shared_ptr<SPar::ParserElement> tworzSurowiec(SPar::ParserElement& root,
		const STyp::Identyfikator& id, 
		const STyp::Tekst& nazwa, 
		const STyp::Tekst& opis, 
		const STyp::Masa& masa, 
		const STyp::Objetosc& objetosc, 
		const STyp::Bool& przyrostowy );

	std::shared_ptr<SPar::ParserElement> tworzStatek(SPar::ParserElement& root,
		const STyp::Identyfikator& id,
		const STyp::Tekst& nazwa,
		const STyp::Tekst& opis,
		const STyp::Masa& masa,
		const STyp::Powierzchnia& powierzchnia,
		const STyp::Bool& przewozonyWHangarze);

	std::shared_ptr<SPar::ParserElement> tworzJednostkaAtakujaca(SPar::ParserElement& statek, 
		const STyp::Obrazenia& atak,
		const STyp::Obrazenia& obrona,
		const STyp::Obrazenia& tarcza );

	std::shared_ptr<SPar::ParserElement> tworzJednostkaLatajaca(SPar::ParserElement& statek,
		const STyp::Identyfikator& idSilnika,
		const STyp::Moc& mocSilnika,
		const STyp::ZuzyciePaliwa& zuzuciePaliwa,
		const STyp::Masa& masaSilnika,
		const STyp::Fluktuacja& sprawnoscSilnika );

	std::shared_ptr<SPar::ParserElement> tworzHangar(SPar::ParserElement& statek,
		const STyp::Powierzchnia& powierzchniaHangaru );

	std::shared_ptr<SPar::ParserElement> tworzLadownia(SPar::ParserElement& statek,
		const STyp::Objetosc& objetoscLadowni );

	std::shared_ptr<SPar::ParserElement> tworzKryterium(SPar::ParserElement& obiekt,
		const STyp::Identyfikator& id,
		const STyp::Poziom& poziom);

	std::shared_ptr<SPar::ParserElement> tworzKryterium(SPar::ParserElement& obiekt,
		const STyp::Identyfikator& id,
		const STyp::Ilosc& ilosc);

	std::shared_ptr<SPar::ParserElement> tworzZmiana(SPar::ParserElement& root,
		const STyp::Identyfikator& id,
		const STyp::Tekst& atrybutFor );

	std::shared_ptr<SPar::ParserElement> tworzZmiana(SPar::ParserElement& root,
		const STyp::Identyfikator& id);

	std::shared_ptr<SPar::ParserElement> tworzParam(SPar::ParserElement& root,
		const STyp::Identyfikator& id,
		const STyp::Wartosc& atrybutFor);
};
