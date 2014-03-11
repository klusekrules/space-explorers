#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class BudynekTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(BudynekTest);
		DODAJ_TEST(podstawowyTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void podstawowyTest();
	BudynekTest(void) = default;
	virtual ~BudynekTest(void) = default;
private:
	const SpEx::Budynek* a;
	const SpEx::Budynek* b;
	const SpEx::Budynek* c;
	std::shared_ptr<SpEx::Planeta> planeta;
};

