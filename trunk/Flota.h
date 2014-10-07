#pragma once
#include "Logger\LoggerInterface.h"
#include "Serializacja.h"
#include "Statek.h"

namespace SpEx {
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
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:
		typedef std::shared_ptr<Flota> SharedPtr;
		typedef std::shared_ptr<const Flota> ConstSharedPtr;

		/**
		* \brief Rodzaje cel�w podr�y floty.
		*
		* Wszystkie rodzaje cel�w podr�y floty.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		enum CelPodrozy{
			Zwiad,
			Atak,
			Transport,
			Stacjonowanie,
			Szczatki,
			Ekspedycja,
			Powrot
		};

		typedef std::map< STyp::Identyfikator, std::shared_ptr<Statek> > ListaStatkow; /// Typ listy statk�w we flocie.

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] identyfikatorFloty - Identyfikator floty.
		* \param[in] planetaPoczatkowa - Identyfikator planety pocz�tkowej.
		* \param[in] planetaDocelowa - Identyfikator planety docelowej.
		* \param[in] celPodrozy - cel podr�y floty.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Flota(const STyp::Identyfikator& identyfikatorFloty, const STyp::Identyfikator& planetaPoczatkowa, const STyp::Identyfikator& planetaDocelowa, CelPodrozy celPodrozy);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Flota(void) = default;

		/**
		* \brief Metoda pobieraj�ca identyfikator floty.
		*
		* Metoda pobiera identyfikator floty.
		* \return Identyfikator floty.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		const STyp::Identyfikator& pobierzIdentyfikator()const;

		/**
		* \brief Metoda dodaje statek do floty.
		*
		* Metoda dodaje kolejny statek do floty.
		* \param[in] statek - Wska�nik do statku, kt�ry ma zosta� dodany do floty.
		* \return true je�eli uda si� doda� statek. false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool dodajStatek(std::shared_ptr<Statek> statek);

		/**
		* \brief Metoda dodaje obiekt do �adowni floty.
		*
		* Metoda dodaje surowiec do �adowni do floty.
		* \param[in] obiekt - Wska�nik do surowca, kt�ry ma zosta� dodany do �adowni floty.
		* \return true je�eli uda si� doda� surowiec. false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool dodajLadunek(std::shared_ptr<Surowce> obiekt);

		/**
		* \brief Metoda dodaje statek do hangaru floty.
		*
		* Metoda dodaje statek do hangaru do floty.
		* \param[in] obiekt - Wska�nik do statku, kt�ry ma zosta� dodany do hangaru floty.
		* \return true je�eli uda si� doda� statek. false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool dodajLadunek(std::shared_ptr<Statek> obiekt);

		/**
		* \brief Metoda pobieraj�ca dost�pne miejsce �adowni.
		*
		* Metoda pobiera wolne miejsce znajduj�ce si� na wszysktich statkach floty.
		* \return Obj�to�� jaka jest dost�pna na statkach.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Objetosc pobierzDostepneMiejsceLadowni() const;

		/**
		* \brief Metoda pobieraj�ca dost�pne miejsce hangaru.
		*
		* Metoda pobiera wolne miejsce znajduj�ce si� na wszysktich statkach floty.
		* \return Obj�to�� jaka jest dost�pna na statkach.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Objetosc pobierzDostepneMiejsceHangaru() const;

		/**
		* \brief Metoda ustawiaj�ca punkt docelowy
		*
		* Metoda ustawia identyfikator planety docelowej do kt�rej zmierza flota.
		* \param[in] identyfikatorPlanety - Identyfikator planety docelowej.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		void ustawPlaneteDocelowa(const STyp::Identyfikator& identyfikatorPlanety);

		/**
		* \brief Metoda ustawiaj�ca punkt pocz�tkowy
		*
		* Metoda ustawia identyfikator planety pocz�tkowej z kt�rej zmierza flota.
		* \param[in] identyfikatorPlanety - Identyfikator planety pocz�tkowej.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		void ustawPlanetePoczatkowa(const STyp::Identyfikator& identyfikatorPlanety);

		/**
		* \brief Metoda pobiera identyfikaktor punktu docelowego.
		*
		* Metoda pobiera identyfikator planety docelowej do kt�rej zmierza flota.
		* \return Identyfikator planety docelowej.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Identyfikator pobierzPlaneteDocelowa() const;

		/**
		* \brief Metoda pobiera indentyfikator punktu pocz�tkowego.
		*
		* Metoda pobiera identyfikator planety pocz�tkowej z kt�rej zmierza flota.
		* \return Identyfikator planety pocz�tkowej.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Identyfikator pobierzPlanetePoczatkowa() const;

		/**
		* \brief Metoda ustwia cel podr�y.
		*
		* Metoda ustawia cel podr�y floty.
		* \param[in] cel - Cel podr�y floty
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		void ustawCelPodrozy(CelPodrozy cel);

		/**
		* \brief Metoda roz�adowuje zawarto�� �adowni na planecie.
		*
		* Metoda roz�adowuje zawarto�� �adowni na planecie. W zale�no�ci o celu mo�e to by� r�zna planeta.
		* \return true je�eli uda sie rozladowa� �adownie, false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool rozladujLadownieNaPlanecie();

		/**
		* \brief Metoda prowadza flot� do planety
		*
		* Metoda wprowadza flot� do planety. Nie usuwa wska�nika floty z planety do kt�rej flota jest przypisana.
		* \return true je�eli uda sie wprowadzi� flot�, false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool rozladujFloteNaPlanecie();

		/**
		* \brief Metoda zawraca flot�
		*
		* Metoda ustawia misje na powr�t.
		* \return true je�eli zostanie ustawiona misja jako powr�t. false je�eli misja jest ju� ustawiona na powr�t.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool zawrocFlote();

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
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
		* \date 25-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis()const override;
	private:
		ListaStatkow lista_; /// Lista statk�w nale��cych do floty.
		STyp::Identyfikator idFloty_; /// Identyfikator planety poczatkowej.
		STyp::Identyfikator planetaPoczatkowa_; /// Identyfikator planety poczatkowej.
		STyp::Identyfikator planetaDocelowa_; /// Identyfikator planety docelowej.
		CelPodrozy celPodrozy_; /// Cel podr�y floty.
	};
}
