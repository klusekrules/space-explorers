#pragma once
#include "Szkielet\TestyJednostkowe.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Siec\Serwer\SerwerMulti.h"
#include "Kontroler\Siec\Serwer\BaseSide.h"

class KomunikacjaSieciowaTest :
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(KomunikacjaSieciowaTest);
		DODAJ_TEST(testEcho);
		DODAJ_TEST(testInicjalizacjiLogowania);
		DODAJ_TEST(testPotwierdzajacyLogowanie);
		DODAJ_TEST(testSumyKontrolnej);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void koniecTestow() override;
	void testEcho();
	void testInicjalizacjiLogowania();
	void testPotwierdzajacyLogowanie();
	void testSumyKontrolnej();
	KomunikacjaSieciowaTest() = default;
	virtual ~KomunikacjaSieciowaTest() = default;
private:
	SpEx::SerwerMulti * serwer_ = nullptr;
	SpEx::KlientSideMulti * klient_ = nullptr;
};

