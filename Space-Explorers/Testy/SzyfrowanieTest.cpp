#include "SzyfrowanieTest.h"
#include "Algorytmy\VMPC_MAC.h"
#include "Algorytmy\SHA3.h"
#include "zlib.h"

void SzyfrowanieTest::szyfrowanieTest()
{
	VMPC_MAC szyfr;
	SHA3 klucz("haslo");
	SHA3 wektor("data");
	std::string wiadomoscOryginalna("Moja wiadomosc");
	std::string wiadomosc;

	wiadomosc = wiadomoscOryginalna;

	szyfr.InitKey(klucz.pobierzKontener(),wektor.pobierzKontener());
	szyfr.EncryptMAC(wiadomosc);
	auto& mac = szyfr.OutputMAC();


	VMPC_MAC deSzyfr;
	deSzyfr.InitKey(klucz.pobierzKontener(), wektor.pobierzKontener());
	deSzyfr.DecryptMAC(wiadomosc);
	auto& macDe = deSzyfr.OutputMAC();

	UNIT_TEST_ASSERT_EQUAL(mac, macDe);
	UNIT_TEST_ASSERT_EQUAL(wiadomosc, wiadomoscOryginalna);

}

void SzyfrowanieTest::kompresjaTest(){
	std::string wiadomoscOryginalna("Moja wiadomosc , Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc");
	
	auto bound = compressBound(wiadomoscOryginalna.size());
	uLongf after = bound;
	std::vector<Bytef> out;
	out.resize(after,0);
	compress((Bytef*)out.data(), &after, (const Bytef*)wiadomoscOryginalna.data(), wiadomoscOryginalna.size());
	

	SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::to_string(bound));

	uLongf unSize = wiadomoscOryginalna.size();
	std::string uncompres;
	uncompres.resize(unSize, 0);
	uncompress((Bytef*)uncompres.data(), &unSize, out.data(), after);

	UNIT_TEST_ASSERT_EQUAL(uncompres, wiadomoscOryginalna);
}

void SzyfrowanieTest::kompresjaOrazSzyfrowanieTest(){
	std::string wiadomoscOryginalna("Moja wiadomosc , Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc");
	std::string wiadomoscOtrzymana;
	SHA3 klucz("haslo");
	SHA3 wektor("data");
	VMPC_MAC szyfrowanie;
	VMPC_MAC deszyfrowanie;

	//Obliczanie maksymalnego rozmiaru bufora do przechowania skompresowanej wiadomoœci
	auto bound = compressBound(wiadomoscOryginalna.size());
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::to_string(bound));

	//Kompresja wiadomoœci
	uLongf after = bound;
	std::string out;
	out.resize(after, 0);
	compress((Bytef*)out.data(), &after, (const Bytef*)wiadomoscOryginalna.data(), wiadomoscOryginalna.size());
	out.resize(after);

	SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::to_string(after));

	//Szyfrowanie wiadomoœci
	szyfrowanie.InitKey(klucz.pobierzKontener(), wektor.pobierzKontener());
	szyfrowanie.EncryptMAC(out);
	auto& sumaKontrolnaSzyfrowania = szyfrowanie.OutputMAC();

	//Deszyfrowywanie wiadomoœci
	deszyfrowanie.InitKey(klucz.pobierzKontener(), wektor.pobierzKontener());
	deszyfrowanie.DecryptMAC(out);
	auto& sumaKontrolnaDeszyfrowania = deszyfrowanie.OutputMAC();

	UNIT_TEST_ASSERT_EQUAL(sumaKontrolnaSzyfrowania, sumaKontrolnaDeszyfrowania);
	
	//Dekompresja wiadomoœci
	uLongf unSize = wiadomoscOryginalna.size();
	wiadomoscOtrzymana.resize(unSize, 0);
	uncompress((Bytef*)wiadomoscOtrzymana.data(), &unSize, (const Bytef*)out.data(), after);

	UNIT_TEST_ASSERT_EQUAL(wiadomoscOtrzymana, wiadomoscOryginalna);
}

REJESTRUJ_PACZKE_TESTOW(SzyfrowanieTest);