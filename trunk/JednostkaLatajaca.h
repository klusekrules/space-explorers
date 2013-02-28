#pragma once
#include "Main.h"
#include "Fluktuacja.h"
#include "Predkosc.h"
#include "Dystans.h"
#include "JednostkaLatajacaInfo.h"


/**
* Klasa implementuj¹ca interfejs, s³u¿¹cy do lotów statków kosmiczych.
* Pozwala na wyliczenie wszystkich parametrów lotu.
*/
class JednostkaLatajaca :
	public LoggerInterface < JednostkaLatajaca >
{
public:
	/**
	* Konstruktor domyœlny
	*/
	JednostkaLatajaca();

	/**
	* Konstruktor parametryczny
	* \param jInfo - Wskazanie na klasê opisuj¹c¹
	* \param mocSilnika - Procentowa wartoœæ mocy w klasie opisuj¹cej. Domyœlnie 1.0 
	* \param zuzyciePaliwa - Procentowa wartoœæ zu¿ycia paliwa w klasie opisuj¹cej. Domyœlnie 1.0 
	*/
	JednostkaLatajaca( JednostkaLatajacaInfo * jInfo , const Fluktuacja& mocSilnika , const Fluktuacja& zuzyciePaliwa );
	
	/**
	* Domyœlny konstruktor kopiuj¹cy
	* \param a - Obiekt na podstawie którego zostanie utworzona kopia.
	*/
	JednostkaLatajaca( const JednostkaLatajaca& a );
	
	/**
	* Destruktor domyœlny
	*/
	virtual ~JednostkaLatajaca();

	/**
	* Funkcja wyliczaj¹ca zy¿ycie paliwa przez statek na okreœlonym dystansie i przy okreœlonej prêkoœci.
	* \param d - Dystans, na którym ma poruszaæ siê statek.
	* \param p - Prêdkoœæ, któr¹ ma lecieæ statek.
	* \return Paliwo zu¿yte przez statek.
	*/
	ZuzyciePaliwa WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const;

	/**
	* Maksymalna prêkoœæ jak¹ mo¿e rozwin¹æ statek.
	* \return prêdkoœæ jak¹ mo¿e rozwin¹æ statek.
	*/
	Predkosc PredkoscMaksymalna() const;
	
	/**
	* Metoda zwraca procentowy wspó³czynnik mocy silnika.
	* \return Procentowy wpó³czynnik mocy silnika.
	*/
	Fluktuacja getPrzyrostMocySilnika() const;

	/**
	* Metoda ustawia procentowy wspó³czynnik mocy silnika.
	* \param f - Procentowy wpó³czynnik mocy silnika.
	*/
	void setPrzyrostMocySilnika( const Fluktuacja& f );

	/**
	* Metoda zwraca procentowy wspó³czynnik zu¿ycia paliwa.
	* \return Procentowy wpó³czynnik zau¿ycia paliwa.
	*/
	Fluktuacja getPrzyrostZuzyciaPaliwa() const;

	/**
	* Metoda ustawia procentowy wspó³czynnik zu¿ycia paliwa.
	* \param f - Procentowy wpó³czynnik zu¿ycia paliwa.
	*/
	void setPrzyrostZuzyciaPaliwa( const Fluktuacja& f );

	/**
	* Metoda opisuj¹ca zawartoœæ klasy.
	* \return CI¹g znaków opisuj¹cy klasê.
	*/
	string toString() const override;

protected:

	/**
	* Metoda zwracaj¹ca ca³kowit¹ masê statku w raz z mas¹ ³adowni.
	* \return Ca³kowita masa statku
	*/
	virtual Masa CalkowitaMasaJednostki() const;

private:
	JednostkaLatajacaInfo * info; /// WskaŸnika na klase opisuj¹c¹.
	Fluktuacja	przyrostMocySilnika; /// Procentowa wartoœæ mocy silnika.
	Fluktuacja	przyrostZuzyciaPaliwa; /// Procentowa wartoœæ zu¿ycia paliwa.

};

