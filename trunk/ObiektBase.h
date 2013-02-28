#pragma once
#include "Main.h"
#include "Base.h"
#include "Ilosc.h"
#include "Poziom.h"
#include "Klucz.h"

class ObiektInfo;

/**
* Klasa bazowa dla obiekt�w gry. Zawiera informacje o id obiektu,
* poziomie obiektu, ilo�ci obiekt�w przypisanych do tej klasy.
* Klasa umo�liwa jednoznaczne zidentyfikowanie obiekt�w w grze.
* Zawiera tak�e wskazanie na klase opisuj�c� dok�adne dane obiektu.
* Klasa umo�liwia sprawdzenie czy obiekty moga zosta� po��czone i 
* ewentualnie po��czy�. Pozwala tak�e sprawdzi� czy mo�na podzieli� i
* ewentualnie podzieli�. Pozwala tak�e na stworzeni kopii obiektu.
*/
class ObiektBase :
	virtual public Base,
	public Ilosc,
	public Poziom,
	public LoggerInterface<ObiektBase>
{
protected:
	const ObiektInfo *info; /**< Wskazanie na obiekt opisuj�cy dan� klas�*/

public:
	typedef LoggerInterface<ObiektBase> LogObiektBase;

	/**
	* Konstruktor domy�lny.
	*/
	ObiektBase();

	/**
	* Konstruktor klasy na podstawie obiektu opisuj�cego.
	* \param obiektInfo - Klasa opisuj�ca obiekt. 
	*/
	explicit ObiektBase( const ObiektInfo& obiektInfo );

	/**
	* Konstruktor z parametrami inicjalizuj�cymi.
	* \param ilosc - Informacja o ilo�ci obiekt�w reprezentowanych przez klas�.
	* \param poziom - Poziom obiekt�w opisywanych przez klas�.
	* \param obiektInfo - Wskazanie na klas� opisuj�c� reprezentowany obiekt.
	* \param base - Klasa przehocwuj�ca informacje o id obiektu.
	*/
	ObiektBase( const Ilosc& ilosc, const Poziom & poziom, const ObiektInfo* obiektInfo, const Base& base );

	/**
	* Konstruktor z parametrami inicjalizuj�cymi.
	* \param ilosc - Informacja o ilo�ci obiekt�w reprezentowanych przez klas�.
	* \param poziom - Poziom obiekt�w opisywanych przez klas�.
	* \param obiektInfo - Wskazanie na klas� opisuj�c� reprezentowany obiekt.
	* \param id - Id obiektu.
	*/
	ObiektBase( const Ilosc& ilosc, const Poziom & poziom, const ObiektInfo* obiektInfo, const IdType& id );

	/**
	* Konstruktor z parametrami inicjalizuj�cymi. Inicjalizacja p�l wymaganych tylko do identyfikacji obiekt�w.
	* \param poziom - Poziom obiekt�w opisywanych przez klas�.
	* \param id - Id obiektu.
	*/
	ObiektBase( const IdType& id, const Poziom & poziom);

	/**
	* Destruktor domy�lny.
	*/
	virtual ~ObiektBase();

	/**
	* Metoda kopiuj�ca klase. Metoda allokuje nowy obiekt, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	virtual ObiektBase* Kopia() const;

	/**
	* Metoda dziel�ca klas� wzdl�dem ilo�ci podanej przez argument.
	* Metoda allokuje nowy obiekt, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* Zwr�cony obiekt ma ilo�� r�wn� podan� przez parametr.
	* Obiekt bazowy ma ilo�� zmniejszon� o podan� przez parametr warto��.
	* \param ilosc - Ilo�� obiekt�w wzgl�dem, kt�rego jest podzielony obiekt.
	* \return Wskazanie na podzielony obiekt.
	*/
	virtual ObiektBase* Podziel( const Ilosc& ilosc);

	/**
	* Metoda ��czy obiekt bazowy z obiektem przekazanym przez parametr.
	* Metoda nie wywo�uje funkcji delete na przekazanym obiekcie.
	* \param obiektBase - Obiekt do po��czenia.
	* \return Kiedy obiekty zostan� po��czone, zwracana warto�� to true, w przeciwnym wypadku zwr�cona warto�� to false.
	*/
	virtual bool Polacz( const ObiektBase& obiektBase);
	
	/**
	* Metoda s�u�y do zwr�cenia klucza jednozancznie identyfikuj�cego typ obiektu. 
	* Klucz sk�ada si� z id obiektu i poziomu obiektu.
	* \return Klucz identyfikuj�cy obiekt.
	*/
	Klucz ID() const;

	/**
	* Metoda sprawdzaj�ca warunki po��czenia obiekt�w.
	* \param obiektBase - Obiekt dla kt�rego maj� by� sprawdzone warunki po��czenia.
	* \return Kiedy obiekt mo�e by� po��czony, zwracana warto�� to true, w przeciwnym wypadku zwr�cona warto�� to false.
	*/
	virtual bool czyMoznaPolaczyc( const ObiektBase& obiektBase) const;

	/**
	* Metoda sprawdzaj�ca czy mo�na podzieli� obiekt wed�ug podanej ilo�ci.
	* \param ilosc - Ilo�� w zgl�dem, kt�rej s� sprawdzane warunki podzia�u.
	* \return Je�eli mo�na podzieli�, zwracana jest warto�� true, w przeciwnym wypadku zwr�cona warto�� to false.
	*/
	virtual bool czyMoznaPodzielic( const Ilosc& ilosc) const;
	
	/**
	* Metoda zwracaj�ca wskazanie na obiekt opisuj�cy.
	* \return Wskazanie na obiekt opisij�cy.
	*/
	ObiektInfo* getObiektInfo() const;

	/**
	* Metoda ustawiaj�ca obiekt opisuj�cy klas�.
	* \param iInfo - Obiekt opisuj�cy.
	*/
	void setObiektInfo( const ObiektInfo* iInfo );

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string toString() const override;
};

