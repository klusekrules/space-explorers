/*

	Autor: Daniel Wojdak
	Wersja: 0.0.0.1
	Plik: Ladownia.h
	Opis: Klasa zajmuj¹ca siê przechowywaniem surowców na statkach
	
*/

#pragma once
#include "Main.h"
#include "Biblioteki.h"
#include "NieznalezionoObiektu.h"
#include "NiepoprawnaIloscObiektow.h"
#include "NiepoprawneParametryFunkcji.h"
#include "BladDzieleniaLadowni.h"
#include "Objetosc.h"
#include "Klucz.h"
#include "Ilosc.h"
#include "Obiekt.h"
#include "Fluktuacja.h"
#include "Masa.h"
#include "ObiektList.hpp"

class LadowniaInfo;

class Ladownia:
	public LoggerInterface<Ladownia>
{
public:
	typedef Obiekt Item;
	typedef ObiektList< Item > Zbiornik;
	typedef list < Klucz > ListaKluczy;

	Ladownia( const LadowniaInfo& );
	Ladownia( Zbiornik& , const LadowniaInfo& );
	virtual ~Ladownia( );	
	
	Fluktuacja WolneMiejsce() const;

	Ilosc SprawdzIloscObiektow( const Klucz& ) const;
	
	bool DodajObiektDoLadowni( const Item& );

	Item& PobierzObiekt( const Klucz& , const Ilosc& ) throw ( NieznalezionoObiektu, NiepoprawnaIloscObiektow );

	ListaKluczy PobierzListeIdObiektow() const;

	const Zbiornik& getPrzewozoneObiekty() const;

	Zbiornik* PodzielLadownie( const Objetosc&, const Objetosc& ) throw( BladDzieleniaLadowni, NiepoprawneParametryFunkcji  );

	const Objetosc& getZajeteMiejsce() const;

	virtual Objetosc getPojemnoscMax() const;

	string toString() const override;

protected:

	void przeliczZajeteMiejsce();
	Masa getMasaZawartosciLadowni();

	Zbiornik obiekty;
	Objetosc zajete;

	const LadowniaInfo& ladowniaInfo;
};

