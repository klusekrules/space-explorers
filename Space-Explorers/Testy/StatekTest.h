#pragma once
#include "Szkielet\TestyJednostkowe.h"
#include "Model\Planeta.h"

class StatekTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(StatekTest);
		DODAJ_TEST(Issue42Test);
		DODAJ_TEST(FlotaTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void Issue42Test();
	void FlotaTest();
	StatekTest(void) = default;
	virtual ~StatekTest(void) = default;
private:
	const SpEx::Statek* a;
	const SpEx::Statek* b;
	const SpEx::Statek* c;
	const SpEx::Statek* d;
	std::shared_ptr<SpEx::Planeta> planeta;
};

