#pragma once
#include "TestyJednostkowe.h"

class InicjalizacjaDanychTestowych : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(InicjalizacjaDanychTestowych);
		DODAJ_TEST(zaladujDane);
		DODAJ_TEST(generujDane);
	TWORZ_PACZKE_TESTOW_END();
public:
	void zaladujDane();
	void generujDane();
	InicjalizacjaDanychTestowych();
	virtual ~InicjalizacjaDanychTestowych();
};
