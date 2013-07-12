#pragma once
#include "Main.h"
#include "Cennik.h"
#include "Warunek.h"
#include "Logger\LoggerInterface.h"
#include "PodstawoweParametry.h"

class Wymagania :
	public Cennik,
	public Warunek,
	virtual public LoggerInterface
{
public:
	explicit Wymagania( TiXmlElement* ) throw(WyjatekParseraXML);

	/**
	* Funkcja sprawdzaj¹ca czy zosta³y spe³nione wymagania dla danej planety.
	* \param i - Ilosc elementów. Potrzebne przy sprawdzaniu ceny, aby sprawdziæ czy podana iloœæ elementów spe³nia wymagania.
	*/
	bool czySpelniaWymagania( const Ilosc& i , const PodstawoweParametry& )const;

	string napis() const override;

};
