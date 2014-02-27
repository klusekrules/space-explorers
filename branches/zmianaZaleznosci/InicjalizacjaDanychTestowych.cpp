#include "InicjalizacjaDanychTestowych.h"
#include "Aplikacja.h"
#include "Parser\ParserDokumentXml.h"

void InicjalizacjaDanychTestowych::zaladujDane(){
	SPar::ParserDokumentXml dokument;
	auto root = dokument.tworzElement(WEZEL_XML_ROOT);
	UNIT_TEST_ASSERT_NOTNULL(root);

	// SUROWIEC - METAL
	tworzParam(
		*tworzZmiana(
			*tworzSurowiec(
				*root, 
				STyp::Identyfikator(1), 
				STyp::Tekst("Metal"), 
				STyp::Tekst("Opis metalu."), 
				STyp::Masa(3), 
				STyp::Objetosc(1), 
				STyp::Bool(true)),
			STyp::Identyfikator(3), 
			STyp::Tekst(WEZEL_XML_CZAS)), 
		STyp::Identyfikator(0), 
		STyp::Wartosc(1.0));
	// SUROWIEC - METAL END

	// SUROWIEC - KRYSZTAL
	tworzParam(
		*tworzZmiana(
			*tworzSurowiec(
				*root, 
				STyp::Identyfikator(2), 
				STyp::Tekst("Krysztal"), 
				STyp::Tekst("Opis kryszta³u."),
				STyp::Masa(2),
				STyp::Objetosc(1.3), 
				STyp::Bool(true)),
			STyp::Identyfikator(3), 
			STyp::Tekst(WEZEL_XML_CZAS)), 
		STyp::Identyfikator(0), 
		STyp::Wartosc(2.0));
	// SUROWIEC - KRYSZTAL END

	// SUROWIEC - DEUTER
	tworzParam(
		*tworzZmiana(
			*tworzSurowiec(
				*root, 
				STyp::Identyfikator(3), 
				STyp::Tekst("Deuter"), 
				STyp::Tekst("Opis deuteru."), 
				STyp::Masa(1), 
				STyp::Objetosc(3), 
				STyp::Bool(true)), 
			STyp::Identyfikator(3), 
			STyp::Tekst(WEZEL_XML_CZAS)), 
		STyp::Identyfikator(0), 
		STyp::Wartosc(0.1));
	// SUROWIEC - DEUTER END

	// SUROWIEC - ENERGIA
	tworzSurowiec(
		*root,
		STyp::Identyfikator(4),
		STyp::Tekst("Energia"),
		STyp::Tekst("Opis energii."),
		STyp::Masa(0),
		STyp::Objetosc(0),
		STyp::Bool(false));
	// SUROWIEC - ENERGIA END
	
	// STATEK - MALY TRANSPORTOWIEC
	auto mtransport = tworzStatek(
		*root,
		STyp::Identyfikator(5),
		STyp::Tekst("Ma³y transportowiec"),
		STyp::Tekst("Opis ma³ego transportowca."),
		STyp::Masa(560),
		STyp::Powierzchnia(120),
		STyp::Bool(true)
		);
	tworzJednostkaAtakujaca(
		*mtransport,
		STyp::Obrazenia(50),
		STyp::Obrazenia(130),
		STyp::Obrazenia(40)
		);
	tworzJednostkaLatajaca(
		*mtransport,
		STyp::Identyfikator(1),
		STyp::Moc(500),
		STyp::ZuzyciePaliwa(300),
		STyp::Masa(40),
		STyp::Fluktuacja(0.7f)
		);
	tworzHangar(*mtransport,STyp::Powierzchnia(0));
	tworzLadownia(*mtransport,STyp::Objetosc(500));
	tworzKryterium(*mtransport,STyp::Identyfikator(1),STyp::Ilosc(2000));
	tworzKryterium(*mtransport,STyp::Identyfikator(2),STyp::Ilosc(2000));

	// STATEK - MALY TRANSPORTOWIEC END

	//UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajDane());
}

std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzSurowiec(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Tekst& nazwa,
	const STyp::Tekst& opis,
	const STyp::Masa& masa,
	const STyp::Objetosc& objetosc,
	const STyp::Bool& przyrostowy){
	auto surowiec = root.tworzElement(WEZEL_XML_SUROWCE_INFO);
	UNIT_TEST_ASSERT_NOTNULL(surowiec);
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, id.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_MASA, masa.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_OBJETOSC, objetosc.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_TYP, przyrostowy.napis().c_str()));
	UNIT_TEST_ASSERT_TRUE(surowiec->ustawTekst(opis().c_str()));
	return surowiec;
}
std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzStatek(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Tekst& nazwa,
	const STyp::Tekst& opis,
	const STyp::Masa& masa,
	const STyp::Powierzchnia& powierzchnia,
	const STyp::Bool& przewozonyWHangarze){
	auto statek = root.tworzElement(WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO);
	UNIT_TEST_ASSERT_NOTNULL(statek);
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, id.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_MASA, masa.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_POWIERZCHNIA, powierzchnia.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_HANGAR, przewozonyWHangarze.napis().c_str()));
	UNIT_TEST_ASSERT_TRUE(statek->ustawTekst(opis().c_str()));
	return statek;
}

std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzJednostkaAtakujaca(SPar::ParserElement& statek,
	const STyp::Obrazenia& atak,
	const STyp::Obrazenia& obrona,
	const STyp::Obrazenia& tarcza){
	auto jednostka = statek.tworzElement(WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO);
	UNIT_TEST_ASSERT_NOTNULL(jednostka);
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_ATAK, atak.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_PANCERZ, obrona.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_OSLONA, tarcza.napis().c_str()));
	return jednostka;
}

std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzJednostkaLatajaca(SPar::ParserElement& statek,
	const STyp::Identyfikator& idSilnika,
	const STyp::Moc& mocSilnika,
	const STyp::ZuzyciePaliwa& zuzuciePaliwa,
	const STyp::Masa& masaSilnika,
	const STyp::Fluktuacja& sprawnoscSilnika){
	auto jednostka = statek.tworzElement(WEZEL_XML_JEDNOSTKA_LATAJACA_INFO);
	UNIT_TEST_ASSERT_NOTNULL(jednostka);
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_RODZAJ_SILNIKA_ID, idSilnika.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_MOC_SILNIKA, mocSilnika.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_ZUZYCIE_PALIWA, zuzuciePaliwa.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_MASA_SILNIKA, masaSilnika.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_SPRAWNOSC_SILNIKA, sprawnoscSilnika.napis().c_str()));
	return jednostka;
}

std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzHangar(SPar::ParserElement& statek,
	const STyp::Powierzchnia& powierzchniaHangaru){
	auto hangar = statek.tworzElement(WEZEL_XML_HANGAR_INFO);
	UNIT_TEST_ASSERT_NOTNULL(hangar);
	UNIT_TEST_ASSERT_NOTNULL(hangar->tworzAtrybut(ATRYBUT_XML_POJEMNOSC_MAKSYMALNA, powierzchniaHangaru.napis().c_str()));
	return hangar;
}

std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzLadownia(SPar::ParserElement& statek,
	const STyp::Objetosc& objetoscLadowni){
	auto ladownia = statek.tworzElement(WEZEL_XML_LADOWNIA_INFO);
	UNIT_TEST_ASSERT_NOTNULL(ladownia);
	UNIT_TEST_ASSERT_NOTNULL(ladownia->tworzAtrybut(ATRYBUT_XML_POJEMNOSC_MAKSYMALNA, objetoscLadowni.napis().c_str()));
	return ladownia;
}

std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzKryterium(SPar::ParserElement& obiekt,
	const STyp::Identyfikator& id,
	const STyp::Poziom& poziom){
	auto kryterium = obiekt.tworzElement(WEZEL_XML_ZMIANA);
	UNIT_TEST_ASSERT_NOTNULL(kryterium);
	UNIT_TEST_ASSERT_NOTNULL(kryterium->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, id.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(kryterium->tworzAtrybut(ATRYBUT_XML_POZIOM, poziom.napis().c_str()));
	return kryterium;
}

std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzKryterium(SPar::ParserElement& obiekt,
	const STyp::Identyfikator& id,
	const STyp::Ilosc& ilosc){
	auto kryterium = obiekt.tworzElement(WEZEL_XML_ZMIANA);
	UNIT_TEST_ASSERT_NOTNULL(kryterium);
	UNIT_TEST_ASSERT_NOTNULL(kryterium->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, id.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(kryterium->tworzAtrybut(ATRYBUT_XML_POZIOM, ilosc.napis().c_str()));
	return kryterium;
}

std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzZmiana(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Tekst& atrybutFor){
	auto zmiana = root.tworzElement(WEZEL_XML_ZMIANA);
	UNIT_TEST_ASSERT_NOTNULL(zmiana);
	UNIT_TEST_ASSERT_NOTNULL(zmiana->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, id.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(zmiana->tworzAtrybut(ATRYBUT_XML_FOR, atrybutFor().c_str()));
	return zmiana;
}

std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzZmiana(SPar::ParserElement& root,
	const STyp::Identyfikator& id){
	auto zmiana = root.tworzElement(WEZEL_XML_ZMIANA);
	UNIT_TEST_ASSERT_NOTNULL(zmiana);
	UNIT_TEST_ASSERT_NOTNULL(zmiana->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, id.napis().c_str()));
	return zmiana;
}

std::shared_ptr<SPar::ParserElement> InicjalizacjaDanychTestowych::tworzParam(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Wartosc& atrybutFor){
	auto param = root.tworzElement(WEZEL_XML_PARAM);
	UNIT_TEST_ASSERT_NOTNULL(param);
	UNIT_TEST_ASSERT_NOTNULL(param->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, id.napis().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(param->tworzAtrybut(ATRYBUT_XML_WSPOLCZYNNIK, atrybutFor.napis().c_str()));
	return param;
}