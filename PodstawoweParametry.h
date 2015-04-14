#pragma once
#include "Logger\LoggerInterface.h"
#include "Serializacja.h"

namespace SpEx{
	/**
	* \brief Klasa zawieraj�ca podstawowe parametry.
	*
	* Przechowywane przez t� klas� atrybuty, s� podstawowymi parametrami
	* potrzebnymi do wyliczenia warto�ci atrybut�w obiekt�w pochodnych.
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
		* \brief Typy atrybut�w u�ywane w aplikacji.
		*
		* Wszystkie typy atrybut�w, jakie s� u�ywane w aplikacji.
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
		* \brief Typ zmiennej przechowuj�cej jeden z wybranych typ�w atrybut�w.
		*
		* Typ zmiennej, w kt�rej mo�emy przechowywa� jeden z wybranych typ�w atrybut�w.
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
		* \brief Metoda tworz�ca atrybut.
		*
		* Metoda tworz�ca atrybut na podstawie poziomu przekazanego w parametrze.
		* \return Atrybut podstawowy.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		static AtrybutPodstawowy wpisPoziom(const STyp::Poziom& poziom);

		/**
		* \brief Metoda tworz�ca atrybut.
		*
		* Metoda tworz�ca atrybut na podstawie ilo�ci przekazanej w parametrze.
		* \return Atrybut podstawowy.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		static AtrybutPodstawowy wpisIlosc(const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda tworz�ca atrybut.
		*
		* Metoda tworz�ca atrybut o warto�ci jednostkowej na podstawie typu atrybutu przekazanego w parametrze.
		* \return Atrybut podstawowy.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		static AtrybutPodstawowy wartoscJednostkowaAtrybutu(TypAtrybutu typ);

		/**
		* \brief Metoda tworz�ca obiekt podstawowych parametr�w.
		*
		* Metoda tworz�ca obiekt podstawowych parametr�w o warto��i jednostkowej na podstawie typu atrybutu przekazanego w parametrze.
		* \return Podstawowe parametry obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		static PodstawoweParametry wartoscJednostkowaParametru(TypAtrybutu typ);

		/**
		* \brief Metoda pobieraj�ca poziom.
		*
		* Metoda pobiera poziom elementu reprezentowanego przez obiekt klasy.
		* \return Poziom elementu. Je�eli typem atrybutu jest ilo��, warto�� zwr�cona jest nie okre�lona.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		STyp::Poziom pobierzPoziom()const;

		/**
		* \brief Metoda pobieraj�ca ilo��.
		*
		* Metoda pobiera ilo�� element�w reprezentowanych przez obiekt klasy.
		* \return Ilo�� element�w. Je�eli typem atrybutu jest poziom, warto�� zwr�cona jest nie okre�lona.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		STyp::Ilosc pobierzIlosc()const;

		/**
		* \brief Konstruktor
		*
		* Podstawowy konstruktor obiektu. Ustawia atrybut podstawowy, typ atrybutu i identyfikator planety, do kt�rej przypisany jest dany obiekt.
		* \param[in] atrybut - Atrybut obiektu.
		* \param[in] typ - typ atrybutu
		* \param[in] identyfikatorPlanety - Identyfikator planety zawieraj�cej obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PodstawoweParametry(const AtrybutPodstawowy& atrybut, TypAtrybutu typ, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		/**
		* \brief Konstruktor
		*
		* Podstawowy konstruktor obiektu. Ustawia ilo�� reprezentowanych element�w i identyfikator planety, do kt�rej przypisany jest dany obiekt.
		* \param[in] ilosc - ilo�� reprezentowanych element�w.
		* \param[in] identyfikatorPlanety - Identyfikator planety zawieraj�cej obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PodstawoweParametry(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		/**
		* \brief Konstruktor
		*
		* Podstawowy konstruktor obiektu. Ustawia poziom reprezentowanego elementu i identyfikator planety, do kt�rej przypisany jest dany obiekt.
		* \param[in] poziom - poziom reprezentowanego elementu.
		* \param[in] identyfikatorPlanety - Identyfikator planety zawieraj�cej obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PodstawoweParametry(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		/**
		* \brief Konstruktor przenosz�cy.
		*
		*  Konstruktor przenosz�cy.
		* \param[inout] obiekt - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PodstawoweParametry(PodstawoweParametry&& obiekt);

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca atrybut obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		const AtrybutPodstawowy& pobierzAtrybut() const;

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] atrybut - Nowa warto�� atrybutu obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void ustawAtrybut(const AtrybutPodstawowy& atrybut);

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca identyfiaktor planety rodzica obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		const STyp::Identyfikator& pobierzIdentyfikatorPlanety() const;

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] identyfikatorPlanety - Nowa warto�� identyfikatora planety rodzica obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void ustawIdentyfikatorPlanety(const STyp::Identyfikator& identyfikatorPlanety);

		/**
		* \brief Metoda zwi�kszaj�ca atrybut podstawowy.
		*
		* Metoda zwi�ksza atrybut podstawowy o podan� ilo��.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void wzrostAtrybutu(const AtrybutPodstawowy& atrybut);

		/**
		* \brief Metoda pobieraj�ca typ atrybutu podstawowego.
		*
		* Metoda pobiera typ atrybutu podstawowego przechowywwanego przez klas�.
		* \return Typ atrybutu podstawowego.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		TypAtrybutu typAtrybutu()const;

		/**
		* \brief Metoda ustawia poziom i identyfikator planety rodzica.
		*
		* Metoda przypisuje warto�ci atrybut�w z obiektu podanego jako parametr do obiektu docelowego.
		* \param[in] podstawoweParametry - Obiekt zawieraj�cy atrybuty, kt�re maj� zosta� przypisane do obiektu docelowego.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void ustawKontekst(const PodstawoweParametry& podstawoweParametry);

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
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
		* \date 22-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

	protected:
		/**
		* \brief Domy�lny konstruktor kopiuj�cy.
		*
		* Domy�lny konstruktor kopiuj�cy.
		*/
		PodstawoweParametry(const PodstawoweParametry&) = default;

	private:
		TypAtrybutu typAtrybutu_; /// Typ atrybutu podstawowego.
		AtrybutPodstawowy atrybutPodstawowy_;/// Atrybut poziomu obiektu.
		STyp::Identyfikator identyfikatorPlanety_;/// Atrybut identyfikatora planety rodzica obiektu.
	};
}