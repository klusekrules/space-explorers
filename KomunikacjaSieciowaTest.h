#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"
#include "Serwer.h"
#include "Klient.h"

class KomunikacjaSieciowaTest :
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(KomunikacjaSieciowaTest);
		DODAJ_TEST(testEcho);
		DODAJ_TEST(testInicjalizacjiLogowania);
		DODAJ_TEST(testPotwierdzajacyLogowanie);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void koniecTestow() override;
	void testEcho();
	void testInicjalizacjiLogowania();
	void testPotwierdzajacyLogowanie();
	KomunikacjaSieciowaTest() = default;
	virtual ~KomunikacjaSieciowaTest() = default;
private:
	SpEx::Serwer * serwer_ = nullptr;
	SpEx::Klient * klient_ = nullptr;
};

