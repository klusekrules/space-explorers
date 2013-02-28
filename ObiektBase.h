#pragma once
#include "Main.h"
#include "Base.h"
#include "Ilosc.h"
#include "Poziom.h"
#include "Klucz.h"

class ObiektInfo;

/**
* Klasa bazowa dla obiektów gry. Zawiera informacje o id obiektu,
* poziomie obiektu, iloœci obiektów przypisanych do tej klasy.
* Klasa umo¿liwa jednoznaczne zidentyfikowanie obiektów w grze.
* Zawiera tak¿e wskazanie na klase opisuj¹c¹ dok³adne dane obiektu.
* Klasa umo¿liwia sprawdzenie czy obiekty moga zostaæ po³¹czone i 
* ewentualnie po³¹czyæ. Pozwala tak¿e sprawdziæ czy mo¿na podzieliæ i
* ewentualnie podzieliæ. Pozwala tak¿e na stworzeni kopii obiektu.
*/
class ObiektBase :
	virtual public Base,
	public Ilosc,
	public Poziom,
	public LoggerInterface<ObiektBase>
{
protected:
	const ObiektInfo *info; /**< Wskazanie na obiekt opisuj¹cy dan¹ klasê*/

public:
	typedef LoggerInterface<ObiektBase> LogObiektBase;

	/**
	* Konstruktor domyœlny.
	*/
	ObiektBase();

	/**
	* Konstruktor klasy na podstawie obiektu opisuj¹cego.
	* \param obiektInfo - Klasa opisuj¹ca obiekt. 
	*/
	explicit ObiektBase( const ObiektInfo& obiektInfo );

	/**
	* Konstruktor z parametrami inicjalizuj¹cymi.
	* \param ilosc - Informacja o iloœci obiektów reprezentowanych przez klasê.
	* \param poziom - Poziom obiektów opisywanych przez klasê.
	* \param obiektInfo - Wskazanie na klasê opisuj¹c¹ reprezentowany obiekt.
	* \param base - Klasa przehocwuj¹ca informacje o id obiektu.
	*/
	ObiektBase( const Ilosc& ilosc, const Poziom & poziom, const ObiektInfo* obiektInfo, const Base& base );

	/**
	* Konstruktor z parametrami inicjalizuj¹cymi.
	* \param ilosc - Informacja o iloœci obiektów reprezentowanych przez klasê.
	* \param poziom - Poziom obiektów opisywanych przez klasê.
	* \param obiektInfo - Wskazanie na klasê opisuj¹c¹ reprezentowany obiekt.
	* \param id - Id obiektu.
	*/
	ObiektBase( const Ilosc& ilosc, const Poziom & poziom, const ObiektInfo* obiektInfo, const IdType& id );

	/**
	* Konstruktor z parametrami inicjalizuj¹cymi. Inicjalizacja pól wymaganych tylko do identyfikacji obiektów.
	* \param poziom - Poziom obiektów opisywanych przez klasê.
	* \param id - Id obiektu.
	*/
	ObiektBase( const IdType& id, const Poziom & poziom);

	/**
	* Destruktor domyœlny.
	*/
	virtual ~ObiektBase();

	/**
	* Metoda kopiuj¹ca klase. Metoda allokuje nowy obiekt, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	virtual ObiektBase* Kopia() const;

	/**
	* Metoda dziel¹ca klasê wzdlêdem iloœci podanej przez argument.
	* Metoda allokuje nowy obiekt, który musi zostaæ zwolniony wywo³aniem delete.
	* Zwrócony obiekt ma iloœæ równ¹ podan¹ przez parametr.
	* Obiekt bazowy ma iloœæ zmniejszon¹ o podan¹ przez parametr wartoœæ.
	* \param ilosc - Iloœæ obiektów wzglêdem, którego jest podzielony obiekt.
	* \return Wskazanie na podzielony obiekt.
	*/
	virtual ObiektBase* Podziel( const Ilosc& ilosc);

	/**
	* Metoda ³¹czy obiekt bazowy z obiektem przekazanym przez parametr.
	* Metoda nie wywo³uje funkcji delete na przekazanym obiekcie.
	* \param obiektBase - Obiekt do po³¹czenia.
	* \return Kiedy obiekty zostan¹ po³¹czone, zwracana wartoœæ to true, w przeciwnym wypadku zwrócona wartoœæ to false.
	*/
	virtual bool Polacz( const ObiektBase& obiektBase);
	
	/**
	* Metoda s³u¿y do zwrócenia klucza jednozancznie identyfikuj¹cego typ obiektu. 
	* Klucz sk³ada siê z id obiektu i poziomu obiektu.
	* \return Klucz identyfikuj¹cy obiekt.
	*/
	Klucz ID() const;

	/**
	* Metoda sprawdzaj¹ca warunki po³¹czenia obiektów.
	* \param obiektBase - Obiekt dla którego maj¹ byæ sprawdzone warunki po³¹czenia.
	* \return Kiedy obiekt mo¿e byæ po³¹czony, zwracana wartoœæ to true, w przeciwnym wypadku zwrócona wartoœæ to false.
	*/
	virtual bool czyMoznaPolaczyc( const ObiektBase& obiektBase) const;

	/**
	* Metoda sprawdzaj¹ca czy mo¿na podzieliæ obiekt wed³ug podanej iloœci.
	* \param ilosc - Iloœæ w zglêdem, której s¹ sprawdzane warunki podzia³u.
	* \return Je¿eli mo¿na podzieliæ, zwracana jest wartoœæ true, w przeciwnym wypadku zwrócona wartoœæ to false.
	*/
	virtual bool czyMoznaPodzielic( const Ilosc& ilosc) const;
	
	/**
	* Metoda zwracaj¹ca wskazanie na obiekt opisuj¹cy.
	* \return Wskazanie na obiekt opisij¹cy.
	*/
	ObiektInfo* getObiektInfo() const;

	/**
	* Metoda ustawiaj¹ca obiekt opisuj¹cy klasê.
	* \param iInfo - Obiekt opisuj¹cy.
	*/
	void setObiektInfo( const ObiektInfo* iInfo );

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string toString() const override;
};

