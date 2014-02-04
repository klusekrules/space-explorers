#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class HangarTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(HangarTest);
		DODAJ_TEST(podstawowyTest);
		DODAJ_TEST(oproznianieHangaru);
		DODAJ_TEST(dzielenieHangaru);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void podstawowyTest();
	void oproznianieHangaru();
	void dzielenieHangaru();
	HangarTest(void);
	virtual ~HangarTest(void);

private:
	SpEx::Gra* gra;
	std::shared_ptr<SpEx::Statek> statekTransportowy;
	std::shared_ptr<SpEx::Statek> statekTransportowyDuzy;
	std::shared_ptr<SpEx::Statek> mysliwiec;
	std::shared_ptr<SpEx::Statek> mysliwiecDrugi;
};
