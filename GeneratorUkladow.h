#pragma once
#include <random>
#include "UkladSloneczny.h"
#include "Planeta.h"
#include "Licznik.h"
#include "Galaktyka.h"

namespace SpEx{
	/**
	* \brief Klasa generuj¹ca lokacje
	*
	* Klasa generuje lokacje takie jak galaktyki, uk³ady s³oneczne oraz planety.
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
		const static STyp::Identyfikator LICZNIK_UKLADOW_ID; /// Identyfikator licznika uk³adów s³onecznych
		const static STyp::Identyfikator LICZNIK_GALAKTYK_ID;/// identyfikator licznika galaktyk

		const static STyp::SPG::Dystans SREDNICA_GWIAZDY_MIN; /// Minimalna œrednica gwiazdy
		const static STyp::SPG::Dystans SREDNICA_GWIAZDY_MAX; /// Maksymalna œrednica gwiazdy
		const static double SREDNICA_GWIAZDY_PARAM_ALFA; /// Parametr generatora losowego gwiazdy.
		const static double SREDNICA_GWIAZDY_PARAM_BETA; /// Parametr generatora losowego gwiazdy.

		const static STyp::SPG::Temperatura TEMPERATURA_GWIAZDY_MIN; /// Minimalna temperatura gwiazdy
		const static STyp::SPG::Temperatura TEMPERATURA_GWIAZDY_MAX; /// Maksymalna temperatura gwiazdy
		const static double TEMPERATURA_GWIAZDY_PROCENT_SREDNICY; /// Procent œrednicy w wyliczniu temperatury gwiazdy.
		const static double TEMPERATURA_GWIAZDY_PROCENT_STALY; /// Sta³y procent temperatury gwiazdy
		const static double TEMPERATURA_GWIAZDY_PROCENT_LOSOWY; /// Procent losowy temperatury gwiazdy.

		const static int ILOSC_PLANET_MIN; /// Minimalna iloœæ planet w uk³adzie
		const static int ILOSC_PLANET_MAX; /// Maksymlana iloœæ planet w uk³adzie.
		const static double ILOSC_PLANET_PARAM; /// Parametr generatora iloœci planet.

		const static STyp::SPG::Dystans SREDNICA_PLANETY_MIN; /// Minimalna œrednica planety
		const static STyp::SPG::Dystans SREDNICA_PLANETY_MAX; /// Maksymlana œrednica planety
		const static double SREDNICA_PLANETY_ODCHYLENIE; /// Parametr generatora œrednicy planety.
		const static double SREDNICA_PLANETY_PRZESUNIECIE; /// Parametr generatora œrednicy planety.
		const static double SREDNICA_PLANETY_ROZCIAGNIECIE; /// Parametr generatora œrednicy planety.

		const static STyp::SPG::Dystans ODLEGLOSC_MIEDZYPLANETARNA_MIN; /// Minimalna odleg³oœæ miedzyplanetarna
		const static STyp::SPG::Dystans ODLEGLOSC_MIEDZYPLANETARNA_MAX; /// Maksymalna odleg³oœæ miêdzyplanetarna

		const static STyp::SPG::Temperatura TEMPERATURA_PLANETY_MAX; /// Maksymlana temperatura na planecie.

		const static STyp::SPG::Fluktuacja POWIERZCHNIA_UZYTKOWA_MIN; /// Minimalny procent powierzchni u¿ytkowej na planecie.
		const static STyp::SPG::Fluktuacja POWIERZCHNIA_UZYTKOWA_MAX; /// Maksymalny procent powierchni u¿ytkowej na planecie.

		const static STyp::SPG::Fluktuacja POWIERZCHNIA_WODY_MAX; /// Maksymalny procent powierzchni zajmowanej przez wodê.

		const static int ILOSC_UKLADOW_MIN; /// Minimalna iloœæ uk³adów s³onecznych w galaktyce
		const static int ILOSC_UKLADOW_MAX; /// Maksymalna iloœæ uk³adów s³onecznych w galaktyce

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
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~GeneratorUkladow() = default;

		/**
		* \brief Metoda generuj¹ca galaktykê.
		*
		* Metoda generuje galaktykê.
		* \return WskaŸnik na galaktykê.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		std::shared_ptr<Galaktyka> generujGalaktyke() const;

		/**
		* \brief Metoda generuj¹ca uk³ad s³oneczny.
		*
		* Metoda generuje uk³ad s³oneczny.
		* \param[in] identyfikatorGalatyki - Numer identyfikuj¹cy galaktykê.
		* \return WskaŸnik na uk³ad s³oneczny.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		std::shared_ptr<UkladSloneczny> generujUklad(const STyp::Identyfikator& identyfikatorGalatyki) const;

		/**
		* \brief Metoda generuj¹ca planetê.
		*
		* Metoda generuje planetê.
		* \param[in] odlegloscOdCentrum - odleg³oœæ planety od œrodka uk³adu s³onecznego.
		* \param[in] mocGwiazdy - moc gwiazdy znajduj¹cej siê u uk³adzie.
		* \param[in] identyfikatorUkladu - Numer identyfikuj¹cy uk³ad s³oneczny
		* \return WskaŸnik na planetê.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		std::shared_ptr<Planeta> generujPlanete(const STyp::Dystans& odlegloscOdCentrum, const STyp::Moc& mocGwiazdy, const STyp::Identyfikator& identyfikatorUkladu) const;

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

		/**
		* \brief Metoda odczytuj¹ca.
		*
		* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
		* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
		* \warning Metoda nie modyfikuje wêz³a.
		* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
		* \return Napis zawieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	private:

		mutable std::random_device generator; /// Silnik generatora.
		std::gamma_distribution<STyp::SPG::Dystans> dystrybutorSrednicyGwiazdy; /// Generator œrednicy gwiazdy
		std::binomial_distribution<int> dystrybutorIlosciPlanet; /// Genetator iloœci planet w uk³adzie s³onecznym
		std::uniform_int_distribution<int> dystrybutorIlosciUkladow; /// Generator iloœci uk³adów.
		std::uniform_real_distribution<STyp::SPG::Fluktuacja>  dystrybucjaPowierzchniUzytkowej; /// Generator procentu powierzchni u¿ytkowej.
		mutable Licznik licznikIdPlanet; /// Licznik planet
		mutable Licznik licznikIdUkladow; /// Licznik uk³adów s³onecznych
		mutable Licznik licznikIdGalaktyk; /// Licznik galaktyk

		/**
		* \brief Metoda generuj¹ca œrednicê gwiazdy
		*
		* Metoda generuje œrednicê gwiazdy.
		* \return Œrednica gwiazdy w mln km.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		STyp::SPG::Dystans generujSredniceGwiazdy() const;

		/**
		* \brief Metoda generuj¹ca œrednicê planety
		*
		* Metoda generuje œrednicê planety.
		* \param[in] odlegloscOdCentrum - Odleg³oœæ planety od œrodka uk³adu s³onecznego.
		* \return Œrednica planety w mln km.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		STyp::SPG::Dystans generujSrednicePlanety(const STyp::Dystans& odlegloscOdCentrum) const;

		/**
		* \brief Metoda generuj¹ca temperaturê gwiazdy.
		*
		* Metoda generuje temperaturê gwiazdy.
		* \param[in] srednica - œrednica gwiazdy.
		* \return Temperatura gwiazdy w kelwinach.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		STyp::SPG::Temperatura generujTemperatureGwiazdy(STyp::SPG::Dystans srednica) const;

		/**
		* \brief Metoda generuj¹ca temperaturê planety.
		*
		* Metoda generuje temperaturê planety.
		* \param[in] odlegloscOdCentrum - Odleg³oœæ planety od œrodka uk³adu s³onecznego.
		* \param[in] mocGwiazdy - moc gwiazdy znajduj¹cej siê u uk³adzie.
		* \return Temperatura planety w kelwinach.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		STyp::SPG::Temperatura generujTemperaturePlanety(const STyp::Dystans& odlegloscOdCentrum, const STyp::Moc& mocGwiazdy) const;
	};
}
