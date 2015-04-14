#include "TestyUtilsBO.h"
#include "TestyJednostkowe.h"
#include "Parser\ParserDokumentXml.h"
#include "Utils\DefinicjeWezlowXML.h"

std::shared_ptr<SPar::ParserDokument> TestyUtilsBO::dane(){
	auto before = std::locale::global(std::locale("C"));
	std::shared_ptr<SPar::ParserDokument>dokument = std::make_shared<SPar::ParserDokumentXml>();
	auto root = dokument->tworzElement(WEZEL_XML_ROOT);
	UNIT_TEST_ASSERT_NOTNULL(root);

	// SUROWIEC - METAL
	tworzParam(
		*tworzZmiana(
		*tworzSurowiec(
		*root,
		STyp::Identyfikator(1),
		STyp::Tekst("Metal"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis metalu."),
		STyp::Masa(3),
		STyp::Objetosc(1),
		STyp::Bool(true)),
		STyp::Identyfikator(8),
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
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis kryszta³u."),
		STyp::Masa(2),
		STyp::Objetosc(1.3),
		STyp::Bool(true)),
		STyp::Identyfikator(8),
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
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis deuteru."),
		STyp::Masa(1),
		STyp::Objetosc(3),
		STyp::Bool(true)),
		STyp::Identyfikator(8),
		STyp::Tekst(WEZEL_XML_CZAS)),
		STyp::Identyfikator(0),
		STyp::Wartosc(0.1));
	// SUROWIEC - DEUTER END

	// SUROWIEC - ENERGIA
	tworzSurowiec(
		*root,
		STyp::Identyfikator(4),
		STyp::Tekst("Energia"),
		STyp::Tekst("BrakObrazka"),
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
		STyp::Tekst("BrakObrazka"),
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
	tworzHangar(*mtransport, STyp::Powierzchnia(0));
	tworzLadownia(*mtransport, STyp::Objetosc(500));
	tworzKryterium(*mtransport, STyp::Identyfikator(1), STyp::Ilosc(2000));
	tworzKryterium(*mtransport, STyp::Identyfikator(2), STyp::Ilosc(2000));
	tworzKryterium(*mtransport, STyp::Identyfikator(9), STyp::Poziom(3));
	// STATEK - MALY TRANSPORTOWIEC END

	// STATEK - DUZY TRANSPORTOWIEC
	auto dtransport = tworzStatek(
		*root,
		STyp::Identyfikator(6),
		STyp::Tekst("Du¿y transportowiec"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis du¿ego transportowca."),
		STyp::Masa(560 * 3),
		STyp::Powierzchnia(120 * 2.5),
		STyp::Bool(true)
		);
	tworzJednostkaAtakujaca(
		*dtransport,
		STyp::Obrazenia(50 * 2),
		STyp::Obrazenia(130 * 1.5),
		STyp::Obrazenia(40 * 4)
		);
	tworzJednostkaLatajaca(
		*dtransport,
		STyp::Identyfikator(1),
		STyp::Moc(500 * 4),
		STyp::ZuzyciePaliwa(300 * 3),
		STyp::Masa(40 * 3.4),
		STyp::Fluktuacja(0.75f)
		);
	tworzHangar(*dtransport, STyp::Powierzchnia(0));
	tworzLadownia(*dtransport, STyp::Objetosc(2500));
	tworzKryterium(*dtransport, STyp::Identyfikator(1), STyp::Ilosc(6000));
	tworzKryterium(*dtransport, STyp::Identyfikator(2), STyp::Ilosc(6000));
	tworzKryterium(*dtransport, STyp::Identyfikator(9), STyp::Poziom(3));
	tworzKryterium(*dtransport, STyp::Identyfikator(10), STyp::Poziom(5));
	// STATEK - DUZY TRANSPORTOWIEC END

	// STATEK - MYSLIWIEC
	auto mysliwiec = tworzStatek(
		*root,
		STyp::Identyfikator(7),
		STyp::Tekst("Myœliwiec"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis myœliwca."),
		STyp::Masa(900),
		STyp::Powierzchnia(200),
		STyp::Bool(true)
		);
	tworzJednostkaAtakujaca(
		*mysliwiec,
		STyp::Obrazenia(200),
		STyp::Obrazenia(160),
		STyp::Obrazenia(200)
		);
	tworzJednostkaLatajaca(
		*mysliwiec,
		STyp::Identyfikator(2),
		STyp::Moc(1500),
		STyp::ZuzyciePaliwa(400),
		STyp::Masa(80),
		STyp::Fluktuacja(0.72f)
		);
	tworzHangar(*mysliwiec, STyp::Powierzchnia(0));
	tworzLadownia(*mysliwiec, STyp::Objetosc(100));
	tworzKryterium(*mysliwiec, STyp::Identyfikator(1), STyp::Ilosc(3000));
	tworzKryterium(*mysliwiec, STyp::Identyfikator(2), STyp::Ilosc(1000));
	// STATEK - MYSLIWIEC END

	// STATEK - TRANSPORTER
	auto transporter = tworzStatek(
		*root,
		STyp::Identyfikator(8),
		STyp::Tekst("Transporter"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis transportera."),
		STyp::Masa(10000),
		STyp::Powierzchnia(20000),
		STyp::Bool(false)
		);
	tworzJednostkaAtakujaca(
		*transporter,
		STyp::Obrazenia(300),
		STyp::Obrazenia(1500),
		STyp::Obrazenia(2000)
		);
	tworzJednostkaLatajaca(
		*transporter,
		STyp::Identyfikator(4),
		STyp::Moc(5000),
		STyp::ZuzyciePaliwa(1000),
		STyp::Masa(150),
		STyp::Fluktuacja(0.86f)
		);
	tworzHangar(*transporter, STyp::Powierzchnia(18000));
	tworzLadownia(*transporter, STyp::Objetosc(8000));
	tworzKryterium(*transporter, STyp::Identyfikator(1), STyp::Ilosc(25000));
	tworzKryterium(*transporter, STyp::Identyfikator(2), STyp::Ilosc(20000));
	tworzKryterium(*transporter, STyp::Identyfikator(3), STyp::Ilosc(5000));
	// STATEK - TRANSPORTER END

	// TECHNOLOGIA - KOMPUTEROWA
	auto tKomputerowa = tworzTechnologie(
		*root, 
		STyp::Identyfikator(9),
		STyp::Tekst("Technologia komputerowa"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis technologii komputerowej.")
		);
	tworzKryterium(*tKomputerowa, STyp::Identyfikator(10), STyp::Poziom(2));
	// TECHNOLOGIA - KOMPUTEROWA END

	// TECHNOLOGIA - ENERGETYCZNA
	auto tEnergetyczna = tworzTechnologie(
		*root,
		STyp::Identyfikator(10),
		STyp::Tekst("Technologia energetyczna"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis technologii energetycznej.")
		);
	// TECHNOLOGIA - ENERGETYCZNA END

	// BUDYNEK - KOPALNIA METALU
	auto bkopalnia = tworzBudynek(
		*root,
		STyp::Identyfikator(11),
		STyp::Tekst("Kopalnia metalu"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis kopalni metalu."),
		STyp::Powierzchnia(1200)
		);
	auto bKopalniaKryteriuMetal = tworzZmiana(*tworzKryterium(*bkopalnia, STyp::Identyfikator(1), STyp::Ilosc(60)), STyp::Identyfikator(4));
	tworzParam(*bKopalniaKryteriuMetal, STyp::Identyfikator(1),STyp::Wartosc(1));
	tworzParam(*bKopalniaKryteriuMetal, STyp::Identyfikator(2), STyp::Wartosc(2));

	auto bKopalniaKryteriuKrysztal = tworzZmiana(*tworzKryterium(*bkopalnia, STyp::Identyfikator(2), STyp::Ilosc(24)), STyp::Identyfikator(4));
	tworzParam(*bKopalniaKryteriuKrysztal, STyp::Identyfikator(1), STyp::Wartosc(1));
	tworzParam(*bKopalniaKryteriuKrysztal, STyp::Identyfikator(2), STyp::Wartosc(2));

	auto bKopalniaZmianaCzas = tworzZmiana(*bkopalnia, STyp::Identyfikator(7),STyp::Tekst("Czas"));
	tworzParam(*bKopalniaZmianaCzas, STyp::Identyfikator(0), STyp::Wartosc(2));
	tworzParam(*tworzZmiana(*bKopalniaZmianaCzas, STyp::Identyfikator(6)), STyp::Identyfikator(13), STyp::Wartosc(0));

	tworzProdukcje(*bkopalnia, STyp::Identyfikator(1), STyp::Ilosc(50));
	tworzZapotrzebowanie(*bkopalnia, STyp::Identyfikator(4), STyp::Ilosc(120));
	// BUDYNEK - KOPALNIA METALU END

	// BUDYNEK - ELEKTROWNIA SLONECZNA
	auto belektrownia = tworzBudynek(
		*root,
		STyp::Identyfikator(12),
		STyp::Tekst("Elektrownia s³oneczna"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis elektrowni s³onecznej."),
		STyp::Powierzchnia(2500)
		);
	auto belektrowniaKryteriuMetal = tworzZmiana(*tworzKryterium(*belektrownia, STyp::Identyfikator(1), STyp::Ilosc(40)), STyp::Identyfikator(4));
	tworzParam(*belektrowniaKryteriuMetal, STyp::Identyfikator(1), STyp::Wartosc(1));
	tworzParam(*belektrowniaKryteriuMetal, STyp::Identyfikator(2), STyp::Wartosc(2));

	auto belektrowniaKryteriuKrysztal = tworzZmiana(*tworzKryterium(*belektrownia, STyp::Identyfikator(2), STyp::Ilosc(13)), STyp::Identyfikator(4));
	tworzParam(*belektrowniaKryteriuKrysztal, STyp::Identyfikator(1), STyp::Wartosc(1));
	tworzParam(*belektrowniaKryteriuKrysztal, STyp::Identyfikator(2), STyp::Wartosc(2));

	auto belektrowniaZmianaCzas = tworzZmiana(*belektrownia, STyp::Identyfikator(7), STyp::Tekst("Czas"));
	tworzParam(*belektrowniaZmianaCzas, STyp::Identyfikator(0), STyp::Wartosc(2));
	tworzParam(*tworzZmiana(*belektrowniaZmianaCzas, STyp::Identyfikator(6)), STyp::Identyfikator(13), STyp::Wartosc(0));
	tworzProdukcje(*belektrownia, STyp::Identyfikator(4), STyp::Ilosc(320));
	// BUDYNEK - ELEKTROWNIA SLONECZNA END

	// BUDYNEK - FABRYKA ROBOTOW
	auto bfabryka = tworzBudynek(
		*root,
		STyp::Identyfikator(13),
		STyp::Tekst("Fabryka robotów"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis fabryki robotów."),
		STyp::Powierzchnia(500)
		);
	//tworzKryterium(*bfabryka, STyp::Identyfikator(3), STyp::Ilosc(96));

	auto bfabrykaKryteriuMetal = tworzZmiana(*tworzKryterium(*bfabryka, STyp::Identyfikator(1), STyp::Ilosc(200)), STyp::Identyfikator(4));
	tworzParam(*bfabrykaKryteriuMetal, STyp::Identyfikator(1), STyp::Wartosc(1));
	tworzParam(*bfabrykaKryteriuMetal, STyp::Identyfikator(2), STyp::Wartosc(2));

	auto bfabrykaKryteriuKrysztal = tworzZmiana(*tworzKryterium(*bfabryka, STyp::Identyfikator(2), STyp::Ilosc(140)), STyp::Identyfikator(4));
	tworzParam(*bfabrykaKryteriuKrysztal, STyp::Identyfikator(1), STyp::Wartosc(1));
	tworzParam(*bfabrykaKryteriuKrysztal, STyp::Identyfikator(2), STyp::Wartosc(2));

	tworzKryterium(*bfabryka, STyp::Identyfikator(11), STyp::Poziom(3));
	tworzKryterium(*bfabryka, STyp::Identyfikator(12), STyp::Poziom(2));

	auto bfabrykaZmianaCzas = tworzZmiana(*bfabryka, STyp::Identyfikator(7), STyp::Tekst("Czas"));
	tworzParam(*bfabrykaZmianaCzas, STyp::Identyfikator(0), STyp::Wartosc(2));
	tworzParam(*tworzZmiana(*bfabrykaZmianaCzas, STyp::Identyfikator(6)), STyp::Identyfikator(13), STyp::Wartosc(0));
	// BUDYNEK - FABRYKA ROBOTOW END

	// OBRONA - WYRZUTNIA RAKIET
	auto owyrzutnia = tworzObrone(
		*root,
		STyp::Identyfikator(14),
		STyp::Tekst("Wyrzutnia rakiet"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis wyrzutni rakiet."),
		STyp::Powierzchnia(2.31)
		);
	tworzJednostkaAtakujaca(
		*owyrzutnia,
		STyp::Obrazenia(90),
		STyp::Obrazenia(120),
		STyp::Obrazenia(10)
		);
	tworzKryterium(*owyrzutnia, STyp::Identyfikator(1), STyp::Ilosc(2000));
	// OBRONA - WYRZUTNIA RAKIET END

	// OBRONA - DZIALO LASEROWE
	auto olaserowe = tworzObrone(
		*root,
		STyp::Identyfikator(15),
		STyp::Tekst("Dzia³o laserowe"),
		STyp::Tekst("BrakObrazka"),
		STyp::Tekst("Opis dzia³a laserowego."),
		STyp::Powierzchnia(4.62)
		);
	tworzJednostkaAtakujaca(
		*olaserowe,
		STyp::Obrazenia(80),
		STyp::Obrazenia(60),
		STyp::Obrazenia(30)
		);
	tworzKryterium(*olaserowe, STyp::Identyfikator(1), STyp::Ilosc(1500));
	tworzKryterium(*olaserowe, STyp::Identyfikator(2), STyp::Ilosc(500));
	tworzKryterium(*olaserowe, STyp::Identyfikator(3), STyp::Ilosc(100));
	// OBRONA - DZIALO LASEROWE END


	std::locale::global(before);
	return dokument;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzSurowiec(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Tekst& nazwa,
	const STyp::Tekst& obrazek,
	const STyp::Tekst& opis,
	const STyp::Masa& masa,
	const STyp::Objetosc& objetosc,
	const STyp::Bool& przyrostowy){
	auto surowiec = root.tworzElement(WEZEL_XML_SUROWCE_INFO);
	UNIT_TEST_ASSERT_NOTNULL(surowiec);
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_ADRES_OBRAZKA, obrazek().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_MASA, std::to_string(masa()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_OBJETOSC, std::to_string(objetosc()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(surowiec->tworzAtrybut(ATRYBUT_XML_TYP, std::to_string(przyrostowy()).c_str()));
	UNIT_TEST_ASSERT_TRUE(surowiec->ustawTekst(opis().c_str()));
	return surowiec;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzStatek(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Tekst& nazwa,
	const STyp::Tekst& obrazek,
	const STyp::Tekst& opis,
	const STyp::Masa& masa,
	const STyp::Powierzchnia& powierzchnia,
	const STyp::Bool& przewozonyWHangarze){
	auto statek = root.tworzElement(WEZEL_XML_STATEK_INFO);
	UNIT_TEST_ASSERT_NOTNULL(statek);
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_ADRES_OBRAZKA, obrazek().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_MASA, std::to_string(masa()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_POWIERZCHNIA, std::to_string(powierzchnia()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(statek->tworzAtrybut(ATRYBUT_XML_HANGAR, std::to_string(przewozonyWHangarze()).c_str()));
	UNIT_TEST_ASSERT_TRUE(statek->ustawTekst(opis().c_str()));
	return statek;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzTechnologie(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Tekst& nazwa,
	const STyp::Tekst& obrazek,
	const STyp::Tekst& opis){
	auto technologia = root.tworzElement(WEZEL_XML_TECHNOLOGIA_INFO);
	UNIT_TEST_ASSERT_NOTNULL(technologia);
	UNIT_TEST_ASSERT_NOTNULL(technologia->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(technologia->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(technologia->tworzAtrybut(ATRYBUT_XML_ADRES_OBRAZKA, obrazek().c_str()));
	UNIT_TEST_ASSERT_TRUE(technologia->ustawTekst(opis().c_str()));
	return technologia;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzBudynek(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Tekst& nazwa,
	const STyp::Tekst& obrazek,
	const STyp::Tekst& opis,
	const STyp::Powierzchnia& powierzchnia){
	auto budynek = root.tworzElement(WEZEL_XML_BUDYNEK_INFO);
	UNIT_TEST_ASSERT_NOTNULL(budynek);
	UNIT_TEST_ASSERT_NOTNULL(budynek->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(budynek->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(budynek->tworzAtrybut(ATRYBUT_XML_ADRES_OBRAZKA, obrazek().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(budynek->tworzAtrybut(ATRYBUT_XML_POWIERZCHNIA, std::to_string(powierzchnia()).c_str()));
	UNIT_TEST_ASSERT_TRUE(budynek->ustawTekst(opis().c_str()));
	return budynek;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzObrone(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Tekst& nazwa,
	const STyp::Tekst& obrazek,
	const STyp::Tekst& opis,
	const STyp::Powierzchnia& powierzchnia){
	auto obrona = root.tworzElement(WEZEL_XML_OBRONA_INFO);
	UNIT_TEST_ASSERT_NOTNULL(obrona);
	UNIT_TEST_ASSERT_NOTNULL(obrona->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(obrona->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(obrona->tworzAtrybut(ATRYBUT_XML_ADRES_OBRAZKA, obrazek().c_str()));
	UNIT_TEST_ASSERT_NOTNULL(obrona->tworzAtrybut(ATRYBUT_XML_POWIERZCHNIA, std::to_string(powierzchnia()).c_str()));
	UNIT_TEST_ASSERT_TRUE(obrona->ustawTekst(opis().c_str()));
	return obrona;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzJednostkaAtakujaca(SPar::ParserElement& statek,
	const STyp::Obrazenia& atak,
	const STyp::Obrazenia& obrona,
	const STyp::Obrazenia& tarcza){
	auto jednostka = statek.tworzElement(WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO);
	UNIT_TEST_ASSERT_NOTNULL(jednostka);
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_ATAK, std::to_string(atak()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_PANCERZ, std::to_string(obrona()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_OSLONA, std::to_string(tarcza()).c_str()));
	return jednostka;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzJednostkaLatajaca(SPar::ParserElement& statek,
	const STyp::Identyfikator& idSilnika,
	const STyp::Moc& mocSilnika,
	const STyp::ZuzyciePaliwa& zuzuciePaliwa,
	const STyp::Masa& masaSilnika,
	const STyp::Fluktuacja& sprawnoscSilnika){
	auto jednostka = statek.tworzElement(WEZEL_XML_JEDNOSTKA_LATAJACA_INFO);
	UNIT_TEST_ASSERT_NOTNULL(jednostka);
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_RODZAJ_SILNIKA_ID, std::to_string(idSilnika()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_MOC_SILNIKA, std::to_string(mocSilnika()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_ZUZYCIE_PALIWA, std::to_string(zuzuciePaliwa()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_MASA_SILNIKA, std::to_string(masaSilnika()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(jednostka->tworzAtrybut(ATRYBUT_XML_SPRAWNOSC_SILNIKA, std::to_string(sprawnoscSilnika()).c_str()));
	return jednostka;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzHangar(SPar::ParserElement& statek,
	const STyp::Powierzchnia& powierzchniaHangaru){
	auto hangar = statek.tworzElement(WEZEL_XML_HANGAR_INFO);
	UNIT_TEST_ASSERT_NOTNULL(hangar);
	UNIT_TEST_ASSERT_NOTNULL(hangar->tworzAtrybut(ATRYBUT_XML_POJEMNOSC_MAKSYMALNA, std::to_string(powierzchniaHangaru()).c_str()));
	return hangar;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzLadownia(SPar::ParserElement& statek,
	const STyp::Objetosc& objetoscLadowni){
	auto ladownia = statek.tworzElement(WEZEL_XML_LADOWNIA_INFO);
	UNIT_TEST_ASSERT_NOTNULL(ladownia);
	UNIT_TEST_ASSERT_NOTNULL(ladownia->tworzAtrybut(ATRYBUT_XML_POJEMNOSC_MAKSYMALNA, std::to_string(objetoscLadowni()).c_str()));
	return ladownia;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzKryterium(SPar::ParserElement& obiekt,
	const STyp::Identyfikator& id,
	const STyp::Poziom& poziom){
	auto kryterium = obiekt.tworzElement(WEZEL_XML_KRYTERIUM);
	UNIT_TEST_ASSERT_NOTNULL(kryterium);
	UNIT_TEST_ASSERT_NOTNULL(kryterium->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(kryterium->tworzAtrybut(ATRYBUT_XML_POZIOM, std::to_string(poziom()).c_str()));
	return kryterium;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzKryterium(SPar::ParserElement& obiekt,
	const STyp::Identyfikator& id,
	const STyp::Ilosc& ilosc){
	auto kryterium = obiekt.tworzElement(WEZEL_XML_KRYTERIUM);
	UNIT_TEST_ASSERT_NOTNULL(kryterium);
	UNIT_TEST_ASSERT_NOTNULL(kryterium->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(kryterium->tworzAtrybut(ATRYBUT_XML_ILOSC, std::to_string(ilosc()).c_str()));
	return kryterium;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzZapotrzebowanie(SPar::ParserElement& obiekt,
	const STyp::Identyfikator& id,
	const STyp::Ilosc& ilosc){
	auto zapotrzebowanie = obiekt.tworzElement(WEZEL_XML_ZAPOTRZEBOWANIE);
	UNIT_TEST_ASSERT_NOTNULL(zapotrzebowanie);
	UNIT_TEST_ASSERT_NOTNULL(zapotrzebowanie->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(zapotrzebowanie->tworzAtrybut(ATRYBUT_XML_ILOSC, std::to_string(ilosc()).c_str()));
	return zapotrzebowanie;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzProdukcje(SPar::ParserElement& obiekt,
	const STyp::Identyfikator& id,
	const STyp::Ilosc& ilosc){
	auto produkcja = obiekt.tworzElement(WEZEL_XML_PRODUKCJA);
	UNIT_TEST_ASSERT_NOTNULL(produkcja);
	UNIT_TEST_ASSERT_NOTNULL(produkcja->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(produkcja->tworzAtrybut(ATRYBUT_XML_ILOSC, std::to_string(ilosc()).c_str()));
	return produkcja;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzZmiana(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Tekst& atrybutFor){
	auto zmiana = root.tworzElement(WEZEL_XML_ZMIANA);
	UNIT_TEST_ASSERT_NOTNULL(zmiana);
	UNIT_TEST_ASSERT_NOTNULL(zmiana->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(zmiana->tworzAtrybut(ATRYBUT_XML_FOR, atrybutFor().c_str()));
	return zmiana;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzZmiana(SPar::ParserElement& root,
	const STyp::Identyfikator& id){
	auto zmiana = root.tworzElement(WEZEL_XML_ZMIANA);
	UNIT_TEST_ASSERT_NOTNULL(zmiana);
	UNIT_TEST_ASSERT_NOTNULL(zmiana->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	return zmiana;
}

std::shared_ptr<SPar::ParserElement> TestyUtilsBO::tworzParam(SPar::ParserElement& root,
	const STyp::Identyfikator& id,
	const STyp::Wartosc& atrybutFor){
	auto param = root.tworzElement(WEZEL_XML_PARAM);
	UNIT_TEST_ASSERT_NOTNULL(param);
	UNIT_TEST_ASSERT_NOTNULL(param->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()).c_str()));
	UNIT_TEST_ASSERT_NOTNULL(param->tworzAtrybut(ATRYBUT_XML_WSPOLCZYNNIK, std::to_string(atrybutFor()).c_str()));
	return param;
}
