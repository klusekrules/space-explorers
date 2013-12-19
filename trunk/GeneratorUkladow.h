#pragma once
#include <random>
#include "UkladSloneczny.h"
#include "Planeta.h"
#include "Licznik.h"
#include "Galaktyka.h"

using namespace std;

/**
* \brief Klasa generuj�ca lokacje
*
* Klasa generuje lokacje takie jak galaktyki, uk�ady s�oneczne oraz planety.
* \author Daniel Wojdak
* \version 1
* \date 18-10-2013
*/
class GeneratorUkladow :
	virtual public LoggerInterface,
	public Serializacja
{
public:
	const static Identyfikator LICZNIK_PLANET_ID; /// Identyfikator licznika planet
	const static Identyfikator LICZNIK_UKLADOW_ID; /// Identyfikator licznika uk�ad�w s�onecznych
	const static Identyfikator LICZNIK_GALAKTYK_ID;/// identyfikator licznika galaktyk
	
	const static SPG::Dystans SREDNICA_GWIAZDY_MIN; /// Minimalna �rednica gwiazdy
	const static SPG::Dystans SREDNICA_GWIAZDY_MAX; /// Maksymalna �rednica gwiazdy
	const static double SREDNICA_GWIAZDY_PARAM_ALFA; /// Parametr generatora losowego gwiazdy.
	const static double SREDNICA_GWIAZDY_PARAM_BETA; /// Parametr generatora losowego gwiazdy.

	const static SPG::Temperatura TEMPERATURA_GWIAZDY_MIN; /// Minimalna temperatura gwiazdy
	const static SPG::Temperatura TEMPERATURA_GWIAZDY_MAX; /// Maksymalna temperatura gwiazdy
	const static double TEMPERATURA_GWIAZDY_PROCENT_SREDNICY; /// Procent �rednicy w wyliczniu temperatury gwiazdy.
	const static double TEMPERATURA_GWIAZDY_PROCENT_STALY; /// Sta�y procent temperatury gwiazdy
	const static double TEMPERATURA_GWIAZDY_PROCENT_LOSOWY; /// Procent losowy temperatury gwiazdy.
	
	const static int ILOSC_PLANET_MIN; /// Minimalna ilo�� planet w uk�adzie
	const static int ILOSC_PLANET_MAX; /// Maksymlana ilo�� planet w uk�adzie.
	const static double ILOSC_PLANET_PARAM; /// Parametr generatora ilo�ci planet.

	const static SPG::Dystans SREDNICA_PLANETY_MIN; /// Minimalna �rednica planety
	const static SPG::Dystans SREDNICA_PLANETY_MAX; /// Maksymlana �rednica planety
	const static double SREDNICA_PLANETY_ODCHYLENIE; /// Parametr generatora �rednicy planety.
	const static double SREDNICA_PLANETY_PRZESUNIECIE; /// Parametr generatora �rednicy planety.
	const static double SREDNICA_PLANETY_ROZCIAGNIECIE; /// Parametr generatora �rednicy planety.

	const static SPG::Dystans ODLEGLOSC_MIEDZYPLANETARNA_MIN; /// Minimalna odleg�o�� miedzyplanetarna
	const static SPG::Dystans ODLEGLOSC_MIEDZYPLANETARNA_MAX; /// Maksymalna odleg�o�� mi�dzyplanetarna

	const static SPG::Temperatura TEMPERATURA_PLANETY_MAX; /// Maksymlana temperatura na planecie.

	const static SPG::Fluktuacja POWIERZCHNIA_UZYTKOWA_MIN; /// Minimalny procent powierzchni u�ytkowej na planecie.
	const static SPG::Fluktuacja POWIERZCHNIA_UZYTKOWA_MAX; /// Maksymalny procent powierchni u�ytkowej na planecie.

	const static SPG::Fluktuacja POWIERZCHNIA_WODY_MAX; /// Maksymalny procent powierzchni zajmowanej przez wod�.

	const static int ILOSC_UKLADOW_MIN; /// Minimalna ilo�� uk�ad�w s�onecznych w galaktyce
	const static int ILOSC_UKLADOW_MAX; /// Maksymalna ilo�� uk�ad�w s�onecznych w galaktyce

	/**
	* \brief Konstruktor.
	*/
	GeneratorUkladow();

	/**
	* \brief Destruktor.
	*/
	virtual ~GeneratorUkladow();

	/**
	* \brief Metoda generuj�ca galaktyk�.
	*
	* Metoda generuje galaktyk�.
	* \return Wska�nik na galaktyk�.
	*/
	shared_ptr<Galaktyka> generujGalaktyke() const;

	/**
	* \brief Metoda generuj�ca uk�ad s�oneczny.
	*
	* Metoda generuje uk�ad s�oneczny.
	* \param[in] identyfikatorGalatyki - Numer identyfikuj�cy galaktyk�.
	* \return Wska�nik na uk�ad s�oneczny.
	*/
	shared_ptr<UkladSloneczny> generujUklad( const Identyfikator& identyfikatorGalatyki ) const;

	/**
	* \brief Metoda generuj�ca planet�.
	*
	* Metoda generuje planet�.
	* \param[in] odlegloscOdCentrum - odleg�o�� planety od �rodka uk�adu s�onecznego.
	* \param[in] mocGwiazdy - moc gwiazdy znajduj�cej si� u uk�adzie.
	* \param[in] identyfikatorUkladu - Numer identyfikuj�cy uk�ad s�oneczny
	* \return Wska�nik na planet�.
	*/
	shared_ptr<Planeta> generujPlanete( const Dystans& odlegloscOdCentrum, const Moc& mocGwiazdy, const Identyfikator& identyfikatorUkladu ) const;

	/**
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
	* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( tinyxml2::XMLElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	* \warning Metoda nie modyfikuje w�z�a.
	* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
	*/
	bool odczytaj( tinyxml2::XMLElement* wezel ) override;

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override;

private:
	
	mutable random_device generator; /// Silnik generatora.
	gamma_distribution<SPG::Dystans> dystrybutorSrednicyGwiazdy; /// Generator �rednicy gwiazdy
	binomial_distribution<int> dystrybutorIlosciPlanet; /// Genetator ilo�ci planet w uk�adzie s�onecznym
	uniform_int_distribution<int> dystrybutorIlosciUkladow; /// Generator ilo�ci uk�ad�w.
	uniform_real_distribution<SPG::Fluktuacja>  dystrybucjaPowierzchniUzytkowej; /// Generator procentu powierzchni u�ytkowej.
	mutable Licznik licznikIdPlanet; /// Licznik planet
	mutable Licznik licznikIdUkladow; /// Licznik uk�ad�w s�onecznych
	mutable Licznik licznikIdGalaktyk; /// Licznik galaktyk

	/**
	* \brief Metoda generuj�ca �rednic� gwiazdy
	*
	* Metoda generuje �rednic� gwiazdy.
	* \return �rednica gwiazdy w mln km.
	*/
	SPG::Dystans generujSredniceGwiazdy() const;

	/**
	* \brief Metoda generuj�ca �rednic� planety
	*
	* Metoda generuje �rednic� planety.
	* \param[in] odlegloscOdCentrum - Odleg�o�� planety od �rodka uk�adu s�onecznego.
	* \return �rednica planety w mln km.
	*/
	SPG::Dystans generujSrednicePlanety( const Dystans& odlegloscOdCentrum ) const;

	/**
	* \brief Metoda generuj�ca temperatur� gwiazdy.
	*
	* Metoda generuje temperatur� gwiazdy.
	* \param[in] srednica - �rednica gwiazdy.
	* \return Temperatura gwiazdy w kelwinach.
	*/
	SPG::Temperatura generujTemperatureGwiazdy( SPG::Dystans srednica ) const;

	/**
	* \brief Metoda generuj�ca temperatur� planety.
	*
	* Metoda generuje temperatur� planety.
	* \param[in] odlegloscOdCentrum - Odleg�o�� planety od �rodka uk�adu s�onecznego.	
	* \param[in] mocGwiazdy - moc gwiazdy znajduj�cej si� u uk�adzie.
	* \return Temperatura planety w kelwinach.
	*/
	SPG::Temperatura generujTemperaturePlanety( const Dystans& odlegloscOdCentrum, const Moc& mocGwiazdy ) const;
};
