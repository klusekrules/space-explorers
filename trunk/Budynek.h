#pragma once
#include "Obiekt.h"
#include "Wymagania.h"

namespace SpEx{
	/**
	* \brief Klasa Budynku
	*
	* Klasa implementuje metody zale�ne od dzia�ania obiektu. Dodaje metody pobieraj�ce zapotrzebowanie i produkcje obiektu.
	* \author Daniel Wojdak
	* \version 2
	* \date 15-07-2014
	*/
	class Budynek :
		public Obiekt,
		virtual public SLog::LoggerInterface
	{
		friend class BudynekInfo;
	public:
		typedef BudynekInfo Info;
		typedef std::shared_ptr<Budynek> SharedPtr;
		typedef std::shared_ptr<const Budynek> ConstSharedPtr;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] poziom - Poziom tworzonych obiekt�w.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] obiektInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Budynek(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const BudynekInfo& obiektInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
		* \param[in] obiektInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Budynek(const PodstawoweParametry& podstawoweParametry, const BudynekInfo& obiektInfo);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Budynek() = default;

		/**
		* \brief Metoda wyliczaj�ca zapotrzebowanie.
		*
		* Metoda wylicza zapotrzebowanie dla danego obiektu.
		* \return Lista element�w zapotrzebowania obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Wymagania::PrzetworzoneWarunki pobierzZapotrzebowanie()const;

		/**
		* \brief Metoda wyliczaj�ca produkcj�.
		*
		* Metoda wylicza produkcj� dla danego obiektu.
		* \return Lista element�w produkcji obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Wymagania::PrzetworzoneWarunki pobierzProdukcje()const;

		/**
		* \brief Metoda wyliczaj�ca powierzchni� budynku.
		*
		* Metoda wylicza powierzchni� dla danego obiektu.
		* \return Powierzchnia.
		* \author Daniel Wojdak
		* \version 1
		* \date 15-07-2014
		*/
		STyp::Powierzchnia pobierzPowierzchnie()const;

		/**
		* \brief Metoda tworz�ca kopi� obiektu.
		*
		* Metoda kopiuj�ca obiekt.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Wskazanie na kopie obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Budynek* kopia() const override;

		/**
		* \brief Metoda dziel�ca obiekt budynku.
		*
		* Metoda dziel�ca obiekt, nie jest wspierana dla budynku, zawsze zwraca nullptr.
		* \param[in] ilosc - Nieu�ywany.
		* \return  Metoda zawsze zwraca nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Budynek* podziel(const STyp::Ilosc& ilosc) override;

		/**
		* \brief Metoda ��cz�ca obiekty budynk�w.
		*
		* Metoda ��czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiekt - Nieu�ywany.
		* \return Zawsze zwraca warto�� false.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/		
		bool polacz(const Obiekt& obiekt) override;

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
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
		* \date 24-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis()const override;

	protected:
		const BudynekInfo& budynekInfo_; /// Referencja do obiektu opisowego.
	};
}
