#pragma once
#include "Main.h"
#include "Cennik.h"
#include "Warunek.h"
#include "LoggerInterface.h"

class Wymagania :
	public Cennik,
	public Warunek,
	public LoggerInterface < Wymagania >
{
public:
	typedef LoggerInterface < Wymagania > LogWymagania;
	explicit Wymagania( ticpp::Node* ) throw(WyjatekParseraXML);
	Wymagania( const Wymagania& );
	const Wymagania& operator=( const Wymagania& );
	~Wymagania();

	/**
	* Funkcja sprawdzaj�ca czy zosta�y spe�nione wymagania dla danej planety.
	* \param i - Ilosc element�w. Potrzebne przy sprawdzaniu ceny, aby sprawdzi� czy podana ilo�� element�w spe�nia wymagania.
	* \param p - poziom dla kt�rego maj� zosta� sprawdzone warunki spe�nienia wymaga�.
	* \param idPlanety - Planeta w kontek�cie kt�rej maj� zosta� spawdzone warunki spe�nienia wymaga�.
	*/
	bool czySpelniaWymagania( const Ilosc& i , const Poziom& p, const IdType& idPlanety )const; //TODO: Uzupe�ni� funkjc� o odwo�anie dla konkretnej planety.

	string toString() const override;

};
