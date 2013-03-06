
#pragma once
#include "Main.h"
#include "Obrazenia.h"
#include "Fluktuacja.h"
#include "JednostkaAtakujacaInfo.h"
#include "NiezainicjalizowanaKlasa.h"
/**
* Klasa zawieraj¹ca interfejs jednostki atakuj¹cej, zawiera metody wyliczaj¹ce obra¿enia zadawane, 
* obra¿enia otrzymywane oraz obra¿enia odbijane.
*
*/
class JednostkaAtakujaca :
	public LoggerInterface < JednostkaAtakujaca >
{
public:
	typedef LoggerInterface<JednostkaAtakujaca> LogJednostkaAtakujaca;
	/**
	* Konstruktor domyœlny.
	*/
	JednostkaAtakujaca();

	/**
	* Konstruktor parametryczny.
	* \param wzPrzyrostAtaku - przyrost ataku
	* \param wzPrzyrostPancerza - przyrost pancerza
	* \param wzPrzyrostOslony - przyrost oslony
	*/
	JednostkaAtakujaca::JednostkaAtakujaca( JednostkaAtakujacaInfo* jInfo , const Fluktuacja& wzPrzyrostAtaku, const Fluktuacja& wzPrzyrostPancerza, const Fluktuacja& wzPrzyrostOslony );
	/**
	* Konstruktor kopiuj¹cy.
	* \param a - obiekt do skopiowania
	*/
	JednostkaAtakujaca( const JednostkaAtakujaca& a );

	/**
	* Wirtualny destruktor
	*/
	virtual ~JednostkaAtakujaca();
	
	/**
	* Metoda atak s³u¿y do wyliczania obra¿eñ zadawanych przez obiekt.
	* \return Obra¿enia zadane przez obiekt.
	*/
	virtual Obrazenia Atak() const throw (NiezainicjalizowanaKlasa);	

	/**
	* Metoda obliczaj¹ca obra¿enia przyjête przez pancerz. Metoda zwraca obra¿enia, które nie przyj¹³ pancerz.
	* \param o - Obra¿enia przes³ane do obiektu.
	* \return Obra¿enia, które nie zosta³y przyjête przez obiekt.
	*/
	virtual Obrazenia Pancerz( const Obrazenia& o ) const throw (NiezainicjalizowanaKlasa);

	/**
	* Metoda obliczaj¹ca obra¿enia przyjête przez oslone. Metoda zwraca obra¿enia, które nie przyje³a os³ona
	* \param o - Obra¿enia przes³ane do obiektu.
	* \return Obra¿enia, które nie zosta³y przyjête przez obiekt.
	*/
	virtual Obrazenia Oslona( const Obrazenia& o ) const throw (NiezainicjalizowanaKlasa);
	
	/**
	* Metoda zwraca wskazanie na klasê opisuj¹c¹.
	* \return WskaŸnik na klasê opisuj¹c¹.
	*/
	JednostkaAtakujacaInfo* getJednostkaAtakujacaInfo() const;

	/**
	* Metoda ustawia wskazanie na klasê opisuj¹c¹.
	* \param i - Nowy wskaŸnik na klasê opisuj¹c¹.
	*/
	void setJednostkaAtakujacaInfo( JednostkaAtakujacaInfo* i);

	/**
	* Metoda zwraca procentow¹ zmianê ataku wzglêdem wartoœci podstawowej.
	* \return Procent z wartoœci podstawowej.
	*/
	const Fluktuacja& getPrzyrostAtaku() const;

	/**
	* Metoda ustawia procentow¹ zmianê ataku wzglêdem wartoœci podstawowej.
	* \param a - Nowy procent z wartoœci podstawowej.
	*/
	void setPrzyrostAtaku( const Fluktuacja& a );
	
	/**
	* Metoda zwraca procentow¹ zmianê pancerza wzglêdem wartoœci podstawowej.
	* \return Procent z wartoœci podstawowej.
	*/
	const Fluktuacja& getPrzyrostPancerza() const;	

	/**
	* Metoda ustawia procentow¹ zmianê pancerza wzglêdem wartoœci podstawowej.
	* \param p - Nowy procent z wartoœci podstawowej.
	*/
	void setPrzyrostPancerza( const Fluktuacja& p );
	
	/**
	* Metoda zwraca procentow¹ zmianê os³ony wzglêdem wartoœci podstawowej.
	* \return Procent z wartoœci podstawowej.
	*/
	const Fluktuacja& getPrzyrostOslony() const;	

	/**
	* Metoda ustawia procentow¹ zmianê os³ony wzglêdem wartoœci podstawowej.
	* \param o - Nowy procent z wartoœci podstawowej.
	*/
	void setPrzyrostOslony( const Fluktuacja& o );
	
	/**
	* Przeci¹¿ona funkcja generuj¹ca tekstowy opis klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string toString() const override;

private:
	JednostkaAtakujacaInfo * info; /// WskaŸnik na klasê opisuj¹c¹. Wymagany do poprawnego dzia³ania.

	Fluktuacja przyrostAtaku; /// Procentowa zmiana ataku wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.
	Fluktuacja przyrostPancerza; /// Procentowa zmiana pancerza wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.
	Fluktuacja przyrostOslony; /// Procentowa zmiana os³ony wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.
	
};