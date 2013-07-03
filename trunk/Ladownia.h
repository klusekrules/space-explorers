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
#include "PodstawoweParametry.h"

class Surowce;
class LadowniaInfo;
class Statek;

class Ladownia:
	virtual public PodstawoweParametry,
	virtual public LoggerInterface
{
public:
	typedef Obiekt Item;
	typedef ObiektList< Item > Zbiornik;
	typedef list < Klucz > ListaKluczy;

	Ladownia( const Poziom&, const IdType&, const LadowniaInfo& );
	Ladownia( const PodstawoweParametry&, const LadowniaInfo& );	
	
	virtual Fluktuacja WolneMiejsce() const;

	Ilosc SprawdzIloscObiektow( const Klucz& ) const;
	
	virtual bool DodajObiektDoLadowni( const Item& );

	Item& PobierzObiekt( const Klucz& , const Ilosc& ) throw ( NieznalezionoObiektu, NiepoprawnaIloscObiektow );

	ListaKluczy PobierzListeIdObiektow() const;

	const Zbiornik& getPrzewozoneObiekty() const;

	Zbiornik* PodzielLadownie( const Objetosc&, const Objetosc& ) throw( BladDzieleniaLadowni, NiepoprawneParametryFunkcji  );

	const Objetosc& getZajeteMiejsce() const;

	virtual Objetosc getPojemnoscMax() const;

	bool czMoznaDodacDoLadownii( const Statek& c ) const;

	bool czMoznaDodacDoLadownii( const Surowce& c ) const;

	string toString() const override;

protected:

	void przeliczZajeteMiejsce();
	Masa getMasaZawartosciLadowni()const;

	Zbiornik obiekty;
	Objetosc zajete;
private:
	const LadowniaInfo& ladowniaInfo;
};

