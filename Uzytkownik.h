#pragma once
#include "Logger\LoggerInterface.h"
#include "Planeta.h"

namespace SpEx{
	/**
	* \brief Klasa reprezentuj�ca u�ytkownika.
	*
	* Klasa u�ytkownika przechowuje planety oraz wszystkie potrzebne dane
	* \author Daniel Wojdak
	* \version 1
	* \date 26-07-2013
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
		* \param[in] gra - instancja gry dla u�ytkownika..
		*/
		Uzytkownik(Gra& gra);

		/**
		* \brief Destruktor.
		*/
		virtual ~Uzytkownik() = default;

		/**
		* \brief Metoda zwracaj�ca planet� nale��c� do u�ytkownika.
		*
		* Metoda pobiera planete nale��c� do u�ytkownika. Nie usuwa jej z listy jego planet.
		* \param[in] identyfikator - Numer identyfikuj�cy planet�.
		* \return Referencja do planety u�ytkownika.
		*/
		Planeta& pobierzPlanete(const STyp::Identyfikator& identyfikator) const;

		/**
		* \brief Metoda zwracaj�ca planet� nale��c� do u�ytkownika.
		*
		* Metoda pobiera planete nale��c� do u�ytkownika. Nie usuwa jej z listy jego planet.
		* \return Referencja do planety u�ytkownika.
		*/
		Planeta& pobierzPlanete();

		/**
		* \brief Metoda pobieraj�ca nazw� u�ytkownika.
		*
		* Metoda pobiera nazw� u�ytkownika.
		*\return Nazwa u�ytkownika reprezentowanego przez obiekt.
		*/
		STyp::Tekst pobierzNazweUzytkownika()const;

		/**
		* \brief Metoda ustawiaj�ca nazw� u�ytkownika.
		*
		* Metoda ustawia nazw� u�ytkownika.
		*\param[in] nazwa - Nowa nazwa u�ytkownika reprezentowanego przez obiekt.
		*/
		void ustawNazweUzytkownika(const STyp::Tekst& nazwa);

		/**
		* \brief Metoda dodaje palanet� do listy planet u�ytkownika.
		*
		*  Metoda ustawia w�a�ciciela planety na aktualnego u�ytkownika.
		* \param[in] planeta - Sprytny wska�nika na obiekt planety.
		* \return true je�eli uda si� doda� planet�, false je�eli operacja si� nie powiedzie.
		*/
		bool dodajPlanete(std::shared_ptr<Planeta> planeta);

		/**
		* \brief Metoda usuwaj�ca planet� z listy.
		*
		* Metoda usuwa planet� o podanym identyfikatorze z listy planet.
		* \param[in] identyfikator - Numer identyfikuj�cy planet�.
		* \return true je�eli planeta zostanie usuni�ta, false je�eli nie znaleziono planety.
		*/
		bool usunPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
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
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

		bool ustawPlaneteAktywna(const STyp::Identyfikator& id);
	private:
		STyp::Tekst nazwaUzytkownika_; /// Nazwa u�ytkownika. Cz�on nazwy pliku z danymi.
		Planety planety_; /// Lista planet u�ytkownika.
		Gra& instancjaGry; /// Instancja gry do kt�rej nale�y u�ytkowni.
		STyp::Identyfikator aktywnaPlaneta_;
	};
}
