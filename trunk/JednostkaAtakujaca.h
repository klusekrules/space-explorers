
#pragma once
#include "Main.h"
#include "Obrazenia.h"
#include "Fluktuacja.h"
#include "JednostkaAtakujacaInfo.h"
#include "NiezainicjalizowanaKlasa.h"
#include "PodstawoweParametry.h"
/**
* Klasa zawieraj�ca interfejs jednostki atakuj�cej, zawiera metody wyliczaj�ce obra�enia zadawane, 
* obra�enia otrzymywane oraz obra�enia odbijane.
*
*/
class JednostkaAtakujaca :
	virtual public PodstawoweParametry,
	virtual public LoggerInterface
{
public:	
	/**
	* Konstruktor parametryczny.
	* /param jInfo - Wskazanie na klas� reprezentuj�c� opis jednostki atakuj�cej.
	*/
	JednostkaAtakujaca( const Poziom&p , const IdType& idP, const JednostkaAtakujacaInfo& jInfo );
	JednostkaAtakujaca( const PodstawoweParametry& p, const JednostkaAtakujacaInfo& jInfo );
		
	/**
	* Metoda atak s�u�y do wyliczania obra�e� zadawanych przez obiekt.
	* \return Obra�enia zadane przez obiekt.
	*/
	virtual Obrazenia Atak( ) const;	

	/**
	* Metoda obliczaj�ca obra�enia przyj�te przez pancerz. Metoda zwraca obra�enia, kt�re nie przyj�� pancerz.
	* \param o - Obra�enia przes�ane do obiektu.
	* \return Obra�enia, kt�re nie zosta�y przyj�te przez obiekt.
	*/
	virtual Obrazenia Pancerz( const Obrazenia& o ) const;

	/**
	* Metoda obliczaj�ca obra�enia przyj�te przez oslone. Metoda zwraca obra�enia, kt�re nie przyje�a os�ona
	* \param o - Obra�enia przes�ane do obiektu.
	* \return Obra�enia, kt�re nie zosta�y przyj�te przez obiekt.
	*/
	virtual Obrazenia Oslona( const Obrazenia& o ) const;
	
	/**
	* Przeci��ona funkcja generuj�ca tekstowy opis klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override;

	virtual Obrazenia getAtak() const;

	virtual Obrazenia getPancerz() const;

	virtual Obrazenia getOslona() const;

	static const double srednia;
	static const double odchylenie;

protected:
	const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo; /// Wska�nik na klas� opisuj�c�. Wymagany do poprawnego dzia�ania.
};