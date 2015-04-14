#pragma once
#include "Szkielet\TestyJednostkowe.h"
#include "Model\Planeta.h"

class TechnologiaTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(TechnologiaTest);
		DODAJ_TEST(podstawowyTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void podstawowyTest();
	TechnologiaTest(void) = default;
	virtual ~TechnologiaTest(void) = default;
private:
	const SpEx::Technologia* a;
	const SpEx::Technologia* b;
	std::shared_ptr<SpEx::Planeta> planeta;
};

