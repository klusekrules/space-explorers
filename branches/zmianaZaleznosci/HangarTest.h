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
	Gra* gra;
	shared_ptr<Statek> statekTransportowy;
	shared_ptr<Statek> statekTransportowyDuzy;
	shared_ptr<Statek> mysliwiec;
	shared_ptr<Statek> mysliwiecDrugi;
};
