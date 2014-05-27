#pragma once
#include <vector>
#include <memory>
#include "PodstawoweParametry.h"
#include "Kryterium.h"
#include "SzablonKryterium.h"
#include "NonCopyable.h"
#include "NonMoveable.h"

namespace SpEx{
	/**
	* \brief Klasa zarz�dzaj�ca wymaganiami.
	*
	* Klasa gromadzi i zarz�dza wymaganiami obiektu.
	* \author Daniel Wojdak
	* \version 1
	* \date 23-07-2013
	*/
	class Wymagania :
		virtual public SLog::LoggerInterface,
		public se::NonCopyable,
		public se::NonMoveable
	{
	public:
		//--- Definicje typ�w lokalnych ---
		typedef Kryterium TypWarunku;
		typedef SzablonKryterium< TypWarunku > Warunek;
		typedef std::vector< Warunek::TypObiektu > PrzetworzoneWarunki;
		typedef std::vector< Warunek > ListaWarunkow;
		typedef std::shared_ptr<SZmi::ZmianaInterfejs> Zmiana;

		//--- Metody domy�lne ---
		virtual ~Wymagania() = default;

		//--- Metody usuni�te ---

		//--- Metody statyczne ---

		static Kryterium::AtrybutKryterium wylicz(const Warunek&, const PodstawoweParametry&);

		//--- Konstruktory ---

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		*/
		explicit Wymagania(XmlBO::ElementWezla wezel);

		//--- Destruktor ---

		//--- Operatory ---

		//--- Metody wirtualne ---

		//--- Metody przeci��one ---

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

		//--- Metody typu Get/Set ---

		//--- Pozosta�e metody ---

		/**
		* \brief Metoda wyliczaj�ca czas trwania budowy obiektu.
		*
		* Metoda wylicza czas jaki jest potrzebny, aby wybudowa� obiekty o podanej ilo�ci, na planecie przekazanej przez parametry.
		* \param[in] ilosc - Ilo�� obiekt�w dla kt�rych jest wyliczany czas.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia czasu.
		* \return Czas jaki zosta� wyliczony.
		*/
		virtual STyp::Czas pobierzCzasBudowy(const PodstawoweParametry& parametry)const;

		/**
		* \brief Metoda wyliczaj�ca wymagania budowy obiektu.
		*
		* Metoda wylicza potrzebne wymagania, aby wybudowa� obiekty, na planecie przekazanej przez parametry.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymaga�.
		* \return Lista wymaga� jaka zosta�a wyliczona.
		*/
		PrzetworzoneWarunki pobierzWarunki(const PodstawoweParametry& parametry) const;
		
		/**
		* \brief Metoda sprawdzaj�ca czy obiekt spe�nia wymagania i koszty budowy.
		*
		* Metoda wylicza potrzebne wymagania i koszty, a nast�pnie sprawdza czy planeta spe�nia wymagania i zawiera potrzebne zasoby.
		* \param[in] ilosc - Ilo�� obiekt�w, kt�re maj� spe�ni� wymagania.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymaga� i koszt�w.
		* \return true je�eli mo�na wybudowa� obiekty, false w przeciwnym wypadku.
		*/
		bool czySpelniaWymagania(const PodstawoweParametry& parametry)const;

	private:

		//--- Atrybuty ---
		ListaWarunkow warunki_; /// Lista warunk�w.
		Zmiana zmianaCzasuBudowy_; /// Zmiana czasu budowy.
		
	};
}
