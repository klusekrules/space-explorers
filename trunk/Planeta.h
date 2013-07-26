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
* \brief Klasa reprezentuj�ca planet�.
*
* Klasa reprezentuj�ca planet�.
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
	* \brief Metoda pobiera ilo�� r�nych typ�w obiekt�w dost�pnych na planecie.
	* 
	* \return Ilo�� typ�w obiekt�w na planecie.
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
	* Metoda buduje obiekt o podanym identyfikatorze i ilo�ci na planecie.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \param[in] ilosc - Atrybut ilo�ci tworzonego obieku.
	* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
	*/
	bool wybuduj( const Identyfikator& identyfikator, const Ilosc& ilosc );

	/**
	* \brief Metoda buduje statek na planecie.
	* 
	* Metoda buduje statek na planecie.
	* \param[in] obiekt - Sprytny wska�nik na obiekt dodawany do planety.
	* \remark Metoda tworzy kopie elementu, nie zapami�tuje wska�nika przekazanego jako parametr.
	*/
	void wybuduj( shared_ptr< ObiektBazowy > obiekt );
	
	/**
	* \brief Metoda buduje statek na planecie.
	* 
	* Metoda buduje statek na planecie.
	* \param[in] obiekt - Sprytny wska�nik na obiekt dodawany do planety.
	* \remark Je�eli nie ma �adnuych obiekt�w tego typu na planecie metoda zapisuje wska�nik, nie tworzy kopii.
	*/
	void wybuduj( shared_ptr< Statek > obiekt );

	/**
	* \brief Metoda tworzy flot� na planecie.
	*
	* Metoda tworzy pusty obiekt floty na planecie i zwraca identyfikator.
	* \return Identyfikator nowo stworzonej floty.
	*/
	Identyfikator dodajFlote();

	/**
	* \brief Metoda pobiera flot�.
	*
	* Metoda pobiera sprytny wska�nik do floty o podanym identyfikatorze.
	* \param[in] identyfikator - Identyfikator floty.
	* \return Sprytny wska�nik do floty lub nullptr jezeli flota o podanym identyfikatorze nie istnieje.
	*/
	shared_ptr< Flota > pobierzFlote( const Identyfikator& identyfikator ) const;

	/**
	* \brief Metoda usuwaj�ca flot� z planety.
	*
	* Metoda usuwa flot� z listy flot na planecie. Nie roz�adowuje jej ani nie przenosi statk�w na planete.
	* \param[in] identyfikator - Identyfikator floty do usuni�cia.
	* \return true je�eli uda�o si� usun��, false w przecwnym wypadku.
	*/
	bool usunFlote(const Identyfikator& identyfikator);

	/**
	* \brief Metoda przeno�ci obiekt do floty.
	*
	* Metoda przenosi obiekt z planety do floty.
	* \param[in] flota - Identyfikator floty do kt�rej ma zosta� przeniesiony obiekt.
	* \param[in] obiekt - Identyfikator obiektu, kt�ry ma byc przenisiony do floty.
	* \param[in] ilosc - Ilo�� obiekt�w do przeniesienia.
	* \return true je�eli uda si� przenie�� obiekt, false w przeciwnym wypadku.
	*/
	bool przeniesDoFloty(const Identyfikator& flota, const Identyfikator& obiekt, const Ilosc& ilosc );

	/**
	* \brief Metoda przeno�ci obiekt do �adowni floty.
	*
	* Metoda przenosi obiekt z planety do �adowni floty.
	* \param[in] flota - Identyfikator floty do �adowni kt�rej ma zosta� przeniesiony obiekt.
	* \param[in] obiekt - Identyfikator obiektu, kt�ry ma byc przenisiony do �adowni floty.
	* \param[in] ilosc - Ilo�� obiekt�w do przeniesienia.
	* \return true je�eli uda si� przenie�� obiekt, false w przeciwnym wypadku.
	*/
	bool zaladujFlote( const Identyfikator& flota, const Identyfikator& obiekt, const Ilosc& ilosc );

	/**
	* \brief Metoda rozladowujaca statek.
	*
	* Metoda przenosi obiekty z �adowni na planet�.
	*/
	void rozladujStatek( shared_ptr< Statek > statek );

	/**
	* \brief Metoda sprawdzaj�ca czy planeta ma w�asciciela.
	*
	* \return true je�eli obiekt posiada w�a�ciciela, false w przeciwnym przypadku.
	*/
	bool czyMaWlasciciela()const;

	/**
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
	* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( TiXmlElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	* \warning Metoda nie modyfikuje w�z�a.
	* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
	*/
	bool odczytaj( TiXmlElement* wezel ) override;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;
	
private:

	/**
	* \brief Metoda dodaj�ca Budynek do planety.
	*
	* Metoda dodaje Budynek do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
	* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
	* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
	*/
	bool dodajObiekt( shared_ptr< Budynek > obiekt );

	/**
	* \brief Metoda dodaj�ca Statek do planety.
	*
	* Metoda dodaje Statek do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
	* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
	* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
	*/
	bool dodajObiekt( shared_ptr< Statek > obiekt );

	/**
	* \brief Metoda dodaj�ca Technologie do planety.
	*
	* Metoda dodaje Technologie do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
	* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
	* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
	*/
	bool dodajObiekt( shared_ptr< Technologia > obiekt );

	/**
	* \brief Metoda dodaj�ca Surowce do planety.
	*
	* Metoda dodaje Surowce do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
	* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
	* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
	*/
	bool dodajObiekt( shared_ptr< Surowce > obiekt );
	
	/**
	* \brief Metoda ustawia w�a�ciciela planety.
	*
	* Metoda zamienia bierz�cego w�a�ciciela na podanego w parametrze.
	* \param[in] uzytkownik - Wska�nik na u�ytkownika.
	*/
	void ustawWlasciciela( Uzytkownik* uzytkownik );

	/**
	* \brief Metoda pobiera w�a�ciciela.
	*
	*\return Wska�nika na w�a�ciciela.
	*/
	Uzytkownik* pobierzWlasciciela( ) const;

	/* TODO: do pozbycia si�*/
	shared_ptr<ObiektBazowy> pustyObiektBase; /// Pusty obiekt bazowy
	ObiektBazowyInfo pustyobiekBaseInfo; /// Pusty obiekt bazowy info.
	/* ------ */

	Licznik licznikIdentyfikatorowFloty_; /// Licznik identyfikator�w flot.
	Uzytkownik* wlasciciel_; /// W�a�ciciel planety.

	ListaSurowcow listaSurowcow_; /// Lista surowc�w planety.
	ListaStatkow listaStatkow_; /// Lista statk�w planety
	ListaTechnologii listaTechnologii_; /// Lista tehcnologii planety.
	ListaBudynkow listaBudynkow_; /// Lista budynk�w planety.
	ListaObiektow listaObiektow_; /// Lista wszystkich obiekt�w planety.
	ListaObiektowZaladunkowych listaObiektowZaladunkowych_; /// Lista obiekt�w za�adunkowych planety.
	ListaFlot listaFlot_; /// Lista flot planety.
};
