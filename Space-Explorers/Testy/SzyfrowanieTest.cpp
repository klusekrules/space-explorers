#include "SzyfrowanieTest.h"
#include "Algorytmy\VMPC_MAC.h"
#include "Algorytmy\SHA3.h"
#include "zlib.h"
#include "Kontroler\Siec\Szyfrowanie.h"
#include "Kontroler\Siec\Kompresja.h"

void SzyfrowanieTest::startTestow(){
	fp1_ = fopen("test1.dat", "ab+");
	fp2_ = fopen("test2.dat", "ab+");
	fp3_ = fopen("test3.dat", "ab+");
	fp4_ = fopen("test4.dat", "ab+");
	fp5_ = fopen("test5.dat", "ab+");
	fp6_ = fopen("test6.dat", "ab+");
}

void SzyfrowanieTest::koniecTestow(){
	fclose(fp1_);
	fclose(fp2_);
	fclose(fp3_);
	fclose(fp4_);
	fclose(fp5_);
	fclose(fp6_);

	remove("test1.dat");
	remove("test2.dat");
	remove("test3.dat");
	remove("test4.dat");
	remove("test5.dat");
	remove("test6.dat");
}

void SzyfrowanieTest::klasaSzyfrowanieTest(){
	std::string klucz("klucz");
	std::string dane("dane do zaszyfrowania");
	std::string kopiaDanych("dane do zaszyfrowania");
	SpEx::Szyfrowanie szyfrowanie(klucz, dane);
	UNIT_TEST_ASSERT_EQUAL(ERROR_SUCCESS, szyfrowanie.szyfrowanie());
	UNIT_TEST_ASSERT_NOTEQUAL(dane, kopiaDanych);
	UNIT_TEST_ASSERT_EQUAL(ERROR_SUCCESS, szyfrowanie.deszyfrowanie());
	UNIT_TEST_ASSERT_EQUAL(dane, kopiaDanych);
}

void SzyfrowanieTest::klasaSzyfrowanieTestPlik(){
	std::string klucz("klucz");
	std::string dane("dane do zaszyfrowania");
	fwrite(dane.data(), sizeof(std::string::value_type), dane.size(), fp4_);
	std::string kopia;
	kopia.resize(dane.size(), 0);
	fseek(fp4_, 0, SEEK_SET);
	SpEx::Szyfrowanie szyfrowanie(klucz, fp4_, fp5_);
	UNIT_TEST_ASSERT_EQUAL(ERROR_SUCCESS, szyfrowanie.szyfrowanie());
	fseek(fp5_, 0, SEEK_SET);
	SpEx::Szyfrowanie szyfrowanie2(klucz,fp5_, fp6_);
	UNIT_TEST_ASSERT_EQUAL(ERROR_SUCCESS, szyfrowanie2.deszyfrowanie());
	fseek(fp6_, 0, SEEK_SET);
	fread(&kopia[0], sizeof(std::string::value_type), kopia.size(), fp6_);
	UNIT_TEST_ASSERT_EQUAL(kopia, dane);
}

void SzyfrowanieTest::klasaKompresjaTest(){
	std::string wiadomoscOryginalna("Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc,");
	std::string out; 
	std::string out2;
	SpEx::Kompresja kompresja(wiadomoscOryginalna, out);
	UNIT_TEST_ASSERT_EQUAL(ERROR_SUCCESS, kompresja.kompresja());
	SpEx::Kompresja kompresja2(out, out2);
	UNIT_TEST_ASSERT_EQUAL(ERROR_SUCCESS, kompresja2.dekompresja());
	UNIT_TEST_ASSERT_EQUAL(wiadomoscOryginalna, out2);
}

void SzyfrowanieTest::klasaKompresjaTestPlik(){
	std::string wiadomoscOryginalna("Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc,");
	fwrite(wiadomoscOryginalna.data(),sizeof(std::string::value_type),wiadomoscOryginalna.size(),fp1_);
	std::string kopia;
	kopia.resize(wiadomoscOryginalna.size(),0);
	fseek(fp1_, 0, SEEK_SET);
	SpEx::Kompresja kompresja(fp1_, fp2_);
	UNIT_TEST_ASSERT_EQUAL(ERROR_SUCCESS, kompresja.kompresja());
	fseek(fp2_, 0, SEEK_SET);
	SpEx::Kompresja kompresja2(fp2_, fp3_);
	UNIT_TEST_ASSERT_EQUAL(ERROR_SUCCESS, kompresja2.dekompresja());
	fseek(fp3_, 0, SEEK_SET);
	fread(&kopia[0], sizeof(std::string::value_type), kopia.size(), fp3_);
	UNIT_TEST_ASSERT_EQUAL(kopia, wiadomoscOryginalna);
}

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
	std::string wiadomoscOryginalna("Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc");
	
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