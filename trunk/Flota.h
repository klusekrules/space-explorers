#pragma once
#include "Logger\LoggerInterface.h"
#include "Serializacja.h"
#include "Statek.h"

namespace SpEx {
	class Planeta;

	/**
	* \brief Klasa reprezentuj¹ca flote lec¹c¹ miedzy planetami.
	*
	* Klasa zarz¹dza flot¹. Pozwala na dodawanie Statków i £adunków.
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
		* \brief Rodzaje celów podró¿y floty.
		*
		* Wszystkie rodzaje celów podró¿y floty.
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

		typedef std::map< STyp::Identyfikator, std::shared_ptr<Statek> > ListaStatkow; /// Typ listy statków we flocie.

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] identyfikatorFloty - Identyfikator floty.
		* \param[in] planetaPoczatkowa - Identyfikator planety pocz¹tkowej.
		* \param[in] planetaDocelowa - Identyfikator planety docelowej.
		* \param[in] celPodrozy - cel podró¿y floty.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Flota(const STyp::Identyfikator& identyfikatorFloty, const STyp::Identyfikator& planetaPoczatkowa, const STyp::Identyfikator& planetaDocelowa, CelPodrozy celPodrozy);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Flota(void) = default;

		/**
		* \brief Metoda pobieraj¹ca identyfikator floty.
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
		* \param[in] statek - WskaŸnik do statku, który ma zostaæ dodany do floty.
		* \return true je¿eli uda siê dodaæ statek. false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool dodajStatek(std::shared_ptr<Statek> statek);

		/**
		* \brief Metoda dodaje obiekt do ³adowni floty.
		*
		* Metoda dodaje surowiec do ³adowni do floty.
		* \param[in] obiekt - WskaŸnik do surowca, który ma zostaæ dodany do ³adowni floty.
		* \return true je¿eli uda siê dodaæ surowiec. false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool dodajLadunek(std::shared_ptr<Surowce> obiekt);

		/**
		* \brief Metoda dodaje statek do hangaru floty.
		*
		* Metoda dodaje statek do hangaru do floty.
		* \param[in] obiekt - WskaŸnik do statku, który ma zostaæ dodany do hangaru floty.
		* \return true je¿eli uda siê dodaæ statek. false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool dodajLadunek(std::shared_ptr<Statek> obiekt);

		/**
		* \brief Metoda pobieraj¹ca dostêpne miejsce ³adowni.
		*
		* Metoda pobiera wolne miejsce znajduj¹ce siê na wszysktich statkach floty.
		* \return Objêtoœæ jaka jest dostêpna na statkach.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Objetosc pobierzDostepneMiejsceLadowni() const;

		/**
		* \brief Metoda pobieraj¹ca dostêpne miejsce hangaru.
		*
		* Metoda pobiera wolne miejsce znajduj¹ce siê na wszysktich statkach floty.
		* \return Objêtoœæ jaka jest dostêpna na statkach.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Objetosc pobierzDostepneMiejsceHangaru() const;

		/**
		* \brief Metoda ustawiaj¹ca punkt docelowy
		*
		* Metoda ustawia identyfikator planety docelowej do której zmierza flota.
		* \param[in] identyfikatorPlanety - Identyfikator planety docelowej.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		void ustawPlaneteDocelowa(const STyp::Identyfikator& identyfikatorPlanety);

		/**
		* \brief Metoda ustawiaj¹ca punkt pocz¹tkowy
		*
		* Metoda ustawia identyfikator planety pocz¹tkowej z której zmierza flota.
		* \param[in] identyfikatorPlanety - Identyfikator planety pocz¹tkowej.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		void ustawPlanetePoczatkowa(const STyp::Identyfikator& identyfikatorPlanety);

		/**
		* \brief Metoda pobiera identyfikaktor punktu docelowego.
		*
		* Metoda pobiera identyfikator planety docelowej do której zmierza flota.
		* \return Identyfikator planety docelowej.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Identyfikator pobierzPlaneteDocelowa() const;

		/**
		* \brief Metoda pobiera indentyfikator punktu pocz¹tkowego.
		*
		* Metoda pobiera identyfikator planety pocz¹tkowej z której zmierza flota.
		* \return Identyfikator planety pocz¹tkowej.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Identyfikator pobierzPlanetePoczatkowa() const;

		/**
		* \brief Metoda ustwia cel podró¿y.
		*
		* Metoda ustawia cel podró¿y floty.
		* \param[in] cel - Cel podró¿y floty
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		void ustawCelPodrozy(CelPodrozy cel);

		/**
		* \brief Metoda roz³adowuje zawartoœæ ³adowni na planecie.
		*
		* Metoda roz³adowuje zawartoœæ ³adowni na planecie. W zale¿noœci o celu mo¿e to byæ rózna planeta.
		* \return true je¿eli uda sie rozladowaæ ³adownie, false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool rozladujLadownieNaPlanecie();

		/**
		* \brief Metoda prowadza flotê do planety
		*
		* Metoda wprowadza flotê do planety. Nie usuwa wskaŸnika floty z planety do której flota jest przypisana.
		* \return true je¿eli uda sie wprowadziæ flotê, false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool rozladujFloteNaPlanecie();

		/**
		* \brief Metoda zawraca flotê
		*
		* Metoda ustawia misje na powrót.
		* \return true je¿eli zostanie ustawiona misja jako powrót. false je¿eli misja jest ju¿ ustawiona na powrót.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool zawrocFlote();

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
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
		* \date 25-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis()const override;
	private:
		ListaStatkow lista_; /// Lista statków nale¿¹cych do floty.
		STyp::Identyfikator idFloty_; /// Identyfikator planety poczatkowej.
		STyp::Identyfikator planetaPoczatkowa_; /// Identyfikator planety poczatkowej.
		STyp::Identyfikator planetaDocelowa_; /// Identyfikator planety docelowej.
		CelPodrozy celPodrozy_; /// Cel podró¿y floty.
	};
}
