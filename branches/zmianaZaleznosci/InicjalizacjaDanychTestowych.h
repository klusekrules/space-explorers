#pragma once
#include "TestyJednostkowe.h"

class InicjalizacjaDanychTestowych : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(InicjalizacjaDanychTestowych);
		DODAJ_TEST(zaladujDane);
	TWORZ_PACZKE_TESTOW_END();
public:
	
	void zaladujDane();
	InicjalizacjaDanychTestowych() = default;
	virtual ~InicjalizacjaDanychTestowych() = default;

};
