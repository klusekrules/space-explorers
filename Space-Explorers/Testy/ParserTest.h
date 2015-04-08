#pragma once
#include "Szkielet\TestyJednostkowe.h"


class ParserTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(ParserTest);
		DODAJ_TEST(tworzPlik);
		DODAJ_TEST(zapiszPlik);
		DODAJ_TEST(odczytajPlik);
		DODAJ_TEST(usunPlik);
	TWORZ_PACZKE_TESTOW_END();
public:
	ParserTest() = default;
	void tworzPlik();
	void zapiszPlik();
	void odczytajPlik();
	void usunPlik();
	virtual ~ParserTest() = default;
private:

};

