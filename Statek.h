#pragma once
#include "JednostkaAtakujaca.h"
#include "JednostkaLatajaca.h"
#include "Obiekt.h"
#include "Ladownia.h"
#include "Hangar.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	/**
	* \brief Klasa obiektu statku
	*
	* Klasa gromadzi wszytkie niezbêdne klasy bazowe dla obiektu biznesowego typu statek.
	* Nadpisuje metody potrzebne do poprawnego dzia³ania.
	* \author Daniel Wojdak
	* \version 2
	* \date 16-07-2014
	*/
	class Statek :
		public JednostkaAtakujaca,
		public JednostkaLatajaca,
		public Ladownia,
		public Hangar,
		public Obiekt,
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
		friend class StatekInfo;
	public:

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] ilosc - iloœæ tworzonych obiektów.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] statekInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Statek(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety, const StatekInfo& statekInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
		* \param[in] statekInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Statek(const PodstawoweParametry& podstawoweParametry, const StatekInfo& statekInfo);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Statek() = default;

		/**
		* \brief Metoda pobiera obiekt opisuj¹cy statek.
		*
		* Metoda pobieraj¹ca obiekt opisowy.
		* \return Obiekt opisuj¹cy.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		const StatekInfo& pobierzStatekInfo() const;

		/**
		* \brief Metoda wyliczaj¹ca zy¿ycie paliwa przez statek.
		*
		* Metoda wylicza zy¿ycie paliwa przez statek na okreœlonym dystansie i przy okreœlonej prêkoœci.
		* \param[in] dystans - Dystans, na którym ma poruszaæ siê statek.
		* \param[in] predkosc - Prêdkoœæ, któr¹ ma lecieæ statek.
		* \return Paliwo zu¿yte przez statek.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::ZuzyciePaliwa wyliczZuzyciePaliwa(const STyp::Dystans& dystans, const STyp::Predkosc& predkosc) const override;

		/**
		* \brief Metoda tworz¹ca kopie obiektu.
		*
		* Metoda kopiuj¹ca obiekt.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Wskazanie na kopie obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Statek* kopia() const override;

		/**
		* \brief Metoda dziel¹ca obiekt.
		*
		* Metoda dziel¹ca klasê wzdlêdem iloœci podanej przez argument.
		* Zwrócony obiekt ma iloœæ równ¹ podan¹ przez parametr.
		* Obiekt bazowy ma iloœæ zmniejszon¹ o podan¹ przez parametr wartoœæ.
		* \param[in] ilosc - Iloœæ obiektów wzglêdem, którego jest podzielony obiekt.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Wskazanie na podzielony obiekt. Je¿eli nie mo¿na by³o podzieliæ obiektu, zostaje zwrócony nullptr.
		* \remark Metoda jest tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Statek* podziel(const STyp::Ilosc& ilosc) override;

		/**
		* \brief Metoda ³¹cz¹ca obiekt.
		*
		* Metoda ³¹czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiekt - Obiekt do po³¹czenia.
		* \warning Metoda nie zwalnia pamiêci przekazanego obiektu.
		* \return Kiedy obiekty zostan¹ po³¹czone, zwracana wartoœæ to true, w przeciwnym wypadku zwrócona wartoœæ to false.
		* \remark Metoda jest tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool polacz(const Obiekt& obiekt) override;

		/**
		* \brief Metoda oblicza atak obiektu.
		*
		* Metoda atak s³u¿y do wyliczania obra¿eñ zadawanych przez obiekt.
		* \return Obra¿enia zadane przez obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Obrazenia pobierzAtak() const override;

		/**
		* \brief Metoda oblicza pancerz obiektu.
		*
		* Metoda obliczaj¹ca obra¿enia mo¿liwe do przyjêcia przez pancerz.
		* \return Obra¿enia, które mo¿e przyj¹æ pancerz.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Obrazenia pobierzPancerz() const override;

		/**
		* \brief Metoda oblicza os³onê obiektu.
		*
		* Metoda obliczaj¹ca obra¿enia mo¿liwe do przyjêcia przez oslone.
		* \return Obra¿enia, które mo¿e przyj¹æ os³ona.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Obrazenia pobierzOslone() const override;

		/**
		* \brief Metoda wylicza objêtoœæ maksymaln¹ ³adowni.
		*
		* Metoda oblicza maksymaln¹ objêtoœæ obiektów jakie mog¹ znaleœæ siê w ³adowni.
		* \return Objêtoœæ maksymalna ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Objetosc pobierzPojemnoscMaksymalnaLadowni() const override;

		/**
		* \brief Metoda wylicza objêtoœæ maksymaln¹ hangaru.
		*
		* Metoda oblicza maksymaln¹ objêtoœæ obiektów jakie mog¹ znaleœæ siê w hangarze.
		* \return Objêtoœæ maksymalna hangaru.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Powierzchnia pobierzPojemnoscMaksymalnaHangaru() const override;

		/**
		* \brief Metoda wyliczaj¹ca jednostkowe zu¿ycie paliwa.
		*
		* \return Paliwo zu¿yte przez statek.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::ZuzyciePaliwa pobierzJednostkoweZuzyciePaliwa()const override;

		/**
		* \brief Metoda wyliczaj¹ca masê silnika.
		*
		* Metoda oblicza masê samego silnika.
		* \return Masa silnika.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Masa pobierzMasaSilnika()const override;

		/**
		* \brief Metoda sprawdzaj¹ca czy mo¿na obiekt dodaæ do hangaru.
		*
		* Metoda zwracaj¹ca informacje czy mo¿na statek przechowaæ w hangarze.
		* \return true je¿eli mo¿na dodac do hangaru, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool czyMoznaDodacDoHangaru() const;

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

		/**
		* \brief Metoda wyliczaj¹ca powierzchniê jednostkow¹ statku.
		*
		* Metoda wylicza powierzchniê jednostkow¹ dla danego obiektu.
		* \return Powierzchnia.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Powierzchnia pobierzPowierzchnieJednostkowa()const;

		/**
		* \brief Metoda wyliczaj¹ca powierzchniê statku.
		*
		* Metoda wylicza powierzchniê dla danego obiektu.
		* \return Powierzchnia.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Powierzchnia pobierzPowierzchnie()const;

		/**
		* \brief Metoda wyliczaj¹ca masê statku.
		*
		* Metoda wylicza masê dla danego obiektu.
		* \return Masa.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Masa pobierzMase()const;

	protected:

		/**
		* \brief Metoda zwracaj¹ca ca³kowit¹ masê statku wraz z mas¹ ³adowni.
		*
		* Metoda obliczaj¹ca ca³kowit¹ masê jednostki wraz z obiektami jakie znajduj¹ siê w ³adowni i hangarze.
		* \return Ca³kowita masa statku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Masa calkowitaMasaJednostki() const override;

		const StatekInfo& statekinfo_; /// Referencja do obiektu opisuj¹cego.

	};
}
