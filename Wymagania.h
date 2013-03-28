#pragma once
#include "Main.h"
#include "Cennik.h"
#include "Warunek.h"
#include "LoggerInterface.h"

class Wymagania :
	public Cennik,
	public LoggerInterface < Wymagania >
{
public:
	typedef LoggerInterface < Wymagania > LogWymagania;
	explicit Wymagania( ticpp::Node* );
	Wymagania( const Cennik& , Warunek* );
	Wymagania( const Wymagania& );
	const Wymagania& operator=( const Wymagania& );
	~Wymagania();

	/**
	* Funkcja sprawdzaj�ca czy zosta�y spe�nione wymagania dla danej planety.
	* \param i - Ilosc element�w. Potrzebne przy sprawdzaniu ceny, aby sprawdzi� czy podana ilo�� element�w spe�nia wymagania.
	*/
	bool sprawdzWymagania( const Ilosc& i , const Poziom& p, const IdType& idPlanety )const; //TODO: Uzupe�ni� funkjc� o odwo�anie dla konkretnej planety.

	string toString() const override;

private:
	Warunek* wymogi;
};
