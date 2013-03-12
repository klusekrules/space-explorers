
#pragma once
#include "Main.h"
#include "Obrazenia.h"
#include "Fluktuacja.h"
#include "JednostkaAtakujacaInfo.h"
#include "NiezainicjalizowanaKlasa.h"
/**
* Klasa zawieraj�ca interfejs jednostki atakuj�cej, zawiera metody wyliczaj�ce obra�enia zadawane, 
* obra�enia otrzymywane oraz obra�enia odbijane.
*
*/
class JednostkaAtakujaca :
	public LoggerInterface < JednostkaAtakujaca >
{
public:
	typedef LoggerInterface<JednostkaAtakujaca> LogJednostkaAtakujaca;
	
	/**
	* Konstruktor parametryczny.
	* /param jInfo - Wskazanie na klas� reprezentuj�c� opis jednostki atakuj�cej.
	*/
	JednostkaAtakujaca( JednostkaAtakujacaInfo* jInfo );
	/**
	* Konstruktor kopiuj�cy.
	* \param a - obiekt do skopiowania
	*/
	JednostkaAtakujaca( const JednostkaAtakujaca& a );

	/**
	* Wirtualny destruktor
	*/
	virtual ~JednostkaAtakujaca();
	
	/**
	* Metoda atak s�u�y do wyliczania obra�e� zadawanych przez obiekt.
	* \return Obra�enia zadane przez obiekt.
	*/
	virtual Obrazenia Atak() const throw (NiezainicjalizowanaKlasa);	

	/**
	* Metoda obliczaj�ca obra�enia przyj�te przez pancerz. Metoda zwraca obra�enia, kt�re nie przyj�� pancerz.
	* \param o - Obra�enia przes�ane do obiektu.
	* \return Obra�enia, kt�re nie zosta�y przyj�te przez obiekt.
	*/
	virtual Obrazenia Pancerz( const Obrazenia& o ) const throw (NiezainicjalizowanaKlasa);

	/**
	* Metoda obliczaj�ca obra�enia przyj�te przez oslone. Metoda zwraca obra�enia, kt�re nie przyje�a os�ona
	* \param o - Obra�enia przes�ane do obiektu.
	* \return Obra�enia, kt�re nie zosta�y przyj�te przez obiekt.
	*/
	virtual Obrazenia Oslona( const Obrazenia& o ) const throw (NiezainicjalizowanaKlasa);
	
	/**
	* Metoda zwraca wskazanie na klas� opisuj�c�.
	* \return Wska�nik na klas� opisuj�c�.
	*/
	JednostkaAtakujacaInfo* getJednostkaAtakujacaInfo() const;

	/**
	* Metoda ustawia wskazanie na klas� opisuj�c�.
	* \param i - Nowy wska�nik na klas� opisuj�c�.
	*/
	void setJednostkaAtakujacaInfo( JednostkaAtakujacaInfo* i);

	/**
	* Przeci��ona funkcja generuj�ca tekstowy opis klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string toString() const override;

private:
	JednostkaAtakujacaInfo * jednostkaAtakujacaInfo; /// Wska�nik na klas� opisuj�c�. Wymagany do poprawnego dzia�ania.
	
};