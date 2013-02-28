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

class Ladownia:
	public LoggerInterface<Ladownia>
{
public:
	typedef Obiekt Item;
	typedef ObiektList< Item > Zbiornik;
	typedef list < Klucz > ListaKluczy;

	Ladownia( );
	Ladownia( const Objetosc& );
	Ladownia( const Objetosc& , const Fluktuacja& );
	Ladownia( const Ladownia& );	
	virtual ~Ladownia( );	
	
	Fluktuacja WolneMiejsce() const;
	virtual Objetosc MaksymalnaPojemnosc() const;
	Ilosc SprawdzIloscObiektow( const Klucz& ) const;
	
	bool DodajObiektDoLadowni( const Item& );
	Item& PobierzObiekt( const Klucz& , const Ilosc& ) throw ( NieznalezionoObiektu, NiepoprawnaIloscObiektow );
	ListaKluczy PobierzListeIdObiektow() const;

	Zbiornik getPrzewozoneObiekty() const;
	void setPrzeworzoneObiekty( const Zbiornik& );
	Zbiornik* PodzielLadownie( const Objetosc&, const Objetosc& ) throw( BladDzieleniaLadowni, NiepoprawneParametryFunkcji  );

	Objetosc getZajeteMiejsce() const;
	void setZajeteMiejsce( const Objetosc& );

	Objetosc getPojemnoscMax() const;
	void setPojemnoscMax( const Objetosc& );

	Fluktuacja getPrzyrostPojemnoscMax() const;
	void setPrzyrostPojemnoscMax( const Fluktuacja& );

	string toString() const override;

protected:

	void przeliczZajeteMiejsce();
	Masa getMasaZawartosciLadowni();

	Zbiornik obiekty;
	Objetosc zajete;
	Objetosc pojemnoscMax;
	Fluktuacja przyrostPojemnoscMax;
};

