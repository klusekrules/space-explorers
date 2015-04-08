#include "GeneratorUkladow.h"
#include "Kontroler\Gra.h"
#include "Utils\Utils.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\StackThrow.h"

namespace SpEx{

	const STyp::Identyfikator GeneratorUkladow::LICZNIK_PLANET_ID(0x1);
	const STyp::Identyfikator GeneratorUkladow::LICZNIK_UKLADOW_ID(0x2);
	const STyp::Identyfikator GeneratorUkladow::LICZNIK_GALAKTYK_ID(0x3);

	const STyp::SPG::Dystans GeneratorUkladow::SREDNICA_GWIAZDY_MIN = 0.5;
	const STyp::SPG::Dystans GeneratorUkladow::SREDNICA_GWIAZDY_MAX = 70.0;

	const double GeneratorUkladow::SREDNICA_GWIAZDY_PARAM_ALFA = 3;
	const double GeneratorUkladow::SREDNICA_GWIAZDY_PARAM_BETA = 2.5;

	const STyp::SPG::Temperatura GeneratorUkladow::TEMPERATURA_GWIAZDY_MIN = 1700.0;
	const STyp::SPG::Temperatura GeneratorUkladow::TEMPERATURA_GWIAZDY_MAX = 50000.0;

	const double GeneratorUkladow::TEMPERATURA_GWIAZDY_PROCENT_SREDNICY = 0.78;
	const double GeneratorUkladow::TEMPERATURA_GWIAZDY_PROCENT_STALY = 0.1;
	const double GeneratorUkladow::TEMPERATURA_GWIAZDY_PROCENT_LOSOWY = 0.02;

	const int GeneratorUkladow::ILOSC_PLANET_MIN = 2;
	const int GeneratorUkladow::ILOSC_PLANET_MAX = 18;
	const double GeneratorUkladow::ILOSC_PLANET_PARAM = 0.45;

	const STyp::SPG::Dystans GeneratorUkladow::SREDNICA_PLANETY_MIN = 0.01;
	const STyp::SPG::Dystans GeneratorUkladow::SREDNICA_PLANETY_MAX = 0.16;
	const double GeneratorUkladow::SREDNICA_PLANETY_ODCHYLENIE = 0.7;
	const double GeneratorUkladow::SREDNICA_PLANETY_PRZESUNIECIE = 2.5;
	const double GeneratorUkladow::SREDNICA_PLANETY_ROZCIAGNIECIE = 386.0;

	const STyp::SPG::Dystans GeneratorUkladow::ODLEGLOSC_MIEDZYPLANETARNA_MIN = 50.0;
	const STyp::SPG::Dystans GeneratorUkladow::ODLEGLOSC_MIEDZYPLANETARNA_MAX = 300.0;

	const STyp::SPG::Fluktuacja GeneratorUkladow::POWIERZCHNIA_UZYTKOWA_MIN = 0.1f;
	const STyp::SPG::Fluktuacja GeneratorUkladow::POWIERZCHNIA_UZYTKOWA_MAX = 0.9f;

	const STyp::SPG::Temperatura GeneratorUkladow::TEMPERATURA_PLANETY_MAX = 500;

	const STyp::SPG::Fluktuacja GeneratorUkladow::POWIERZCHNIA_WODY_MAX = 0.9f;

#ifdef _DEBUG

	const int GeneratorUkladow::ILOSC_UKLADOW_MIN = 10;
	const int GeneratorUkladow::ILOSC_UKLADOW_MAX = 100;

#else

	const int GeneratorUkladow::ILOSC_UKLADOW_MIN = 100;
	const int GeneratorUkladow::ILOSC_UKLADOW_MAX = 1000;

#endif // DEBUG


	GeneratorUkladow::GeneratorUkladow()
		: licznikIdPlanet(LICZNIK_PLANET_ID, STyp::Ilosc(1)), licznikIdUkladow(LICZNIK_UKLADOW_ID, STyp::Ilosc(1)), licznikIdGalaktyk(LICZNIK_GALAKTYK_ID,STyp::Ilosc(1)),
		dystrybutorSrednicyGwiazdy(SREDNICA_GWIAZDY_PARAM_ALFA, SREDNICA_GWIAZDY_PARAM_BETA),
		dystrybutorIlosciPlanet(ILOSC_PLANET_MAX - ILOSC_PLANET_MIN, ILOSC_PLANET_PARAM),
		dystrybutorIlosciUkladow(ILOSC_UKLADOW_MIN, ILOSC_UKLADOW_MAX),
		dystrybucjaPowierzchniUzytkowej(POWIERZCHNIA_UZYTKOWA_MIN, POWIERZCHNIA_UZYTKOWA_MAX)
	{
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("TEMPERATURA_GWIAZDY_PROCENT_SREDNICY = ") + std::to_string(TEMPERATURA_GWIAZDY_PROCENT_SREDNICY));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("TEMPERATURA_GWIAZDY_PROCENT_STALY = ") + std::to_string(TEMPERATURA_GWIAZDY_PROCENT_STALY));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("TEMPERATURA_GWIAZDY_PROCENT_LOSOWY = ") + std::to_string(TEMPERATURA_GWIAZDY_PROCENT_LOSOWY));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("TEMPERATURA_GWIAZDY_MIN = ") + std::to_string(TEMPERATURA_GWIAZDY_MIN));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("TEMPERATURA_GWIAZDY_MAX = ") + std::to_string(TEMPERATURA_GWIAZDY_MAX));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("SREDNICA_GWIAZDY_MIN = ") + std::to_string(SREDNICA_GWIAZDY_MIN));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("SREDNICA_GWIAZDY_MAX = ") + std::to_string(SREDNICA_GWIAZDY_MAX));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("SREDNICA_GWIAZDY_PARAM_ALFA = ") + std::to_string(SREDNICA_GWIAZDY_PARAM_ALFA));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("SREDNICA_GWIAZDY_PARAM_BETA = ") + std::to_string(SREDNICA_GWIAZDY_PARAM_BETA));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("ILOSC_PLANET_MIN = ") + std::to_string(ILOSC_PLANET_MIN));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("ILOSC_PLANET_MAX = ") + std::to_string(ILOSC_PLANET_MAX));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("ILOSC_PLANET_PARAM = ") + std::to_string(ILOSC_PLANET_PARAM));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("SREDNICA_PLANETY_MIN = ") + std::to_string(SREDNICA_PLANETY_MIN));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("SREDNICA_PLANETY_MAX = ") + std::to_string(SREDNICA_PLANETY_MAX));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("SREDNICA_PLANETY_ODCHYLENIE = ") + std::to_string(SREDNICA_PLANETY_ODCHYLENIE));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("SREDNICA_PLANETY_PRZESUNIECIE = ") + std::to_string(SREDNICA_PLANETY_PRZESUNIECIE));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("SREDNICA_PLANETY_ROZCIAGNIECIE = ") + std::to_string(SREDNICA_PLANETY_ROZCIAGNIECIE));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("ODLEGLOSC_MIEDZYPLANETARNA_MIN = ") + std::to_string(ODLEGLOSC_MIEDZYPLANETARNA_MIN));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("ODLEGLOSC_MIEDZYPLANETARNA_MAX = ") + std::to_string(ODLEGLOSC_MIEDZYPLANETARNA_MAX));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("POWIERZCHNIA_UZYTKOWA_MIN = ") + std::to_string(POWIERZCHNIA_UZYTKOWA_MIN));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("POWIERZCHNIA_UZYTKOWA_MAX = ") + std::to_string(POWIERZCHNIA_UZYTKOWA_MAX));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("TEMPERATURA_PLANETY_MAX = ") + std::to_string(TEMPERATURA_PLANETY_MAX));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("POWIERZCHNIA_WODY_MAX = ") + std::to_string(POWIERZCHNIA_WODY_MAX));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("ILOSC_UKLADOW_MIN = ") + std::to_string(ILOSC_UKLADOW_MIN));
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, std::string("ILOSC_UKLADOW_MAX = ") + std::to_string(ILOSC_UKLADOW_MAX));
#endif
		if (TEMPERATURA_GWIAZDY_PROCENT_SREDNICY + TEMPERATURA_GWIAZDY_PROCENT_STALY + TEMPERATURA_GWIAZDY_PROCENT_LOSOWY >= 1.0 ||
			TEMPERATURA_GWIAZDY_PROCENT_SREDNICY + TEMPERATURA_GWIAZDY_PROCENT_STALY + TEMPERATURA_GWIAZDY_PROCENT_LOSOWY <= 0.0)
			throw std::exception("Invalid const params. TEMPERATURA_GWIAZDY_PROCENT_SREDNICY. TEMPERATURA_GWIAZDY_PROCENT_STALY. TEMPERATURA_GWIAZDY_PROCENT_LOSOWY.");

		if (POWIERZCHNIA_WODY_MAX > 1.0 || POWIERZCHNIA_WODY_MAX < 0.0)
			throw std::exception("Invalid const params. POWIERZCHNIA_WODY_MAX.");

		if (POWIERZCHNIA_UZYTKOWA_MIN > 1.0 || POWIERZCHNIA_UZYTKOWA_MIN < 0.0 ||
			POWIERZCHNIA_UZYTKOWA_MAX > 1.0 || POWIERZCHNIA_UZYTKOWA_MAX < 0.0 || 
			POWIERZCHNIA_UZYTKOWA_MAX < POWIERZCHNIA_UZYTKOWA_MIN)
			throw std::exception("Invalid const params. POWIERZCHNIA_UZYTKOWA_MIN. POWIERZCHNIA_UZYTKOWA_MAX.");

		if (ODLEGLOSC_MIEDZYPLANETARNA_MIN < 0 || ODLEGLOSC_MIEDZYPLANETARNA_MAX < 0 || ODLEGLOSC_MIEDZYPLANETARNA_MIN > ODLEGLOSC_MIEDZYPLANETARNA_MAX)
			throw std::exception("Invalid const params. ODLEGLOSC_MIEDZYPLANETARNA_MIN. ODLEGLOSC_MIEDZYPLANETARNA_MAX.");

		if (SREDNICA_PLANETY_MIN < 0 || SREDNICA_PLANETY_MAX < 0 || SREDNICA_PLANETY_MIN > SREDNICA_PLANETY_MAX)
			throw std::exception("Invalid const params. SREDNICA_PLANETY_MIN. SREDNICA_PLANETY_MAX.");

		if (TEMPERATURA_GWIAZDY_MIN > TEMPERATURA_GWIAZDY_MAX)
			throw std::exception("Invalid const params. TEMPERATURA_GWIAZDY_MIN. TEMPERATURA_GWIAZDY_MAX.");

		if (ILOSC_PLANET_MIN < 0 || ILOSC_PLANET_MAX < 0 || ILOSC_PLANET_MIN > ILOSC_PLANET_MAX)
			throw std::exception("Invalid const params. ILOSC_PLANET_MIN. ILOSC_PLANET_MAX.");

		if (SREDNICA_GWIAZDY_MIN < 0 || SREDNICA_GWIAZDY_MAX < 0 || SREDNICA_GWIAZDY_MIN > SREDNICA_GWIAZDY_MAX)
			throw std::exception("Invalid const params. SREDNICA_GWIAZDY_MIN. SREDNICA_GWIAZDY_MAX.");

		if (ILOSC_UKLADOW_MIN < 0 || ILOSC_UKLADOW_MAX < 0 || ILOSC_UKLADOW_MIN > ILOSC_UKLADOW_MAX)
			throw std::exception("Invalid const params. ILOSC_UKLADOW_MIN. ILOSC_UKLADOW_MAX.");

	}
	
	std::shared_ptr<Galaktyka> GeneratorUkladow::generujGalaktyke() const{
		auto galaktyka = std::make_shared<Galaktyka>(STyp::Identyfikator(static_cast<STyp::Identyfikator::nazwa_typu>(licznikIdGalaktyk()())));
		galaktyka->iloscUkladow_ = dystrybutorIlosciUkladow(generator);
		return galaktyka;
	}

	std::shared_ptr<UkladSloneczny> GeneratorUkladow::generujUklad(const STyp::Identyfikator& idGalatyki) const{
		auto uklad = std::make_shared<UkladSloneczny>(STyp::Identyfikator(static_cast<STyp::Identyfikator::nazwa_typu>(licznikIdUkladow()())), idGalatyki);

		uklad->ustawSredniceGwiazdy(generujSredniceGwiazdy());
		uklad->ustawSredniaTemperatureGwiazdy(generujTemperatureGwiazdy(uklad->pobierzSredniceGwiazdy()()));

		int iloscPlanet = ILOSC_PLANET_MIN + dystrybutorIlosciPlanet(generator);
		STyp::Moc mocGwiazdy = uklad->pobierzMocGwiazdy();
		STyp::Dystans odlegloscOdSrodkaUkladu = uklad->pobierzSredniceGwiazdy() / 2.0;
		std::uniform_real_distribution<STyp::SPG::Dystans> dystrybutorOdleglosciMiedzyplanetarnej(ODLEGLOSC_MIEDZYPLANETARNA_MIN, ODLEGLOSC_MIEDZYPLANETARNA_MAX);

		for (; iloscPlanet > 0; --iloscPlanet){
			odlegloscOdSrodkaUkladu += STyp::Dystans(dystrybutorOdleglosciMiedzyplanetarnej(generator));
			auto planeta = generujPlanete(odlegloscOdSrodkaUkladu, mocGwiazdy, uklad->pobierzIdentyfikator());
			if(!uklad->dodajPlanete(planeta))
				return nullptr;
		}
		return uklad;
	}

	STyp::SPG::Temperatura GeneratorUkladow::generujTemperatureGwiazdy(STyp::SPG::Dystans srednica) const{
		std::uniform_real_distribution<STyp::SPG::Temperatura> dystrybutorLosowejCzesciTemperatury(0, TEMPERATURA_GWIAZDY_PROCENT_LOSOWY);
		double procentLosowy = dystrybutorLosowejCzesciTemperatury(generator) - (TEMPERATURA_GWIAZDY_PROCENT_LOSOWY / 2.0);
		double procentSrednicy = (srednica / SREDNICA_GWIAZDY_MAX) * TEMPERATURA_GWIAZDY_PROCENT_SREDNICY;
		double procentZlozony = procentLosowy + procentSrednicy + TEMPERATURA_GWIAZDY_PROCENT_STALY;
		std::binomial_distribution<> dystrybutorTemperatury(static_cast<int>(TEMPERATURA_GWIAZDY_MAX - TEMPERATURA_GWIAZDY_MIN), procentZlozony);
		STyp::SPG::Temperatura temperatura(dystrybutorTemperatury(generator));
		return temperatura;
	}

	STyp::SPG::Dystans GeneratorUkladow::generujSredniceGwiazdy() const{
		STyp::SPG::Dystans srednica = SREDNICA_GWIAZDY_MIN + dystrybutorSrednicyGwiazdy(generator);
		return srednica > SREDNICA_GWIAZDY_MAX ? SREDNICA_GWIAZDY_MAX : srednica;
	}

	std::shared_ptr<Planeta> GeneratorUkladow::generujPlanete(const STyp::Dystans& odlegloscOdCentrum, const STyp::Moc& mocGwiazdy, const STyp::Identyfikator& idUkladu) const{
		auto planeta = std::make_shared<Planeta>(STyp::Identyfikator(static_cast<STyp::Identyfikator::nazwa_typu>(licznikIdPlanet()())), idUkladu);
		auto srednica = generujSrednicePlanety(odlegloscOdCentrum);
		auto temperatura = generujTemperaturePlanety(odlegloscOdCentrum, mocGwiazdy);

		STyp::SPG::Fluktuacja procentWody = Utils::FMIN();
		if (temperatura < 373.0){
			STyp::SPG::Fluktuacja temp = (static_cast<STyp::SPG::Fluktuacja>(temperatura)-273.0f) / 100.0f;
			std::uniform_real_distribution<STyp::SPG::Fluktuacja> dystrybutorPowierzchniWody(Utils::FMIN(), temp <= Utils::FMIN() || temp > POWIERZCHNIA_WODY_MAX ? POWIERZCHNIA_WODY_MAX : POWIERZCHNIA_WODY_MAX - temp);
			procentWody = dystrybutorPowierzchniWody(generator);
		}
		auto powierzchniaUzytkowa = dystrybucjaPowierzchniUzytkowej(generator);
		planeta->ustawNazwePlanety(STyp::Tekst("Kolonia"));
		planeta->ustawSrednice(STyp::Dystans(srednica));
		planeta->ustawTemperature(STyp::Temperatura(temperatura));
		planeta->ustawOdlegloscOdSrodkaUkladu(odlegloscOdCentrum);
		planeta->wyliczPowierzchnie(STyp::Fluktuacja(procentWody), STyp::Fluktuacja(powierzchniaUzytkowa));
		return planeta;
	}

	STyp::SPG::Dystans GeneratorUkladow::generujSrednicePlanety(const STyp::Dystans& odlegloscOdCentrum) const{
		double x = (odlegloscOdCentrum() / SREDNICA_PLANETY_ROZCIAGNIECIE) - SREDNICA_PLANETY_PRZESUNIECIE;
		STyp::SPG::Dystans d = SREDNICA_PLANETY_MIN + SREDNICA_PLANETY_MAX - SREDNICA_PLANETY_MIN * exp(-(x * x));
		STyp::SPG::Dystans d_min = d - d * SREDNICA_PLANETY_ODCHYLENIE;
		STyp::SPG::Dystans d_max = d + d * SREDNICA_PLANETY_ODCHYLENIE;
		std::uniform_real_distribution<STyp::SPG::Dystans> dystrybutor(d_min, d_max);
		return dystrybutor(generator);
	}

	STyp::SPG::Temperatura GeneratorUkladow::generujTemperaturePlanety(const STyp::Dystans& odlegloscOdCentrum, const STyp::Moc& mocGwiazdy) const{
		return TEMPERATURA_PLANETY_MAX + 200.0 * (1.0 / ((-4 * mocGwiazdy()) / (odlegloscOdCentrum() * odlegloscOdCentrum()) - 0.5));
	}

	bool GeneratorUkladow::zapisz(XmlBO::ElementWezla wezel) const{
		auto element = wezel->tworzElement(WEZEL_XML_GENERATOR_UKLADOW);
		return licznikIdPlanet.zapisz(element) && licznikIdUkladow.zapisz(element) && licznikIdGalaktyk.zapisz(element);
	}

	bool GeneratorUkladow::odczytaj(XmlBO::ElementWezla wezel){
			auto element = XmlBO::ZnajdzWezelJezeli<STACKTHROW>(wezel, WEZEL_XML_LICZNIK, ATRYBUT_XML_IDENTYFIKATOR, std::to_string(LICZNIK_PLANET_ID()));
			if (!licznikIdPlanet.odczytaj(element))
				return false;

			element = XmlBO::ZnajdzWezelJezeli<STACKTHROW>(wezel, WEZEL_XML_LICZNIK, ATRYBUT_XML_IDENTYFIKATOR, std::to_string(LICZNIK_UKLADOW_ID()));
			if (!licznikIdUkladow.odczytaj(element))
				return false;

			element = XmlBO::ZnajdzWezelJezeli<STACKTHROW>(wezel, WEZEL_XML_LICZNIK, ATRYBUT_XML_IDENTYFIKATOR, std::to_string(LICZNIK_GALAKTYK_ID()));
			if (!licznikIdGalaktyk.odczytaj(element))
				return false;
			return true;
	}

	std::string GeneratorUkladow::napis() const {
		SLog::Logger str(NAZWAKLASY(GeneratorUkladow));
		str.dodajPole(NAZWAPOLA(licznikIdPlanet), licznikIdPlanet);
		str.dodajPole(NAZWAPOLA(licznikIdUkladow), licznikIdUkladow);
		str.dodajPole(NAZWAPOLA(licznikIdGalaktyk), licznikIdGalaktyk);
		return str.napis();
	}
}
