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
	* \brief Klasa zarz¹dzaj¹ca wymaganiami.
	*
	* Klasa gromadzi i zarz¹dza wymaganiami obiektu.
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
		typedef std::vector< Warunek > ListaWarunkow;  /// Lista warunków
		typedef std::shared_ptr<SZmi::ZmianaInterfejs> Zmiana; /// Zmiana warunku

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Wymagania() = default;

		/**
		* \brief Metoda wyliczaj¹ca wartoœæ warunku w zale¿noœci od parametrów.
		*
		* Metoda wylicza wartoœæ przekazanego warunku uwzglêdniaj¹c wartoœæ podstawowych parametrów.
		* \param[in] warunek - Wyliczany warunek.
		* \param[in] parametry - Parametry uwzglêdniane przy wyliczaniu.
		* \return Obliczona wartoœc warunku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		static Kryterium::AtrybutKryterium wylicz(const Warunek& warunek, const PodstawoweParametry& parametry);
		
		/**
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		explicit Wymagania(XmlBO::ElementWezla wezel);

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		std::string napis() const override;

		/**
		* \brief Metoda wyliczaj¹ca czas trwania budowy obiektu.
		*
		* Metoda wylicza czas jaki jest potrzebny, aby wybudowaæ obiekty o podanej iloœci, na planecie przekazanej przez parametry.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia czasu.
		* \return Czas jaki zosta³ wyliczony.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		virtual STyp::Czas pobierzCzasBudowy(const PodstawoweParametry& parametry)const;

		/**
		* \brief Metoda wyliczaj¹ca wymagania budowy obiektu.
		*
		* Metoda wylicza potrzebne wymagania, aby wybudowaæ obiekty, na planecie przekazanej przez parametry.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymagañ.
		* \return Lista wymagañ jaka zosta³a wyliczona.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PrzetworzoneWarunki pobierzWarunki(const PodstawoweParametry& parametry) const;
		
		/**
		* \brief Metoda sprawdzaj¹ca czy obiekt spe³nia wymagania i koszty budowy.
		*
		* Metoda wylicza potrzebne wymagania i koszty, a nastêpnie sprawdza czy planeta spe³nia wymagania i zawiera potrzebne zasoby.
		* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymagañ i kosztów.
		* \param[in] warunek - warunek uwzglêdnienia kryterium.
		* \return true je¿eli mo¿na wybudowaæ obiekty, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool czySpelniaWymagania(const PodstawoweParametry& parametry, std::function<bool(const Kryterium&)> warunek = nullptr )const;

	private:
		ListaWarunkow warunki_; /// Lista warunków.
		Zmiana zmianaCzasuBudowy_; /// Zmiana czasu budowy.
		
	};
}
