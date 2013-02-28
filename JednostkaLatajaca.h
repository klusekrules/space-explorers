#pragma once
#include "Main.h"
#include "Fluktuacja.h"
#include "Predkosc.h"
#include "Dystans.h"
#include "JednostkaLatajacaInfo.h"


/**
* Klasa implementuj�ca interfejs, s�u��cy do lot�w statk�w kosmiczych.
* Pozwala na wyliczenie wszystkich parametr�w lotu.
*/
class JednostkaLatajaca :
	public LoggerInterface < JednostkaLatajaca >
{
public:
	/**
	* Konstruktor domy�lny
	*/
	JednostkaLatajaca();

	/**
	* Konstruktor parametryczny
	* \param jInfo - Wskazanie na klas� opisuj�c�
	* \param mocSilnika - Procentowa warto�� mocy w klasie opisuj�cej. Domy�lnie 1.0 
	* \param zuzyciePaliwa - Procentowa warto�� zu�ycia paliwa w klasie opisuj�cej. Domy�lnie 1.0 
	*/
	JednostkaLatajaca( JednostkaLatajacaInfo * jInfo , const Fluktuacja& mocSilnika , const Fluktuacja& zuzyciePaliwa );
	
	/**
	* Domy�lny konstruktor kopiuj�cy
	* \param a - Obiekt na podstawie kt�rego zostanie utworzona kopia.
	*/
	JednostkaLatajaca( const JednostkaLatajaca& a );
	
	/**
	* Destruktor domy�lny
	*/
	virtual ~JednostkaLatajaca();

	/**
	* Funkcja wyliczaj�ca zy�ycie paliwa przez statek na okre�lonym dystansie i przy okre�lonej pr�ko�ci.
	* \param d - Dystans, na kt�rym ma porusza� si� statek.
	* \param p - Pr�dko��, kt�r� ma lecie� statek.
	* \return Paliwo zu�yte przez statek.
	*/
	ZuzyciePaliwa WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const;

	/**
	* Maksymalna pr�ko�� jak� mo�e rozwin�� statek.
	* \return pr�dko�� jak� mo�e rozwin�� statek.
	*/
	Predkosc PredkoscMaksymalna() const;
	
	/**
	* Metoda zwraca procentowy wsp�czynnik mocy silnika.
	* \return Procentowy wp�czynnik mocy silnika.
	*/
	Fluktuacja getPrzyrostMocySilnika() const;

	/**
	* Metoda ustawia procentowy wsp�czynnik mocy silnika.
	* \param f - Procentowy wp�czynnik mocy silnika.
	*/
	void setPrzyrostMocySilnika( const Fluktuacja& f );

	/**
	* Metoda zwraca procentowy wsp�czynnik zu�ycia paliwa.
	* \return Procentowy wp�czynnik zau�ycia paliwa.
	*/
	Fluktuacja getPrzyrostZuzyciaPaliwa() const;

	/**
	* Metoda ustawia procentowy wsp�czynnik zu�ycia paliwa.
	* \param f - Procentowy wp�czynnik zu�ycia paliwa.
	*/
	void setPrzyrostZuzyciaPaliwa( const Fluktuacja& f );

	/**
	* Metoda opisuj�ca zawarto�� klasy.
	* \return CI�g znak�w opisuj�cy klas�.
	*/
	string toString() const override;

protected:

	/**
	* Metoda zwracaj�ca ca�kowit� mas� statku w raz z mas� �adowni.
	* \return Ca�kowita masa statku
	*/
	virtual Masa CalkowitaMasaJednostki() const;

private:
	JednostkaLatajacaInfo * info; /// Wska�nika na klase opisuj�c�.
	Fluktuacja	przyrostMocySilnika; /// Procentowa warto�� mocy silnika.
	Fluktuacja	przyrostZuzyciaPaliwa; /// Procentowa warto�� zu�ycia paliwa.

};

