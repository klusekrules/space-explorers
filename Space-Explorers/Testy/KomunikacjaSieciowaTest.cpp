#include "KomunikacjaSieciowaTest.h"
#include "Kontroler\Siec\RPC\EchoRPC.h"
#include "Kontroler\Siec\RPC\InicjujLogowanieRPC.h"
#include "Kontroler\Siec\RPC\PotwierdzLogowanieRPC.h"
#include "Kontroler\Siec\RPC\StaleRPC.h"
#include "Algorytmy\SHA3.h"
#include "Algorytmy\Hex.h"
#include "Kontroler\Zarzadca\Fabrykator.h"
#include "Kontroler\Siec\RPC\SprawdzSumyKontrolneRPC.h"

void KomunikacjaSieciowaTest::startTestow() {
	if (serwer_ != nullptr)
		delete serwer_;
	if (klient_ != nullptr)
		delete klient_;

	serwer_ = new SpEx::Serwer(SpEx::Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji());
	klient_ = new SpEx::Klient(SpEx::Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji());

	serwer_->odblokuj();
	klient_->odblokuj();
}

void KomunikacjaSieciowaTest::testEcho(){
	UNIT_TEST_ASSERT_NOTNULL(serwer_);
	UNIT_TEST_ASSERT_NOTNULL(klient_);

	auto ptr = SpEx::Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC<SpEx::EchoRPC>(*klient_);
	if (ptr){
		ptr->obiektParametrow()["Echo"] = "Do Serwera";
		UNIT_TEST_ASSERT_EQUAL(ptr->wykonajMetode(), RPC_OK);
		// Sprawdzenie czy parametry zachowuj¹ siê jak referencje.
		UNIT_TEST_ASSERT_EQUAL(ptr->obiektParametrow()["Echo"],"Do klienta"); 
	}
}

void KomunikacjaSieciowaTest::testInicjalizacjiLogowania(){
	UNIT_TEST_ASSERT_NOTNULL(serwer_);
	UNIT_TEST_ASSERT_NOTNULL(klient_);

	auto ptr = SpEx::Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC<SpEx::InicjujLogowanieRPC>(*klient_);
	if (ptr){
		std::string haslo("haslo");
		SHA3 sha3(haslo);
		haslo = sha3.pobierzNapis<Hex>();
		std::string login("Daniel");
		ptr->obiektParametrow()["Login"] = login;
		ptr->obiektParametrow()["Hash"] = haslo;
		UNIT_TEST_ASSERT_EQUAL(ptr->wykonajMetode(), RPC_OK);
	}
}

void KomunikacjaSieciowaTest::testPotwierdzajacyLogowanie(){
	UNIT_TEST_ASSERT_NOTNULL(serwer_);
	UNIT_TEST_ASSERT_NOTNULL(klient_);

	auto ptr = SpEx::Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC<SpEx::PotwierdzLogowanieRPC>(*klient_);
	if (ptr){
		UNIT_TEST_ASSERT_EQUAL(ptr->wykonajMetode(), RPC_OK);
	}
}

void KomunikacjaSieciowaTest::testSumyKontrolnej(){
	UNIT_TEST_ASSERT_NOTNULL(serwer_);
	UNIT_TEST_ASSERT_NOTNULL(klient_);

	auto ptr = SpEx::Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC<SpEx::SprawdzSumyKontrolneRPC>(*klient_);
	if (ptr){
		UNIT_TEST_ASSERT_EQUAL(ptr->wykonajMetode(), RPC_OK);
	}
}

void KomunikacjaSieciowaTest::koniecTestow() {

	klient_->zakoncz();
	klient_->czekajNaZakonczenie();
	serwer_->zakoncz();
	serwer_->czekajNaZakonczenie();

	if (serwer_ != nullptr)
		delete serwer_;
	serwer_ = nullptr;
	if (klient_ != nullptr)
		delete klient_;
	klient_ = nullptr;
}


REJESTRUJ_PACZKE_TESTOW(KomunikacjaSieciowaTest);