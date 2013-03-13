#pragma once
#include "Main.h"
#include "CenaInterfejs.h"
#include "Warunek.h"
#include "LoggerInterface.h"

class Wymagania :
	public LoggerInterface < Wymagania >
{
public:
	Wymagania( );
	Wymagania( CenaInterfejs* , Warunek* );
	Wymagania( const Wymagania& );
	const Wymagania& operator=( const Wymagania& );
	~Wymagania();

	/**
	* Funkcja sprawdzaj�ca czy zosta�y spe�nione wymagania dla danej planety.
	* \param i - Ilosc element�w. Potrzebne przy sprawdzaniu ceny, aby sprawdzi� czy podana ilo�� element�w spe�nia wymagania.
	*/
	bool sprawdzWymagania( const Ilosc& i , const IdType& idPlanety )const; //TODO: Uzupe�ni� funkjc� o odwo�anie dla konkretnej planety.

	string toString() const override;

private:

	CenaInterfejs* koszty;
	Warunek* wymogi;
};
