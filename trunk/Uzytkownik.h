#pragma once
#include "Logger\LoggerInterface.h"
#include "Planeta.h"

namespace SpEx{
	/**
	* \brief Klasa reprezentuj�ca u�ytkownika.
	*
	* Klasa u�ytkownika przechowuje planety oraz wszystkie potrzebne dane
	* \author Daniel Wojdak
	* \version 2
	* \date 14-07-2014
	*/
	class Uzytkownik :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:
		typedef std::map<STyp::Identyfikator, std::shared_ptr<Planeta> > Planety;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] gra - instancja gry dla u�ytkownika..
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		Uzytkownik(Gra& gra);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Uzytkownik() = default;

		/**
		* \brief Metoda zwracaj�ca planet� nale��c� do u�ytkownika.
		*
		* Metoda pobiera planete nale��c� do u�ytkownika. Nie usuwa jej z listy jego planet.
		* \param[in] identyfikator - Numer identyfikuj�cy planet�.
		* \return Referencja do planety u�ytkownika.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		Planeta& pobierzPlanete(const STyp::Identyfikator& identyfikator) const;

		/**
		* \brief Metoda zwracaj�ca planet� nale��c� do u�ytkownika.
		*
		* Metoda pobiera planete nale��c� do u�ytkownika. Nie usuwa jej z listy jego planet.
		* \return Referencja do planety u�ytkownika.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		Planeta& pobierzPlanete();

		/**
		* \brief Metoda pobieraj�ca nazw� u�ytkownika.
		*
		* Metoda pobiera nazw� u�ytkownika.
		*\return Nazwa u�ytkownika reprezentowanego przez obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		const STyp::Tekst& pobierzNazweUzytkownika()const;

		/**
		* \brief Metoda ustawiaj�ca nazw� u�ytkownika.
		*
		* Metoda ustawia nazw� u�ytkownika.
		*\param[in] nazwa - Nowa nazwa u�ytkownika reprezentowanego przez obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		void ustawNazweUzytkownika(const STyp::Tekst& nazwa);

		const STyp::Tekst& pobierzSkrotKlucza() const;

		/**
		* \brief Metoda dodaje palanet� do listy planet u�ytkownika.
		*
		*  Metoda ustawia w�a�ciciela planety na aktualnego u�ytkownika.
		* \param[in] planeta - Sprytny wska�nika na obiekt planety.
		* \return true je�eli uda si� doda� planet�, false je�eli operacja si� nie powiedzie.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		bool dodajPlanete(std::shared_ptr<Planeta> planeta);

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
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
		* \date 26-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda odpina planety od w�a�ciciela.
		*
		* Metoda odpina wszystkie planety od w�a�ciciela czyszcz�c ich zawarto��.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		bool odpinaniePlanet();

		/**
		* \brief Metoda odpina planet� od w�a�ciciela.
		*
		* Metoda odpina planet� o podanym w parametrze identyfikatorze od w�a�ciciela czyszcz�c jej zawarto��.
		* \param[in] id - Identyfikator planety.
		* \return Zwracana jest warto�� true, je�eli operacja zako�czy si� powowdzeniem. Zwracana jest warto�� false, je�eli planeta nie zostanie znaleziona.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		bool odpinaniePlanet(const STyp::Identyfikator& id);

		/**
		* \brief Metoda ustawia now� aktywn� planet�.
		*
		* Metoda ustawia now� aktywn� planet�.
		* \param[in] id - Identyfikator planety.
		* \return Zwracana jest warto�� true, je�eli operacja zako�czy si� powowdzeniem. Zwracana jest warto�� false, je�eli planeta nie zostanie znaleziona.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		bool ustawPlaneteAktywna(const STyp::Identyfikator& id);

	private:
		STyp::Tekst nazwaUzytkownika_; /// Nazwa u�ytkownika. Cz�on nazwy pliku z danymi.
		Planety planety_; /// Lista planet u�ytkownika.
		Gra& instancjaGry; /// Instancja gry do kt�rej nale�y u�ytkowni.
		STyp::Identyfikator aktywnaPlaneta_; /// Identyfikator aktywnej planety.
		STyp::Tekst skrotKlucza_;
	};
}
