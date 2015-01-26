#include "SzyfrowanieTest.h"
#include "VMPC_MAC.h"
#include "SHA3.h"
#include "zlib.h"

void SzyfrowanieTest::szyfrowanieTest()
{
	VMPC_MAC szyfr;
	SHA3 klucz("haslo");
	SHA3 wektor("data");
	std::string wiadomoscOrg("Moja wiadomosc");
	std::string wiadomosc;

	wiadomosc = wiadomoscOrg;

	szyfr.InitKey(klucz.pobierzKontener(),wektor.pobierzKontener());
	szyfr.EncryptMAC(wiadomosc);
	auto& mac = szyfr.OutputMAC();


	VMPC_MAC deSzyfr;
	deSzyfr.InitKey(klucz.pobierzKontener(), wektor.pobierzKontener());
	deSzyfr.DecryptMAC(wiadomosc);
	auto& macDe = deSzyfr.OutputMAC();

	UNIT_TEST_ASSERT_EQUAL(mac, macDe);
	UNIT_TEST_ASSERT_EQUAL(wiadomosc, wiadomoscOrg);

}

void SzyfrowanieTest::kompresjaTest(){
	std::string wiadomoscOrg("Moja wiadomosc , Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc, Moja wiadomosc");
	
	auto bound = compressBound(wiadomoscOrg.size());
	uLongf after = bound;
	std::vector<Bytef> out;
	out.resize(after,0);
	compress((Bytef*)out.data(),&after , (const Bytef*)wiadomoscOrg.data(), wiadomoscOrg.size());
	

	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, std::to_string(bound));

	uLongf unSize = wiadomoscOrg.size();
	std::string uncompres;
	uncompres.resize(unSize, 0);
	uncompress((Bytef*)uncompres.data(), &unSize, out.data(), after);

	UNIT_TEST_ASSERT_EQUAL(uncompres, wiadomoscOrg);
}


REJESTRUJ_PACZKE_TESTOW(SzyfrowanieTest);