#pragma once
#include "Szkielet\TestyJednostkowe.h"
#include "Kontroler\Gra.h"
#include "Model\Statek.h"

class LadowniaTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(LadowniaTest);
		DODAJ_TEST(podstawowyTest);
		DODAJ_TEST(oproznianieLadowni);
		DODAJ_TEST(dzielenieLadowni);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void podstawowyTest();
	void oproznianieLadowni();
	void dzielenieLadowni();
	LadowniaTest(void) = default;
	virtual ~LadowniaTest(void) = default;

private:
	SpEx::Gra* gra;
	std::shared_ptr<SpEx::Statek> statekTransportowy;
	std::shared_ptr<SpEx::Statek> statekTransportowyDuzy;
	std::shared_ptr<SpEx::Surowce> metal;
	std::shared_ptr<SpEx::Surowce> energia;
	std::shared_ptr<SpEx::Surowce> krysztal;
};

