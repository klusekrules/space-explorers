#include "KomunikacjaSieciowaTest.h"
#include "EchoRPC.h"
#include "InicjujLogowanieRPC.h"
#include "PotwierdzLogowanieRPC.h"
#include "StaleRPC.h"
#include "SHA3.h"
#include "Fabrykator.h"

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
		std::string echo("Do Serwera");
		ptr->dodajParametr("Echo", echo);
		UNIT_TEST_ASSERT_EQUAL(ptr->wykonajMetode(), RPC_OK);
	}
}

void KomunikacjaSieciowaTest::testInicjalizacjiLogowania(){
	UNIT_TEST_ASSERT_NOTNULL(serwer_);
	UNIT_TEST_ASSERT_NOTNULL(klient_);

	auto ptr = SpEx::Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC<SpEx::InicjujLogowanieRPC>(*klient_);
	if (ptr){
		std::string haslo("haslo");
		SHA3 sha3(haslo);
		haslo = sha3.pobierzNapis();
		std::string login("Daniel");
		ptr->dodajParametr("Login", login);
		ptr->dodajParametr("Hash", haslo);
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

void KomunikacjaSieciowaTest::koniecTestow() {

	klient_->zamknijPolaczenie();
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