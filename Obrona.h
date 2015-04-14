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
	* \version 2
	* \date 16-07-2014
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
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
		* \param[in] obronaInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
		*/
		Obrona(const PodstawoweParametry& podstawoweParametry, const ObronaInfo& obronaInfo);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Obrona() = default;

		/**
		* \brief Metoda pobiera obiekt opisuj¹cy obronê.
		*
		* Metoda pobieraj¹ca obiekt opisowy.
		* \return Obiekt opisuj¹cy.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
		*/
		const ObronaInfo& pobierzObronaInfo() const;

		/**
		* \brief Metoda kopiuj¹ca obiekt.
		*
		* Metoda kopiuj¹ca obiekt.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Wskazanie na kopie obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
		*/
		Obrona* kopia() const override;

		/**
		* \brief Metoda ³¹cz¹ca obiekty obrony.
		*
		* Metoda ³¹czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiekt - Obiekt do po³¹czenia.
		* \warning Metoda nie zwalnia pamiêci przekazanego obiektu.
		* \return Kiedy obiekty zostan¹ po³¹czone, zwracana wartoœæ to true, w przeciwnym wypadku zwrócona wartoœæ to false.
		* \remark Metoda jest tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
		*/
		bool polacz(const Obiekt& obiekt) override;

		/**
		* \brief Metoda dziel¹ca obiekty obrony.
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
		* \date 29-08-2013
		*/
		Obrona* podziel(const STyp::Ilosc& ilosc) override;

		/**
		* \brief Metoda sprawdzaj¹ca mo¿liwoœæ po³¹czenia.
		*
		* Metoda sprawdza czy mo¿na po³¹czyæ obiekt przekazany przez parametr z obiektem reprezentowanym przez klasê.
		* \param[in] obiekt - Obiekt, dla którego jest sprawdzana mo¿liwoœæ po³¹czenia.
		* \return Zwracana jest wartoœæ true, je¿eli mo¿na po³aczyæ obiekty lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 16-07-2014
		*/
		bool czyMoznaPolaczyc(const Obiekt& obiekt) const;

		/**
		* \brief Metoda sprawdzaj¹ca mo¿liwoœæ podzielenia.
		*
		* Metoda sprawdza czy mo¿na podzielenia obiekt wzglêdem iloœci przekazanej przez parametr.
		* \param[in] ilosc - Iloœæ wzglêdem której ma zostaæ podzielony obiekt.
		* \return Zwracana jest wartoœæ true, je¿eli mo¿na podzieliæ obiekt lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 16-07-2014
		*/
		bool czyMoznaPodzielic(const STyp::Ilosc& ilosc) const;

		/**
		* \brief Metoda obliczaj¹ca atak obrony.
		*
		* Metoda atak s³u¿y do wyliczania obra¿eñ zadawanych przez obiekt.
		* \return Obra¿enia zadane przez obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
		*/
		STyp::Obrazenia pobierzAtak() const override;

		/**
		* \brief Metoda obliczaj¹ca pancerz obrony.
		*
		* Metoda obliczaj¹ca obra¿enia mo¿liwe do przyjêcia przez pancerz.
		* \return Obra¿enia, które mo¿e przyj¹æ pancerz.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
		*/
		STyp::Obrazenia pobierzPancerz() const override;

		/**
		* \brief Metoda obliczaj¹ca os³onê obrony.

		* Metoda obliczaj¹ca obra¿enia mo¿liwe do przyjêcia przez oslone.
		* \return Obra¿enia, które mo¿e przyj¹æ os³ona.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
		*/
		STyp::Obrazenia pobierzOslone() const override;

		/**
		* \brief Metoda wyliczaj¹ca powierzchniê budynku.
		*
		* Metoda wylicza powierzchniê dla danego obiektu.
		* \return Powierzchnia.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Powierzchnia pobierzPowierzchnie()const;

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
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
		* \date 29-08-2013
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