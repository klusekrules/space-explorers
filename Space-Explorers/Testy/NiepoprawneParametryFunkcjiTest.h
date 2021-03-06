#pragma once
#include "Szkielet\TestyJednostkowe.h"
#include "Model\Planeta.h"

class NiepoprawneParametryFunkcjiTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(NiepoprawneParametryFunkcjiTest);
		DODAJ_TEST(tworzenieWyjatku);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void tworzenieWyjatku();
	NiepoprawneParametryFunkcjiTest(void) = default;
	virtual ~NiepoprawneParametryFunkcjiTest(void) = default;

private:
	std::shared_ptr<SpEx::Planeta> planeta;
};

