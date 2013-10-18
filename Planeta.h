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
#include "Obrona.h"
#include "Temperatura.h"

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
	typedef Klucz Indeks;
	typedef map< Indeks , shared_ptr< ObiektBazowy > > ListaObiektow;
	typedef map< Indeks , shared_ptr< Obiekt > > ListaObiektowZaladunkowych;
	typedef map< Indeks , shared_ptr< Budynek > > ListaBudynkow;
	typedef map< Indeks , shared_ptr< Technologia > > ListaTechnologii;
	typedef map< Indeks , shared_ptr< Statek > > ListaStatkow;
	typedef map< Indeks , shared_ptr< Obrona > > ListaObrona;
	typedef map< Indeks , shared_ptr< Surowce > > ListaSurowcow;
	typedef map< Identyfikator , shared_ptr< Flota > > ListaFlot;
	typedef map< Indeks , Ilosc > ListaZasobow;
	
	/**
	* \brief Konstruktor.
	*
	* \param[in] identyfikator - Identyfikator planety.
	* \param[in] identyfikatorUkladu - Numer identyfikuj¹cy uk³ad s³oneczny
	*/
	Planeta(const Identyfikator& identyfikator, const Identyfikator& identyfikatorUkladu);

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
	const ObiektBazowy& pobierzObiekt(const Indeks& identyfikator) const;

	/**
	* \brief Metoda pobiera obiekt o podanym identyfikatorze i najwiêkszym poziomie.
	* 
	* Metoda pobiera z planety obiekt o podanym identyfikatorze i najwiêkszym poziomie.
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
	const Statek& pobierzStatek(const Indeks& identyfikator) const;

	/**
	* \brief Metoda pobiera obronê o podanym identyfikatorze.
	* 
	* Metoda pobiera z planety obronê o podanym identyfikatorze.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \return Referencja do obiektu.
	*/
	const Obrona& pobierzObrone(const Indeks& identyfikator) const;

	/**
	* \brief Metoda pobiera tehcnologie o podanym identyfikatorze.
	* 
	* Metoda pobiera z planety tehcnologie o podanym identyfikatorze.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \return Referencja do obiektu.
	*/
	const Technologia& pobierzTechnologie(const Indeks& identyfikator) const;

	/**
	* \brief Metoda pobiera budynek o podanym identyfikatorze.
	* 
	* Metoda pobiera z planety budynek o podanym identyfikatorze.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \return Referencja do obiektu.
	*/
	const Budynek& pobierzBudynek(const Indeks& identyfikator) const;
	
	/**
	* \brief Metoda buduje obiekt na planecie.
	* 
	* Metoda buduje obiekt o podanym identyfikatorze i iloœci na planecie.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \param[in] ilosc - Atrybut iloœci tworzonego obieku.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybuduj( const Indeks& identyfikator, const Ilosc& ilosc );

	/**
	* \brief Metoda buduje obiekt na planecie.
	* 
	* Metoda buduje obiekt o podanym identyfikatorze, odczytuj¹c dane z wêz³a XML.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \param[in] wezel - Wezel xml z którego maj¹ zaostaæ pobrane dane.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybuduj( const Indeks& identyfikator, TiXmlElement* wezel );

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
	bool przeniesDoFloty(const Identyfikator& flota, const Indeks& obiekt, const Ilosc& ilosc );

	/**
	* \brief Metoda przenoœci obiekt do ³adowni floty.
	*
	* Metoda przenosi obiekt z planety do ³adowni floty.
	* \param[in] flota - Identyfikator floty do ³adowni której ma zostaæ przeniesiony obiekt.
	* \param[in] obiekt - Identyfikator obiektu, który ma byc przenisiony do ³adowni floty.
	* \param[in] ilosc - Iloœæ obiektów do przeniesienia.
	* \return true je¿eli uda siê przenieœæ obiekt, false w przeciwnym wypadku.
	*/
	bool zaladujSurowceNaFlote( const Identyfikator& flota, const Indeks& obiekt, const Ilosc& ilosc );

	/**
	* \brief Metoda przenoœci obiekt do hangaru floty.
	*
	* Metoda przenosi obiekt z planety do hangaru floty.
	* \param[in] flota - Identyfikator floty do hangaru której ma zostaæ przeniesiony obiekt.
	* \param[in] obiekt - Identyfikator obiektu, który ma byc przenisiony do hangaru floty.
	* \param[in] ilosc - Iloœæ obiektów do przeniesienia.
	* \return true je¿eli uda siê przenieœæ obiekt, false w przeciwnym wypadku.
	*/
	bool zaladujStatekNaFlote( const Identyfikator& flota, const Indeks& obiekt, const Ilosc& ilosc );

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
	* \brief Metoda pobieraj¹ca nazwê planety.
	*
	* Metoda pobiera nazwê planety
	* \return Nazwa planety.
	*/
	Tekst pobierzNazwePlanety() const;

	/**
	* \brief Metoda ustawiaj¹ca nazwê planety.
	*
	* Metoda ustawia nazwê planety
	* \param[in] nazwa - Nowa nazwa planety.
	*/
	void ustawNazwePlanety( const Tekst& nazwa );

	/**
	* \brief Metoda ustawia temperaturê.
	* 
	* Metoda ustawiaj¹ca œredni¹ temperaturê na planecie.
	* \param[in] temperatura - wartoœæ temperatury w kelwinach, jaka ma byæ ustawiona w obiekcie.
	*/
	void ustawTemperature( const Temperatura& temperatura );

	/**
	* \brief Metoda ustawia œrednicê.
	* 
	* Metoda ustawiaj¹ca œrednicê planety.
	* \param[in] srednica - wartoœæ srednicy w mln km, jaka ma byæ ustawiona w obiekcie.
	*/
	void ustawSrednice( const Dystans& srednica );

	/**
	* \brief Metoda ustawia odleg³oœæ od œrodka uk³adu s³onecznego.
	* 
	* Metoda ustawiaj¹ca odleg³oœæ planety od œrodka uk³adu s³onecznego.
	* \param[in] odleglosc - wartoœæ odleglosci w mln km, jaka ma byæ ustawiona w obiekcie.
	*/
	void ustawOdlegloscOdSrodkaUkladu( const Dystans& odleglosc );

	/**
	* \brief Metoda przeliczaj¹ca powierzchnie.
	*
	* Metoda przelicza powierzchniê na planecie wed³ug podanych proporcji.
	* \param[in] procentWody - procenty powierzchni bêd¹cej wod¹.
	* \param[in] procentUzytkowa - procent powierzchni u¿ytkowej.
	* \return true je¿eli argumety s¹ w poprawnym zakresie false w przeciwnym wypadku.
	*/
	bool wyliczPowierzchnie( const Fluktuacja& procentWody, const Fluktuacja& procentUzytkowa );

	/**
	* \brief Metoda zwracaj¹ca identyfikator uk³adu rodzica.
	*
	* Metoda zwraca identyfikator uk³adu s³onecznego w którym znajduje sie planeta.
	* \return Identyfikator uk³adu.
	*/
	const Identyfikator& pobierzIdUkladu() const;

	/**
	* \brief Metoda czyœci zawartoœæ planety.
	* 
	* Metoda czyœci zawartoœæ planety. Usuwa tak¿e powi¹zanie z u¿ytkownikiem je¿eli takowe istnieje oraz zalogowany jest u¿ytkownik który jest przypisany do planety.
	* \todo Metoda do zmiany. Usuniêcie sprawdzania warunku tego samego u¿ytkownika. Przeniesienie tego w inne miejsce.
	*/
	void wyczyscZawartoscPlanety();

	/**
	* \brief Metoda zwracaj¹ca poziom obiektu.
	*
	* Metoda zwraca nawy¿szy poziom obiektu o podanym identyfikatorze.
	* \param[in] identyfikator - Numer identyfikuj¹cy obiekt.
	* \return Poziom obiektu lub 0 je¿eli nie znaleziono obiektu.
	*/
	Poziom pobierzPoziomObiektu( const Identyfikator& identyfikator ) const;

	/**
	* \brief Metoda zwracaj¹ca iloœæ obiektu.
	*
	* Metoda zwraca iloœæobiektu o podanym indeksie.
	* \param[in] indeks - Indeks obiekt.
	* \return Iloœæ obiektu lub 0 je¿eli nie znaleziono obiektu.
	*/
	Ilosc pobierzIloscObiektu( const Indeks& indeks ) const;
	
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
	* \brief Metoda dodaj¹ca Obronê do planety.
	*
	* Metoda dodaje Obronê do planety. Nie tworzy kopii. Sprawdza czy istnieje obrona o takim samym identyfikatorze.
	* \param[in] obiekt - Sprytny wskaŸnik na dodawany obiekt.
	* \return true je¿eli uda siê dodaæ obiekt, fasle w przeciwnym wypadku.
	*/
	bool dodajObiekt( shared_ptr< Obrona > obiekt );

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

	Licznik licznikIdentyfikatorowFloty_; /// Licznik identyfikatorów flot.
	Uzytkownik* wlasciciel_; /// W³aœciciel planety.

	ListaSurowcow listaSurowcow_; /// Lista surowców planety.
	ListaStatkow listaStatkow_; /// Lista statków planety
	ListaObrona listaObrona_; /// Lista statków planety
	ListaTechnologii listaTechnologii_; /// Lista tehcnologii planety.
	ListaBudynkow listaBudynkow_; /// Lista budynków planety.
	ListaObiektow listaObiektow_; /// Lista wszystkich obiektów planety.
	ListaObiektowZaladunkowych listaObiektowZaladunkowych_; /// Lista obiektów za³adunkowych planety.
	ListaFlot listaFlot_; /// Lista flot planety.

	/* Lista parametrów planety */
	Dystans srednicaPlanety_; /// Atrybut przechowuje informacje o œrednicy planety.
	Dystans odlegloscOdSlonca_; /// Atrybut przechowuje informacje o odleg³oœci planety od centrum uk³adu s³onecznego.
	//Predkosc predkoscKatowaPlanety_ ; /// Atrybut przechowuje informacje o prêdkoœci obiegu planety woko³o s³oñca.
	//Fluktuacja naslonecznieniePlanety_; /// Atrybut przechowuj¹cy informacje o nas³onecznieniu planety.
	//Fluktuacja wietrznoscPlanety_; /// Atrybut przechowuj¹cy informacje o natê¿eniu wiatrów na planecie.
	Temperatura temperaturaPlanety_; /// Atrybut przechowuj¹cy informacje o œredniej temperaturze planety.
	Powierzchnia calkowitaPowierzchniaPlanety_; /// Atrybut przehcowuj¹cy informacje o ca³kowitej powierzchni planety.
	Powierzchnia powierzchniaZajetaPrzezWode_; /// Atrybut przechowuj¹cy informacje o powierzchni planety zajêtej przez wodê.
	Powierzchnia powierzchniaLadow_; /// Atrybut przechowuj¹cy informacje o powierzchni planety zajêtej przez l¹dy.
	Powierzchnia powierzchniaUzytkowaLadow_; /// Atrybut przechowuj¹cy informacje o powierzchni u¿ytkowej planety.
	//ListaZasobow dostepneZasobyPlanety_; /// Lista zasobów jakie mo¿na wydobyæ na planecie.
	Tekst nazwaPlanety_; /// Nazwa planety.

	Identyfikator idUkladu_; /// Uk³ad s³oneczny w którym znajduje siê planeta.
	Tekst idUzytkownika_; /// Nazwa u¿ytkownika przypisanego do planety.
};
