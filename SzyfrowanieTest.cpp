#include "SzyfrowanieTest.h"
#include "VMPC_MAC.h"
#include "SHA3.h"

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


REJESTRUJ_PACZKE_TESTOW(SzyfrowanieTest);