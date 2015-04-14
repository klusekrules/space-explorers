#pragma once
#include <random>
#include "UkladSloneczny.h"
#include "Planeta.h"
#include "Licznik.h"
#include "Galaktyka.h"

namespace SpEx{
	/**
	* \brief Klasa generuj�ca lokacje
	*
	* Klasa generuje lokacje takie jak galaktyki, uk�ady s�oneczne oraz planety.
	* \author Daniel Wojdak
	* \version 1
	* \date 18-10-2013
	*/
	class GeneratorUkladow :
		virtual public SLog::LoggerInterface,
		public Serializacja
	{
	public:
		const static STyp::Identyfikator LICZNIK_PLANET_ID; /// Identyfikator licznika planet
		const static STyp::Identyfikator LICZNIK_UKLADOW_ID; /// Identyfikator licznika uk�ad�w s�onecznych
		const static STyp::Identyfikator LICZNIK_GALAKTYK_ID;/// identyfikator licznika galaktyk

		const static STyp::SPG::Dystans SREDNICA_GWIAZDY_MIN; /// Minimalna �rednica gwiazdy
		const static STyp::SPG::Dystans SREDNICA_GWIAZDY_MAX; /// Maksymalna �rednica gwiazdy
		const static double SREDNICA_GWIAZDY_PARAM_ALFA; /// Parametr generatora losowego gwiazdy.
		const static double SREDNICA_GWIAZDY_PARAM_BETA; /// Parametr generatora losowego gwiazdy.

		const static STyp::SPG::Temperatura TEMPERATURA_GWIAZDY_MIN; /// Minimalna temperatura gwiazdy
		const static STyp::SPG::Temperatura TEMPERATURA_GWIAZDY_MAX; /// Maksymalna temperatura gwiazdy
		const static double TEMPERATURA_GWIAZDY_PROCENT_SREDNICY; /// Procent �rednicy w wyliczniu temperatury gwiazdy.
		const static double TEMPERATURA_GWIAZDY_PROCENT_STALY; /// Sta�y procent temperatury gwiazdy
		const static double TEMPERATURA_GWIAZDY_PROCENT_LOSOWY; /// Procent losowy temperatury gwiazdy.

		const static int ILOSC_PLANET_MIN; /// Minimalna ilo�� planet w uk�adzie
		const static int ILOSC_PLANET_MAX; /// Maksymlana ilo�� planet w uk�adzie.
		const static double ILOSC_PLANET_PARAM; /// Parametr generatora ilo�ci planet.

		const static STyp::SPG::Dystans SREDNICA_PLANETY_MIN; /// Minimalna �rednica planety
		const static STyp::SPG::Dystans SREDNICA_PLANETY_MAX; /// Maksymlana �rednica planety
		const static double SREDNICA_PLANETY_ODCHYLENIE; /// Parametr generatora �rednicy planety.
		const static double SREDNICA_PLANETY_PRZESUNIECIE; /// Parametr generatora �rednicy planety.
		const static double SREDNICA_PLANETY_ROZCIAGNIECIE; /// Parametr generatora �rednicy planety.

		const static STyp::SPG::Dystans ODLEGLOSC_MIEDZYPLANETARNA_MIN; /// Minimalna odleg�o�� miedzyplanetarna
		const static STyp::SPG::Dystans ODLEGLOSC_MIEDZYPLANETARNA_MAX; /// Maksymalna odleg�o�� mi�dzyplanetarna

		const static STyp::SPG::Temperatura TEMPERATURA_PLANETY_MAX; /// Maksymlana temperatura na planecie.

		const static STyp::SPG::Fluktuacja POWIERZCHNIA_UZYTKOWA_MIN; /// Minimalny procent powierzchni u�ytkowej na planecie.
		const static STyp::SPG::Fluktuacja POWIERZCHNIA_UZYTKOWA_MAX; /// Maksymalny procent powierchni u�ytkowej na planecie.

		const static STyp::SPG::Fluktuacja POWIERZCHNIA_WODY_MAX; /// Maksymalny procent powierzchni zajmowanej przez wod�.

		const static int ILOSC_UKLADOW_MIN; /// Minimalna ilo�� uk�ad�w s�onecznych w galaktyce
		const static int ILOSC_UKLADOW_MAX; /// Maksymalna ilo�� uk�ad�w s�onecznych w galaktyce

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		GeneratorUkladow();

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~GeneratorUkladow() = default;

		/**
		* \brief Metoda generuj�ca galaktyk�.
		*
		* Metoda generuje galaktyk�.
		* \return Wska�nik na galaktyk�.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		std::shared_ptr<Galaktyka> generujGalaktyke() const;

		/**
		* \brief Metoda generuj�ca uk�ad s�oneczny.
		*
		* Metoda generuje uk�ad s�oneczny.
		* \param[in] identyfikatorGalatyki - Numer identyfikuj�cy galaktyk�.
		* \return Wska�nik na uk�ad s�oneczny.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		std::shared_ptr<UkladSloneczny> generujUklad(const STyp::Identyfikator& identyfikatorGalatyki) const;

		/**
		* \brief Metoda generuj�ca planet�.
		*
		* Metoda generuje planet�.
		* \param[in] odlegloscOdCentrum - odleg�o�� planety od �rodka uk�adu s�onecznego.
		* \param[in] mocGwiazdy - moc gwiazdy znajduj�cej si� u uk�adzie.
		* \param[in] identyfikatorUkladu - Numer identyfikuj�cy uk�ad s�oneczny
		* \return Wska�nik na planet�.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		std::shared_ptr<Planeta> generujPlanete(const STyp::Dystans& odlegloscOdCentrum, const STyp::Moc& mocGwiazdy, const STyp::Identyfikator& identyfikatorUkladu) const;

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

		/**
		* \brief Metoda odczytuj�ca.
		*
		* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
		* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
		* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
		* \warning Metoda nie modyfikuje w�z�a.
		* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
		* \return Napis zawieraj�cy opis klasy.
		*/
		std::string napis() const override;

	private:

		mutable std::random_device generator; /// Silnik generatora.
		std::gamma_distribution<STyp::SPG::Dystans> dystrybutorSrednicyGwiazdy; /// Generator �rednicy gwiazdy
		std::binomial_distribution<int> dystrybutorIlosciPlanet; /// Genetator ilo�ci planet w uk�adzie s�onecznym
		std::uniform_int_distribution<int> dystrybutorIlosciUkladow; /// Generator ilo�ci uk�ad�w.
		std::uniform_real_distribution<STyp::SPG::Fluktuacja>  dystrybucjaPowierzchniUzytkowej; /// Generator procentu powierzchni u�ytkowej.
		mutable Licznik licznikIdPlanet; /// Licznik planet
		mutable Licznik licznikIdUkladow; /// Licznik uk�ad�w s�onecznych
		mutable Licznik licznikIdGalaktyk; /// Licznik galaktyk

		/**
		* \brief Metoda generuj�ca �rednic� gwiazdy
		*
		* Metoda generuje �rednic� gwiazdy.
		* \return �rednica gwiazdy w mln km.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		STyp::SPG::Dystans generujSredniceGwiazdy() const;

		/**
		* \brief Metoda generuj�ca �rednic� planety
		*
		* Metoda generuje �rednic� planety.
		* \param[in] odlegloscOdCentrum - Odleg�o�� planety od �rodka uk�adu s�onecznego.
		* \return �rednica planety w mln km.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		STyp::SPG::Dystans generujSrednicePlanety(const STyp::Dystans& odlegloscOdCentrum) const;

		/**
		* \brief Metoda generuj�ca temperatur� gwiazdy.
		*
		* Metoda generuje temperatur� gwiazdy.
		* \param[in] srednica - �rednica gwiazdy.
		* \return Temperatura gwiazdy w kelwinach.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		STyp::SPG::Temperatura generujTemperatureGwiazdy(STyp::SPG::Dystans srednica) const;

		/**
		* \brief Metoda generuj�ca temperatur� planety.
		*
		* Metoda generuje temperatur� planety.
		* \param[in] odlegloscOdCentrum - Odleg�o�� planety od �rodka uk�adu s�onecznego.
		* \param[in] mocGwiazdy - moc gwiazdy znajduj�cej si� u uk�adzie.
		* \return Temperatura planety w kelwinach.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		STyp::SPG::Temperatura generujTemperaturePlanety(const STyp::Dystans& odlegloscOdCentrum, const STyp::Moc& mocGwiazdy) const;
	};
}
