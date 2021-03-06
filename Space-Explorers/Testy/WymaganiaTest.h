#pragma once
#include "Szkielet\TestyJednostkowe.h"
#include "Model\Planeta.h"

class WymaganiaTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(WymaganiaTest);
		DODAJ_TEST(sprawdzenieKosztow);
		DODAJ_TEST(czyMoznaWybudowacTest);
		DODAJ_TEST(czasBudowy);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void sprawdzenieKosztow();
	void czyMoznaWybudowacTest();
	void czasBudowy();
	WymaganiaTest(void) = default;
	virtual ~WymaganiaTest(void) = default;
private:
	const SpEx::Statek* a;
	std::shared_ptr <SpEx::Planeta> planeta;
};

