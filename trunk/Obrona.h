#pragma once
#include "JednostkaAtakujaca.h"
#include "Obiekt.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	/**
	* \brief Klasa obiektu Obrony
	*
	* Klasa gromadzi wszytkie niezbêdne klasy bazowe dla obiektu biznesowego typu obrona.
	* Nadpisuje metody potrzebne do poprawnego dzia³ania.
	* \author Daniel Wojdak
	* \version 1
	* \date 29-08-2013
	*/
	class Obrona :
		public JednostkaAtakujaca,
		public Obiekt,
		virtual public SLog::LoggerInterface,
		virtual public Serializacja,
		virtual public PodstawoweParametry
	{
		friend class ObronaInfo;
	public:

		/**
		* \brief Konstruktor.
		*
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
		* \param[in] obronaInfo - Referencja do obiektu opisuj¹cego.
		*/
		Obrona(const PodstawoweParametry& podstawoweParametry, const ObronaInfo& obronaInfo);

		/**
		* \brief Destruktor.
		*/
		virtual ~Obrona() = default;

		/**
		* \brief Metoda pobiera obiekt opisuj¹cy obronê.
		* \return Obiekt opisuj¹cy.
		*/
		const ObronaInfo& pobierzObronaInfo() const;

		/**
		* Metoda kopiuj¹ca obiekt.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Wskazanie na kopie obiektu.
		*/
		Obrona* kopia() const override;

		/**
		* Metoda ³¹czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiekt - Obiekt do po³¹czenia.
		* \warning Metoda nie zwalnia pamiêci przekazanego obiektu.
		* \return Kiedy obiekty zostan¹ po³¹czone, zwracana wartoœæ to true, w przeciwnym wypadku zwrócona wartoœæ to false.
		* \remark Metoda jest tranzakcyjna.
		*/
		bool polacz(const Obiekt& obiekt) override;

		/**
		* Metoda dziel¹ca klasê wzdlêdem iloœci podanej przez argument.
		* Zwrócony obiekt ma iloœæ równ¹ podan¹ przez parametr.
		* Obiekt bazowy ma iloœæ zmniejszon¹ o podan¹ przez parametr wartoœæ.
		* \param[in] ilosc - Iloœæ obiektów wzglêdem, którego jest podzielony obiekt.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Wskazanie na podzielony obiekt. Je¿eli nie mo¿na by³o podzieliæ obiektu, zostaje zwrócony nullptr.
		* \remark Metoda jest tranzakcyjna.
		*/
		Obrona* podziel(const STyp::Ilosc& ilosc) override;


		bool czyMoznaPolaczyc(const Obiekt& obiektBase) const;


		bool czyMoznaPodzielic(const STyp::Ilosc& ilosc) const;

		/**
		* Metoda atak s³u¿y do wyliczania obra¿eñ zadawanych przez obiekt.
		* \return Obra¿enia zadane przez obiekt.
		*/
		STyp::Obrazenia pobierzAtak() const override;

		/**
		* Metoda obliczaj¹ca obra¿enia mo¿liwe do przyjêcia przez pancerz.
		* \return Obra¿enia, które mo¿e przyj¹æ pancerz.
		*/
		STyp::Obrazenia pobierzPancerz() const override;

		/**
		* Metoda obliczaj¹ca obra¿enia mo¿liwe do przyjêcia przez oslone.
		* \return Obra¿enia, które mo¿e przyj¹æ os³ona.
		*/
		STyp::Obrazenia pobierzOslone() const override;

		STyp::Powierzchnia pobierzPowierzchnie(const PodstawoweParametry& podstawoweParametry)const;

		STyp::Powierzchnia pobierzPowierzchnie()const;

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
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
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis()const override;

	protected:

		const ObronaInfo& obronaInfo_; /// Referencja do obiektu opisuj¹cego.
	};
}