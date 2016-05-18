#pragma once
#include "Szkielet\TestyJednostkowe.h"
#include "Kontroler\Aplikacja.h"

class SzyfrowanieTest :
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(SzyfrowanieTest);
		DODAJ_TEST(szyfrowanieTest);
		DODAJ_TEST(klasaSzyfrowanieTest);
		DODAJ_TEST(klasaSzyfrowanieTestPlik);
		DODAJ_TEST(kompresjaTest);
		DODAJ_TEST(klasaKompresjaTest);
		DODAJ_TEST(klasaKompresjaTestPlik);
		DODAJ_TEST(kompresjaOrazSzyfrowanieTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	SzyfrowanieTest() = default;
	void startTestow() override;
	void koniecTestow() override;
	void klasaSzyfrowanieTest();
	void klasaSzyfrowanieTestPlik();
	void klasaKompresjaTest();
	void klasaKompresjaTestPlik();
	void szyfrowanieTest();
	void kompresjaTest();
	void kompresjaOrazSzyfrowanieTest();
	virtual ~SzyfrowanieTest() = default;
private:
	FILE *fp1_;
	FILE *fp2_;
	FILE *fp3_;
	FILE *fp4_;
	FILE *fp5_;
	FILE *fp6_;
};

