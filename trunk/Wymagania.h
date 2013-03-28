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
	* Funkcja sprawdzaj¹ca czy zosta³y spe³nione wymagania dla danej planety.
	* \param i - Ilosc elementów. Potrzebne przy sprawdzaniu ceny, aby sprawdziæ czy podana iloœæ elementów spe³nia wymagania.
	*/
	bool sprawdzWymagania( const Ilosc& i , const Poziom& p, const IdType& idPlanety )const; //TODO: Uzupe³niæ funkjcê o odwo³anie dla konkretnej planety.

	string toString() const override;

private:
	Warunek* wymogi;
};
