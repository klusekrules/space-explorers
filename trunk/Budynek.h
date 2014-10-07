#pragma once
#include "Obiekt.h"
#include "Wymagania.h"

namespace SpEx{
	/**
	* \brief Klasa Budynku
	*
	* Klasa implementuje metody zale¿ne od dzia³ania obiektu. Dodaje metody pobieraj¹ce zapotrzebowanie i produkcje obiektu.
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
		* \param[in] poziom - Poziom tworzonych obiektów.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] obiektInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Budynek(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const BudynekInfo& obiektInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
		* \param[in] obiektInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Budynek(const PodstawoweParametry& podstawoweParametry, const BudynekInfo& obiektInfo);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Budynek() = default;

		/**
		* \brief Metoda wyliczaj¹ca zapotrzebowanie.
		*
		* Metoda wylicza zapotrzebowanie dla danego obiektu.
		* \return Lista elementów zapotrzebowania obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Wymagania::PrzetworzoneWarunki pobierzZapotrzebowanie()const;

		/**
		* \brief Metoda wyliczaj¹ca produkcjê.
		*
		* Metoda wylicza produkcjê dla danego obiektu.
		* \return Lista elementów produkcji obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Wymagania::PrzetworzoneWarunki pobierzProdukcje()const;

		/**
		* \brief Metoda wyliczaj¹ca powierzchniê budynku.
		*
		* Metoda wylicza powierzchniê dla danego obiektu.
		* \return Powierzchnia.
		* \author Daniel Wojdak
		* \version 1
		* \date 15-07-2014
		*/
		STyp::Powierzchnia pobierzPowierzchnie()const;

		/**
		* \brief Metoda tworz¹ca kopiê obiektu.
		*
		* Metoda kopiuj¹ca obiekt.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Wskazanie na kopie obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Budynek* kopia() const override;

		/**
		* \brief Metoda dziel¹ca obiekt budynku.
		*
		* Metoda dziel¹ca obiekt, nie jest wspierana dla budynku, zawsze zwraca nullptr.
		* \param[in] ilosc - Nieu¿ywany.
		* \return  Metoda zawsze zwraca nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Budynek* podziel(const STyp::Ilosc& ilosc) override;

		/**
		* \brief Metoda ³¹cz¹ca obiekty budynków.
		*
		* Metoda ³¹czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiekt - Nieu¿ywany.
		* \return Zawsze zwraca wartoœæ false.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/		
		bool polacz(const Obiekt& obiekt) override;

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
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
		* \date 24-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis()const override;

	protected:
		const BudynekInfo& budynekInfo_; /// Referencja do obiektu opisowego.
	};
}
