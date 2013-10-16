#pragma once
#include <random>
#include "UkladSloneczny.h"
#include "Planeta.h"
#include "Licznik.h"

using namespace std;

class GeneratorUkladow :
	virtual public LoggerInterface,
	public Serializacja
{
public:
	const static Identyfikator LICZNIK_PLANET_ID;
	const static Identyfikator LICZNIK_UKLADOW_ID;
	const static Identyfikator LICZNIK_GALAKTYK_ID;
	
	const static SPG::Dystans SREDNICA_GWIAZDY_MIN;
	const static SPG::Dystans SREDNICA_GWIAZDY_MAX;
	const static double SREDNICA_GWIAZDY_PARAM_ALFA;
	const static double SREDNICA_GWIAZDY_PARAM_BETA;

	const static SPG::Temperatura TEMPERATURA_GWIAZDY_MIN;
	const static SPG::Temperatura TEMPERATURA_GWIAZDY_MAX;
	const static double TEMPERATURA_GWIAZDY_PROCENT_SREDNICY;
	const static double TEMPERATURA_GWIAZDY_PROCENT_STALY;
	const static double TEMPERATURA_GWIAZDY_PROCENT_LOSOWY;
	
	const static int ILOSC_PLANET_MIN;
	const static int ILOSC_PLANET_MAX;
	const static double ILOSC_PLANET_PARAM;

	const static SPG::Dystans SREDNICA_PLANETY_MIN;
	const static SPG::Dystans SREDNICA_PLANETY_MAX;
	const static double SREDNICA_PLANETY_ODCHYLENIE;
	const static double SREDNICA_PLANETY_PRZESUNIECIE;
	const static double SREDNICA_PLANETY_ROZCIAGNIECIE;

	const static SPG::Dystans ODLEGLOSC_MIEDZYPLANETARNA_MIN;
	const static SPG::Dystans ODLEGLOSC_MIEDZYPLANETARNA_MAX;

	const static SPG::Temperatura TEMPERATURA_PLANETY_MAX;

	const static SPG::Fluktuacja POWIERZCHNIA_UZYTKOWA_MIN;
	const static SPG::Fluktuacja POWIERZCHNIA_UZYTKOWA_MAX;

	const static SPG::Fluktuacja POWIERZCHNIA_WODY_MAX;

	GeneratorUkladow();
	~GeneratorUkladow();

	shared_ptr<UkladSloneczny> generujUklad() const;
	shared_ptr<Planeta> generujPlanete( const Dystans& odlegloscOdCentrum, const Moc& mocGwiazdy ) const;

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
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override;

private:

	mutable random_device generator;
	gamma_distribution<SPG::Dystans> dystrybutorSrednicyGwiazdy;
	binomial_distribution<int> dystrybutorIlosciPlanet;
	uniform_real_distribution<SPG::Fluktuacja>  dystrybucjaPowierzchniUzytkowej;
	mutable Licznik licznikIdPlanet;
	mutable Licznik licznikIdUkladow;
	mutable Licznik licznikIdGalaktyk;

	SPG::Dystans generujSredniceGwiazdy() const;

	SPG::Dystans generujSrednicePlanety( const Dystans& odlegloscOdCentrum ) const;

	SPG::Temperatura generujTemperatureGwiazdy( SPG::Dystans srednica ) const;

	SPG::Temperatura generujTemperaturePlanety( const Dystans& odlegloscOdCentrum, const Moc& mocGwiazdy ) const;
};

