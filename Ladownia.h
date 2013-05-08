/*

	Autor: Daniel Wojdak
	Wersja: 0.0.0.1
	Plik: Ladownia.h
	Opis: Klasa zajmuj¹ca siê przechowywaniem surowców na statkach
	
*/

#pragma once
#include "Main.h"
#include "Biblioteki.h"
#include "BaseTypes\NieznalezionoObiektu.h"
#include "BaseTypes\NiepoprawnaIloscObiektow.h"
#include "BaseTypes\NiepoprawneParametryFunkcji.h"
#include "BaseTypes\BladDzieleniaLadowni.h"
#include "BaseTypes\Objetosc.h"
#include "BaseTypes\Klucz.h"
#include "BaseTypes\Ilosc.h"
#include "Obiekt.h"
#include "BaseTypes\Fluktuacja.h"
#include "BaseTypes\Masa.h"
#include "ObiektList.hpp"

class Surowce;
class LadowniaInfo;
class Statek;

class Ladownia:
	virtual public LoggerInterface
{
public:
	typedef Obiekt Item;
	typedef ObiektList< Item > Zbiornik;
	typedef list < Klucz > ListaKluczy;

	Ladownia( const LadowniaInfo& );
	Ladownia( Zbiornik& , const LadowniaInfo& );
	virtual ~Ladownia( );	
	
	virtual Fluktuacja WolneMiejsce( const Poziom& pz ) const;

	Ilosc SprawdzIloscObiektow( const Klucz& ) const;
	
	virtual bool DodajObiektDoLadowni( const Item& , const Poziom& pz );

	Item& PobierzObiekt( const Klucz& , const Ilosc& ) throw ( NieznalezionoObiektu, NiepoprawnaIloscObiektow );

	ListaKluczy PobierzListeIdObiektow() const;

	const Zbiornik& getPrzewozoneObiekty() const;

	Zbiornik* PodzielLadownie( const Objetosc&, const Objetosc& ) throw( BladDzieleniaLadowni, NiepoprawneParametryFunkcji  );

	const Objetosc& getZajeteMiejsce() const;

	virtual Objetosc getPojemnoscMax( const Poziom& pz ) const;

	bool czMoznaDodacDoLadownii( const Statek& c ) const;

	bool czMoznaDodacDoLadownii( const Surowce& c ) const;

	string toString() const override;

protected:

	void przeliczZajeteMiejsce();
	Masa getMasaZawartosciLadowni();

	Zbiornik obiekty;
	Objetosc zajete;

	const LadowniaInfo& ladowniaInfo;
};

