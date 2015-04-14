#pragma once
#include "Logger\LoggerInterface.h"
#include "Serializacja.h"

namespace SpEx{
	/**
	* \brief Klasa zawieraj¹ca podstawowe parametry.
	*
	* Przechowywane przez tê klasê atrybuty, s¹ podstawowymi parametrami
	* potrzebnymi do wyliczenia wartoœci atrybutów obiektów pochodnych.
	* \author Daniel Wojdak
	* \version 2
	* \date 14-07-2014
	*/
	class PodstawoweParametry :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:

		/**
		* \brief Typy atrybutów u¿ywane w aplikacji.
		*
		* Wszystkie typy atrybutów, jakie s¹ u¿ywane w aplikacji.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		enum TypAtrybutu
		{
			POZIOM,
			ILOSC
		};

		/**
		* \brief Typ zmiennej przechowuj¹cej jeden z wybranych typów atrybutów.
		*
		* Typ zmiennej, w której mo¿emy przechowywaæ jeden z wybranych typów atrybutów.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		typedef union AtrybutPodstawowy
		{
			STyp::Poziom::nazwa_typu poziom;
			STyp::Ilosc::nazwa_typu ilosc;
		};

		/**
		* \brief Metoda tworz¹ca atrybut.
		*
		* Metoda tworz¹ca atrybut na podstawie poziomu przekazanego w parametrze.
		* \return Atrybut podstawowy.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		static AtrybutPodstawowy wpisPoziom(const STyp::Poziom& poziom);

		/**
		* \brief Metoda tworz¹ca atrybut.
		*
		* Metoda tworz¹ca atrybut na podstawie iloœci przekazanej w parametrze.
		* \return Atrybut podstawowy.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		static AtrybutPodstawowy wpisIlosc(const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda tworz¹ca atrybut.
		*
		* Metoda tworz¹ca atrybut o wartoœci jednostkowej na podstawie typu atrybutu przekazanego w parametrze.
		* \return Atrybut podstawowy.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		static AtrybutPodstawowy wartoscJednostkowaAtrybutu(TypAtrybutu typ);

		/**
		* \brief Metoda tworz¹ca obiekt podstawowych parametrów.
		*
		* Metoda tworz¹ca obiekt podstawowych parametrów o wartoœæi jednostkowej na podstawie typu atrybutu przekazanego w parametrze.
		* \return Podstawowe parametry obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		static PodstawoweParametry wartoscJednostkowaParametru(TypAtrybutu typ);

		/**
		* \brief Metoda pobieraj¹ca poziom.
		*
		* Metoda pobiera poziom elementu reprezentowanego przez obiekt klasy.
		* \return Poziom elementu. Je¿eli typem atrybutu jest iloœæ, wartoœæ zwrócona jest nie okreœlona.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		STyp::Poziom pobierzPoziom()const;

		/**
		* \brief Metoda pobieraj¹ca iloœæ.
		*
		* Metoda pobiera iloœæ elementów reprezentowanych przez obiekt klasy.
		* \return Iloœæ elementów. Je¿eli typem atrybutu jest poziom, wartoœæ zwrócona jest nie okreœlona.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		STyp::Ilosc pobierzIlosc()const;

		/**
		* \brief Konstruktor
		*
		* Podstawowy konstruktor obiektu. Ustawia atrybut podstawowy, typ atrybutu i identyfikator planety, do której przypisany jest dany obiekt.
		* \param[in] atrybut - Atrybut obiektu.
		* \param[in] typ - typ atrybutu
		* \param[in] identyfikatorPlanety - Identyfikator planety zawieraj¹cej obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PodstawoweParametry(const AtrybutPodstawowy& atrybut, TypAtrybutu typ, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		/**
		* \brief Konstruktor
		*
		* Podstawowy konstruktor obiektu. Ustawia iloœæ reprezentowanych elementów i identyfikator planety, do której przypisany jest dany obiekt.
		* \param[in] ilosc - iloœæ reprezentowanych elementów.
		* \param[in] identyfikatorPlanety - Identyfikator planety zawieraj¹cej obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PodstawoweParametry(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		/**
		* \brief Konstruktor
		*
		* Podstawowy konstruktor obiektu. Ustawia poziom reprezentowanego elementu i identyfikator planety, do której przypisany jest dany obiekt.
		* \param[in] poziom - poziom reprezentowanego elementu.
		* \param[in] identyfikatorPlanety - Identyfikator planety zawieraj¹cej obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PodstawoweParametry(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		/**
		* \brief Konstruktor przenosz¹cy.
		*
		*  Konstruktor przenosz¹cy.
		* \param[inout] obiekt - Obiekt Ÿród³owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PodstawoweParametry(PodstawoweParametry&& obiekt);

		/**
		* \brief Metoda pobieraj¹ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca atrybut obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		const AtrybutPodstawowy& pobierzAtrybut() const;

		/**
		* \brief Metoda ustawiaj¹ca atrybut.
		*
		* Metoda ustawiaj¹ca atrybut obiektu.
		* \param[in] atrybut - Nowa wartoœæ atrybutu obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void ustawAtrybut(const AtrybutPodstawowy& atrybut);

		/**
		* \brief Metoda pobieraj¹ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca identyfiaktor planety rodzica obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		const STyp::Identyfikator& pobierzIdentyfikatorPlanety() const;

		/**
		* \brief Metoda ustawiaj¹ca atrybut.
		*
		* Metoda ustawiaj¹ca atrybut obiektu.
		* \param[in] identyfikatorPlanety - Nowa wartoœæ identyfikatora planety rodzica obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void ustawIdentyfikatorPlanety(const STyp::Identyfikator& identyfikatorPlanety);

		/**
		* \brief Metoda zwiêkszaj¹ca atrybut podstawowy.
		*
		* Metoda zwiêksza atrybut podstawowy o podan¹ iloœæ.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void wzrostAtrybutu(const AtrybutPodstawowy& atrybut);

		/**
		* \brief Metoda pobieraj¹ca typ atrybutu podstawowego.
		*
		* Metoda pobiera typ atrybutu podstawowego przechowywwanego przez klasê.
		* \return Typ atrybutu podstawowego.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		TypAtrybutu typAtrybutu()const;

		/**
		* \brief Metoda ustawia poziom i identyfikator planety rodzica.
		*
		* Metoda przypisuje wartoœci atrybutów z obiektu podanego jako parametr do obiektu docelowego.
		* \param[in] podstawoweParametry - Obiekt zawieraj¹cy atrybuty, które maj¹ zostaæ przypisane do obiektu docelowego.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void ustawKontekst(const PodstawoweParametry& podstawoweParametry);

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
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
		* \date 22-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	protected:
		/**
		* \brief Domyœlny konstruktor kopiuj¹cy.
		*
		* Domyœlny konstruktor kopiuj¹cy.
		*/
		PodstawoweParametry(const PodstawoweParametry&) = default;

	private:
		TypAtrybutu typAtrybutu_; /// Typ atrybutu podstawowego.
		AtrybutPodstawowy atrybutPodstawowy_;/// Atrybut poziomu obiektu.
		STyp::Identyfikator identyfikatorPlanety_;/// Atrybut identyfikatora planety rodzica obiektu.
	};
}