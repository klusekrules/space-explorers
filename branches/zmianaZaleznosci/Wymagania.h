#pragma once
#include <vector>
#include <memory>
#include "PodstawoweParametry.h"
#include "Kryterium.h"
#include "SzablonKryterium.h"

namespace SpEx{
	/**
	* \brief Klasa zarz¹dzaj¹ca wymaganiami.
	*
	* Klasa gromadzi i zarz¹dza wymaganiami obiektu.
	* \author Daniel Wojdak
	* \version 1
	* \date 23-07-2013
	*/
	class Wymagania :
		virtual public SLog::LoggerInterface
	{
	public:
		typedef Kryterium TypWarunku;
		typedef SzablonKryterium< TypWarunku > Warunek;
		typedef std::vector< Warunek::TypObiektu > PrzetworzoneWarunki;
		typedef std::vector< Warunek > ListaWarunkow;

		/**
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		*/
		explicit Wymagania(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~Wymagania() = default;

		/**
		* \brief Metoda wyliczaj¹ca czas trwania budowy obiektu.
		*
		* Metoda wylicza czas jaki jest potrzebny, aby wybudowaæ obiekty o podanej iloœci, na planecie przekazanej przez parametry.
		* \param[in] ilosc - Iloœæ obiektów dla których jest wyliczany czas.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia czasu.
		* \return Czas jaki zosta³ wyliczony.
		*/
		virtual STyp::Czas pobierzCzasBudowy(const PodstawoweParametry& parametry)const;

		/**
		* \brief Metoda wyliczaj¹ca wymagania budowy obiektu.
		*
		* Metoda wylicza potrzebne wymagania, aby wybudowaæ obiekty, na planecie przekazanej przez parametry.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymagañ.
		* \return Lista wymagañ jaka zosta³a wyliczona.
		*/
		PrzetworzoneWarunki pobierzWarunki(const PodstawoweParametry& parametry) const;
		
		/**
		* \brief Metoda sprawdzaj¹ca czy obiekt spe³nia wymagania i koszty budowy.
		*
		* Metoda wylicza potrzebne wymagania i koszty, a nastêpnie sprawdza czy planeta spe³nia wymagania i zawiera potrzebne zasoby.
		* \param[in] ilosc - Iloœæ obiektów, które maj¹ spe³niæ wymagania.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymagañ i kosztów.
		* \return true je¿eli mo¿na wybudowaæ obiekty, false w przeciwnym wypadku.
		*/
		bool czySpelniaWymagania(const PodstawoweParametry& parametry)const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;
	private:
		ListaWarunkow warunki_; /// Lista warunków.
		std::shared_ptr <SZmi::ZmianaInterfejs> zmianaCzasuBudowy_; /// Zmiana czasu budowy.

		Kryterium::AtrybutKryterium wylicz(const Warunek&, const PodstawoweParametry&)const;
	};
}
