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
	* Funkcja sprawdzaj�ca czy zosta�y spe�nione wymagania dla danej planety.
	* \param i - Ilosc element�w. Potrzebne przy sprawdzaniu ceny, aby sprawdzi� czy podana ilo�� element�w spe�nia wymagania.
	*/
	bool czySpelniaWymagania( const Ilosc& i , const PodstawoweParametry& )const;

	string napis() const override;

};
