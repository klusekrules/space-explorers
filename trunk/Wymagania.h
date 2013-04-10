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
	* Funkcja sprawdzaj¹ca czy zosta³y spe³nione wymagania dla danej planety.
	* \param i - Ilosc elementów. Potrzebne przy sprawdzaniu ceny, aby sprawdziæ czy podana iloœæ elementów spe³nia wymagania.
	* \param p - poziom dla którego maj¹ zostaæ sprawdzone warunki spe³nienia wymagañ.
	* \param idPlanety - Planeta w kontekœcie której maj¹ zostaæ spawdzone warunki spe³nienia wymagañ.
	*/
	bool czySpelniaWymagania( const Ilosc& i , const Poziom& p, const IdType& idPlanety )const; //TODO: Uzupe³niæ funkjcê o odwo³anie dla konkretnej planety.

	string toString() const override;

};
