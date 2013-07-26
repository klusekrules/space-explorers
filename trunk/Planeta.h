#pragma once
#include "Logger\LoggerInterface.h"
#include "Bazowa.h"
#include "ObiektBazowy.h"
#include "ObiektBazowyInfo.h"
#include <map>
#include <memory>
#include "Budynek.h"
#include "Statek.h"
#include "Technologia.h"
#include "Surowce.h"
#include "NiepoprawnaIloscObiektow.h"
#include "Flota.h"
#include "Licznik.h"

/**
* \brief Klasa reprezentuj¹ca planetê.
*
* Klasa reprezentuj¹ca planetê.
* \author Daniel Wojdak
* \version 1
* \date 26-07-2013
*/
class Planeta:
	public Bazowa,
	virtual public LoggerInterface,
	virtual public Serializacja
{
	friend class Gra;
	friend class Uzytkownik;
public:
	typedef map< Identyfikator , shared_ptr< ObiektBazowy > > ListaObiektow;
	typedef map< Identyfikator , shared_ptr< Obiekt > > ListaObiektowZaladunkowych;
	typedef map< Identyfikator , shared_ptr< Budynek > > ListaBudynkow;
	typedef map< Identyfikator , shared_ptr< Technologia > > ListaTechnologii;
	typedef map< Identyfikator , shared_ptr< Statek > > ListaStatkow;
	typedef map< Identyfikator , shared_ptr< Surowce > > ListaSurowcow;
	typedef map< Identyfikator , shared_ptr< Flota > > ListaFlot;
	
	/**
	* \brief Konstruktor.
	*
	* \param[in] identyfikator - Identyfikator planety.
	*/
	Planeta(const Identyfikator& identyfikator);

	/**
	* \brief Destruktor.
	*/
	virtual ~Planeta(void);
	
	/**
	* \brief Metoda pobiera iloœæ ró¿nych typów obiektów dostêpnych na planecie.
	* 
	* \return Iloœæ typów obiektów na planecie.
	*/
	Ilosc pobierzIloscTypowObiektow()const;

	/**
	* \brief Metoda pobiera obiekt o podanym identyfikatorze.
	* 
	* Metoda pobiera z planety obiekt o podanym identyfikatorze.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \return Referencja do obiektu.
	*/
	const ObiektBazowy& pobierzObiekt(const Identyfikator& identyfikator) const;

	/**
	* \brief Metoda pobiera statek o podanym identyfikatorze.
	* 
	* Metoda pobiera z planety statek o podanym identyfikatorze.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \return Referencja do obiektu.
	*/
	const Statek& pobierzStatek(const Identyfikator& identyfikator) const;

	/**
	* \brief Metoda pobiera tehcnologie o podanym identyfikatorze.
	* 
	* Metoda pobiera z planety tehcnologie o podanym identyfikatorze.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \return Referencja do obiektu.
	*/
	const Technologia& pobierzTechnologie(const Identyfikator& identyfikator) const;

	/**
	* \brief Metoda pobiera budynek o podanym identyfikatorze.
	* 
	* Metoda pobiera z planety budynek o podanym identyfikatorze.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \return Referencja do obiektu.
	*/
	const Budynek& pobierzBudynek(const Identyfikator& identyfikator) const;
	
	/**
	* \brief Metoda buduje obiekt na planecie.
	* 
	* Metoda buduje obiekt o podanym identyfikatorze i iloœci na planecie.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \param[in] ilosc - Atrybut iloœci tworzonego obieku.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybuduj( const Identyfikator& identyfikator, const Ilosc& ilosc );

	/**
	* \brief Metoda buduje statek na planecie.
	* 
	* Metoda buduje statek na planecie.
	* \param[in] obiekt - Sprytny wskaŸnik na obiekt dodawany do planety.
	* \remark Metoda tworzy kopie elementu, nie zapamiêtuje wskaŸnika przekazanego jako parametr.
	*/
	void wybuduj( shared_ptr< ObiektBazowy > obiekt );
	
	/**
	* \brief Metoda buduje statek na planecie.
	* 
	* Metoda buduje statek na planecie.
	* \param[in] obiekt - Sprytny wskaŸnik na obiekt dodawany do planety.
	* \remark Je¿eli nie ma ¿adnuych obiektów tego typu na planecie metoda zapisuje wskaŸnik, nie tworzy kopii.
	*/
	void wybuduj( shared_ptr< Statek > obiekt );

	/**
	* \brief Metoda tworzy flotê na planecie.
	*
	* Metoda tworzy pusty obiekt floty na planecie i zwraca identyfikator.
	* \return Identyfikator nowo stworzonej floty.
	*/
	Identyfikator dodajFlote();

	/**
	* \brief Metoda pobiera flotê.
	*
	* Metoda pobiera sprytny wskaŸnik do floty o podanym identyfikatorze.
	* \param[in] identyfikator - Identyfikator floty.
	* \return Sprytny wskaŸnik do floty lub nullptr jezeli flota o podanym identyfikatorze nie istnieje.
	*/
	shared_ptr< Flota > pobierzFlote( const Identyfikator& identyfikator ) const;

	/**
	* \brief Metoda usuwaj¹ca flotê z planety.
	*
	* Metoda usuwa flotê z listy flot na planecie. Nie roz³adowuje jej ani nie przenosi statków na planete.
	* \param[in] identyfikator - Identyfikator floty do usuniêcia.
	* \return true je¿eli uda³o siê usun¹æ, false w przecwnym wypadku.
	*/
	bool usunFlote(const Identyfikator& identyfikator);

	/**
	* \brief Metoda przenoœci obiekt do floty.
	*
	* Metoda przenosi obiekt z planety do floty.
	* \param[in] flota - Identyfikator floty do której ma zostaæ przeniesiony obiekt.
	* \param[in] obiekt - Identyfikator obiektu, który ma byc przenisiony do floty.
	* \param[in] ilosc - Iloœæ obiektów do przeniesienia.
	* \return true je¿eli uda siê przenieœæ obiekt, false w przeciwnym wypadku.
	*/
	bool przeniesDoFloty(const Identyfikator& flota, const Identyfikator& obiekt, const Ilosc& ilosc );

	/**
	* \brief Metoda przenoœci obiekt do ³adowni floty.
	*
	* Metoda przenosi obiekt z planety do ³adowni floty.
	* \param[in] flota - Identyfikator floty do ³adowni której ma zostaæ przeniesiony obiekt.
	* \param[in] obiekt - Identyfikator obiektu, który ma byc przenisiony do ³adowni floty.
	* \param[in] ilosc - Iloœæ obiektów do przeniesienia.
	* \return true je¿eli uda siê przenieœæ obiekt, false w przeciwnym wypadku.
	*/
	bool zaladujFlote( const Identyfikator& flota, const Identyfikator& obiekt, const Ilosc& ilosc );

	/**
	* \brief Metoda rozladowujaca statek.
	*
	* Metoda przenosi obiekty z ³adowni na planetê.
	*/
	void rozladujStatek( shared_ptr< Statek > statek );

	/**
	* \brief Metoda sprawdzaj¹ca czy planeta ma w³asciciela.
	*
	* \return true je¿eli obiekt posiada w³aœciciela, false w przeciwnym przypadku.
	*/
	bool czyMaWlasciciela()const;

	/**
	* \brief Metoda zapisuj¹ca.
	*
	* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
	* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
	* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( TiXmlElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj¹ca.
	*
	* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
	* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
	* \warning Metoda nie modyfikuje wêz³a.
	* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
	*/
	bool odczytaj( TiXmlElement* wezel ) override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;
	
private:

	/**
	* \brief Metoda dodaj¹ca Budynek do planety.
	*
	* Metoda dodaje Budynek do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
	* \param[in] obiekt - Sprytny wskaŸnik na dodawany obiekt.
	* \return true je¿eli uda siê dodaæ obiekt, fasle w przeciwnym wypadku.
	*/
	bool dodajObiekt( shared_ptr< Budynek > obiekt );

	/**
	* \brief Metoda dodaj¹ca Statek do planety.
	*
	* Metoda dodaje Statek do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
	* \param[in] obiekt - Sprytny wskaŸnik na dodawany obiekt.
	* \return true je¿eli uda siê dodaæ obiekt, fasle w przeciwnym wypadku.
	*/
	bool dodajObiekt( shared_ptr< Statek > obiekt );

	/**
	* \brief Metoda dodaj¹ca Technologie do planety.
	*
	* Metoda dodaje Technologie do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
	* \param[in] obiekt - Sprytny wskaŸnik na dodawany obiekt.
	* \return true je¿eli uda siê dodaæ obiekt, fasle w przeciwnym wypadku.
	*/
	bool dodajObiekt( shared_ptr< Technologia > obiekt );

	/**
	* \brief Metoda dodaj¹ca Surowce do planety.
	*
	* Metoda dodaje Surowce do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
	* \param[in] obiekt - Sprytny wskaŸnik na dodawany obiekt.
	* \return true je¿eli uda siê dodaæ obiekt, fasle w przeciwnym wypadku.
	*/
	bool dodajObiekt( shared_ptr< Surowce > obiekt );
	
	/**
	* \brief Metoda ustawia w³aœciciela planety.
	*
	* Metoda zamienia bierz¹cego w³aœciciela na podanego w parametrze.
	* \param[in] uzytkownik - WskaŸnik na u¿ytkownika.
	*/
	void ustawWlasciciela( Uzytkownik* uzytkownik );

	/**
	* \brief Metoda pobiera w³aœciciela.
	*
	*\return WskaŸnika na w³aœciciela.
	*/
	Uzytkownik* pobierzWlasciciela( ) const;

	/* TODO: do pozbycia siê*/
	shared_ptr<ObiektBazowy> pustyObiektBase; /// Pusty obiekt bazowy
	ObiektBazowyInfo pustyobiekBaseInfo; /// Pusty obiekt bazowy info.
	/* ------ */

	Licznik licznikIdentyfikatorowFloty_; /// Licznik identyfikatorów flot.
	Uzytkownik* wlasciciel_; /// W³aœciciel planety.

	ListaSurowcow listaSurowcow_; /// Lista surowców planety.
	ListaStatkow listaStatkow_; /// Lista statków planety
	ListaTechnologii listaTechnologii_; /// Lista tehcnologii planety.
	ListaBudynkow listaBudynkow_; /// Lista budynków planety.
	ListaObiektow listaObiektow_; /// Lista wszystkich obiektów planety.
	ListaObiektowZaladunkowych listaObiektowZaladunkowych_; /// Lista obiektów za³adunkowych planety.
	ListaFlot listaFlot_; /// Lista flot planety.
};
