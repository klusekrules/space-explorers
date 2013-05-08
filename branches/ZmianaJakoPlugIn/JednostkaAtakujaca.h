
#pragma once
#include "Main.h"
#include "BaseTypes\Obrazenia.h"
#include "BaseTypes\Fluktuacja.h"
#include "JednostkaAtakujacaInfo.h"
#include "BaseTypes\NiezainicjalizowanaKlasa.h"
/**
* Klasa zawieraj�ca interfejs jednostki atakuj�cej, zawiera metody wyliczaj�ce obra�enia zadawane, 
* obra�enia otrzymywane oraz obra�enia odbijane.
*
*/
class JednostkaAtakujaca :
	virtual public LoggerInterface
{
public:	
	/**
	* Konstruktor parametryczny.
	* /param jInfo - Wskazanie na klas� reprezentuj�c� opis jednostki atakuj�cej.
	*/
	explicit JednostkaAtakujaca( const JednostkaAtakujacaInfo& jInfo );
	
	/**
	* Wirtualny destruktor
	*/
	virtual ~JednostkaAtakujaca();
	
	/**
	* Metoda atak s�u�y do wyliczania obra�e� zadawanych przez obiekt.
	* \return Obra�enia zadane przez obiekt.
	*/
	virtual Obrazenia Atak( const Poziom& p ) const;	

	/**
	* Metoda obliczaj�ca obra�enia przyj�te przez pancerz. Metoda zwraca obra�enia, kt�re nie przyj�� pancerz.
	* \param o - Obra�enia przes�ane do obiektu.
	* \return Obra�enia, kt�re nie zosta�y przyj�te przez obiekt.
	*/
	virtual Obrazenia Pancerz( const Obrazenia& o ,const Poziom& p  ) const;

	/**
	* Metoda obliczaj�ca obra�enia przyj�te przez oslone. Metoda zwraca obra�enia, kt�re nie przyje�a os�ona
	* \param o - Obra�enia przes�ane do obiektu.
	* \return Obra�enia, kt�re nie zosta�y przyj�te przez obiekt.
	*/
	virtual Obrazenia Oslona( const Obrazenia& o , const Poziom& p ) const;
	
	/**
	* Przeci��ona funkcja generuj�ca tekstowy opis klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string toString() const override;

protected:
	const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo; /// Wska�nik na klas� opisuj�c�. Wymagany do poprawnego dzia�ania.
	
};