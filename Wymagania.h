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
	* \version 2
	* \date 14-07-2014
	*/
	class Wymagania :
		virtual public SLog::LoggerInterface,
		public se::NonCopyable,
		public se::NonMoveable
	{
	public:
		typedef Kryterium TypWarunku; /// Typ warunku
		typedef SzablonKryterium< TypWarunku > Warunek; /// Warunek
		typedef std::vector< Warunek::TypObiektu > PrzetworzoneWarunki; /// Przetworzony warunek
		typedef std::vector< Warunek > ListaWarunkow;  /// Lista warunk�w
		typedef std::shared_ptr<SZmi::ZmianaInterfejs> Zmiana; /// Zmiana warunku

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Wymagania() = default;

		/**
		* \brief Metoda wyliczaj�ca warto�� warunku w zale�no�ci od parametr�w.
		*
		* Metoda wylicza warto�� przekazanego warunku uwzgl�dniaj�c warto�� podstawowych parametr�w.
		* \param[in] warunek - Wyliczany warunek.
		* \param[in] parametry - Parametry uwzgl�dniane przy wyliczaniu.
		* \return Obliczona warto�c warunku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		static Kryterium::AtrybutKryterium wylicz(const Warunek& warunek, const PodstawoweParametry& parametry);
		
		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		explicit Wymagania(XmlBO::ElementWezla wezel);

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		std::string napis() const override;

		/**
		* \brief Metoda wyliczaj�ca czas trwania budowy obiektu.
		*
		* Metoda wylicza czas jaki jest potrzebny, aby wybudowa� obiekty o podanej ilo�ci, na planecie przekazanej przez parametry.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia czasu.
		* \return Czas jaki zosta� wyliczony.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		virtual STyp::Czas pobierzCzasBudowy(const PodstawoweParametry& parametry)const;

		/**
		* \brief Metoda wyliczaj�ca wymagania budowy obiektu.
		*
		* Metoda wylicza potrzebne wymagania, aby wybudowa� obiekty, na planecie przekazanej przez parametry.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymaga�.
		* \return Lista wymaga� jaka zosta�a wyliczona.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PrzetworzoneWarunki pobierzWarunki(const PodstawoweParametry& parametry) const;
		
		/**
		* \brief Metoda sprawdzaj�ca czy obiekt spe�nia wymagania i koszty budowy.
		*
		* Metoda wylicza potrzebne wymagania i koszty, a nast�pnie sprawdza czy planeta spe�nia wymagania i zawiera potrzebne zasoby.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymaga� i koszt�w.
		* \param[in] warunek - warunek uwzgl�dnienia kryterium.
		* \return true je�eli mo�na wybudowa� obiekty, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool czySpelniaWymagania(const PodstawoweParametry& parametry, std::function<bool(const Kryterium&)> warunek = nullptr )const;

	private:
		ListaWarunkow warunki_; /// Lista warunk�w.
		Zmiana zmianaCzasuBudowy_; /// Zmiana czasu budowy.
		
	};
}
