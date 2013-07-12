
#pragma once
#include "Main.h"
#include "Obrazenia.h"
#include "Fluktuacja.h"
#include "JednostkaAtakujacaInfo.h"
#include "NiezainicjalizowanaKlasa.h"
#include "PodstawoweParametry.h"
/**
* Klasa zawieraj¹ca interfejs jednostki atakuj¹cej, zawiera metody wyliczaj¹ce obra¿enia zadawane, 
* obra¿enia otrzymywane oraz obra¿enia odbijane.
*
*/
class JednostkaAtakujaca :
	virtual public PodstawoweParametry,
	virtual public LoggerInterface
{
public:	
	/**
	* Konstruktor parametryczny.
	* /param jInfo - Wskazanie na klasê reprezentuj¹c¹ opis jednostki atakuj¹cej.
	*/
	JednostkaAtakujaca( const Poziom&p , const IdType& idP, const JednostkaAtakujacaInfo& jInfo );
	JednostkaAtakujaca( const PodstawoweParametry& p, const JednostkaAtakujacaInfo& jInfo );
		
	/**
	* Metoda atak s³u¿y do wyliczania obra¿eñ zadawanych przez obiekt.
	* \return Obra¿enia zadane przez obiekt.
	*/
	virtual Obrazenia Atak( ) const;	

	/**
	* Metoda obliczaj¹ca obra¿enia przyjête przez pancerz. Metoda zwraca obra¿enia, które nie przyj¹³ pancerz.
	* \param o - Obra¿enia przes³ane do obiektu.
	* \return Obra¿enia, które nie zosta³y przyjête przez obiekt.
	*/
	virtual Obrazenia Pancerz( const Obrazenia& o ) const;

	/**
	* Metoda obliczaj¹ca obra¿enia przyjête przez oslone. Metoda zwraca obra¿enia, które nie przyje³a os³ona
	* \param o - Obra¿enia przes³ane do obiektu.
	* \return Obra¿enia, które nie zosta³y przyjête przez obiekt.
	*/
	virtual Obrazenia Oslona( const Obrazenia& o ) const;
	
	/**
	* Przeci¹¿ona funkcja generuj¹ca tekstowy opis klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis() const override;

	virtual Obrazenia getAtak() const;

	virtual Obrazenia getPancerz() const;

	virtual Obrazenia getOslona() const;

	static const double srednia;
	static const double odchylenie;

protected:
	const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo; /// WskaŸnik na klasê opisuj¹c¹. Wymagany do poprawnego dzia³ania.
};