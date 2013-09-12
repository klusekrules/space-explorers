#pragma once
#include "Logger\LoggerInterface.h"
#include "Serializacja.h"
#include "Bazowa.h"
#include "Statek.h"
#include "Klucz.h"

class Planeta;

/**
* \brief Klasa reprezentuj�ca flote lec�c� miedzy planetami.
*
* Klasa zarz�dza flot�. Pozwala na dodawanie Statk�w i �adunk�w. 
* \author Daniel Wojdak
* \version 1
* \date 25-07-2013
*/
class Flota : 
	public Bazowa,
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	enum CelPodrozy{
		Zwiad,
		Atak,
		Transport,
		Stacjonowanie,
		Szczatki,
		Ekspedycja,
		Powrot
	};

	typedef map< Klucz , shared_ptr<Statek> > ListaStatkow;

	/**
	* \brief Konstruktor.
	*
	* \param[in] identyfikatorFloty - Identyfikator floty.
	* \param[in] planetaPoczatkowa - Identyfikator planety pocz�tkowej.
	* \param[in] planetaDocelowa - Identyfikator planety docelowej.
	* \param[in] celPodrozy - cel podr�y floty.
	*/
	Flota(const Identyfikator& identyfikatorFloty, const Identyfikator& planetaPoczatkowa, const Identyfikator& planetaDocelowa, CelPodrozy celPodrozy );

	/**
	* \brief Destruktor.
	*/
	virtual ~Flota(void);

	/**
	* \brief Metoda dodaje statek do floty.
	* 
	* Metoda dodaje kolejny statek do floty.
	* \param[in] statek - Wska�nik do statku, kt�ry ma zosta� dodany do floty.
	* \return true je�eli uda si� doda� statek. false w przeciwnym wypadku.
	*/
	bool dodajStatek( shared_ptr<Statek> statek );

	/**
	* \brief Metoda dodaje obiekt do �adowni floty.
	* 
	* Metoda dodaje surowiec do �adowni do floty.
	* \param[in] obiekt - Wska�nik do surowca, kt�ry ma zosta� dodany do �adowni floty.
	* \return true je�eli uda si� doda� surowiec. false w przeciwnym wypadku.
	*/
	bool dodajLadunek( shared_ptr<Surowce> obiekt );

	/**
	* \brief Metoda dodaje statek do hangaru floty.
	* 
	* Metoda dodaje statek do hangaru do floty.
	* \param[in] obiekt - Wska�nik do statku, kt�ry ma zosta� dodany do hangaru floty.
	* \return true je�eli uda si� doda� statek. false w przeciwnym wypadku.
	*/
	bool dodajLadunek( shared_ptr<Statek> obiekt );

	/**
	* \brief Metoda pobieraj�ca dost�pne miejsce �adowni.
	*
	* Metoda pobiera wolne miejsce znajduj�ce si� na wszysktich statkach floty.
	* \return Obj�to�� jaka jest dost�pna na statkach.
	*/
	Objetosc pobierzDostepneMiejsceLadowni() const;

	/**
	* \brief Metoda pobieraj�ca dost�pne miejsce hangaru.
	*
	* Metoda pobiera wolne miejsce znajduj�ce si� na wszysktich statkach floty.
	* \return Obj�to�� jaka jest dost�pna na statkach.
	*/
	Objetosc pobierzDostepneMiejsceHangaru() const;

	/**
	* \brief Metoda ustawiaj�ca punkt docelowy
	* 
	* Metoda ustawia identyfikator planety docelowej do kt�rej zmierza flota.
	* \param[in] identyfikatorPlanety - Identyfikator planety docelowej.
	*/
	void ustawPlaneteDocelowa( const Identyfikator& identyfikatorPlanety );

	/**
	* \brief Metoda ustawiaj�ca punkt pocz�tkowy
	* 
	* Metoda ustawia identyfikator planety pocz�tkowej z kt�rej zmierza flota.
	* \param[in] identyfikatorPlanety - Identyfikator planety pocz�tkowej.
	*/
	void ustawPlanetePoczatkowa( const Identyfikator& identyfikatorPlanety );

	/**
	* \brief Metoda pobiera identyfikaktor punktu docelowego.
	* 
	* Metoda pobiera identyfikator planety docelowej do kt�rej zmierza flota.
	* \return Identyfikator planety docelowej.
	*/
	Identyfikator pobierzPlaneteDocelowa() const;

	/**
	* \brief Metoda pobiera indentyfikator punktu pocz�tkowego.
	* 
	* Metoda pobiera identyfikator planety pocz�tkowej z kt�rej zmierza flota.
	* \return Identyfikator planety pocz�tkowej.
	*/
	Identyfikator pobierzPlanetePoczatkowa() const;

	/**
	* \brief Metoda ustwia cel podr�y.
	*
	* Metoda ustawia cel podr�y floty.
	* \param[in] cel - Cel podr�y floty
	*/
	void ustawCelPodrozy( CelPodrozy cel );

	/**
	* \brief Metoda roz�adowuje zawarto�� �adowni na planecie.
	*
	* Metoda roz�adowuje zawarto�� �adowni na planecie. W zale�no�ci o celu mo�e to by� r�zna planeta.
	* \return true je�eli uda sie rozladowa� �adownie, false w przeciwnym przypadku.
	*/
	bool rozladujLadownieNaPlanecie();

	/**
	* \brief Metoda prowadza flot� do planety
	*
	* Metoda wprowadza flot� do planety. Nie usuwa wska�nika floty z planety do kt�rej flota jest przypisana.
	* \return true je�eli uda sie wprowadzi� flot�, false w przeciwnym przypadku.
	*/
	bool rozladujFloteNaPlanecie();

	/**
	* \brief Metoda zawraca flot�
	*
	* Metoda ustawia misje na powr�t.
	* \return true je�eli zostanie ustawiona misja jako powr�t. false je�eli misja jest ju� ustawiona na powr�t.
	*/
	bool zawrocFlote();

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
	string napis()const override;
private:
	ListaStatkow lista_; /// Lista statk�w nale��cych do floty.
	Identyfikator planetaPoczatkowa_; /// Identyfikator planety poczatkowej.
	Identyfikator planetaDocelowa_; /// Identyfikator planety docelowej.
	CelPodrozy celPodrozy_; /// Cel podr�y floty.
};
