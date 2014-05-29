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
	* \version 1
	* \date 22-07-2013
	*/
	class PodstawoweParametry :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:
		
		enum TypAtrybutu
		{
			POZIOM,
			ILOSC
		};

		typedef union AtrybutPodstawowy
		{
			STyp::Poziom::nazwa_typu poziom;
			STyp::Ilosc::nazwa_typu ilosc;
		};

		static AtrybutPodstawowy wpisPoziom(const STyp::Poziom&);
		static AtrybutPodstawowy wpisIlosc(const STyp::Ilosc&);
		static AtrybutPodstawowy wartoscJednostkowaAtrybutu(TypAtrybutu);
		static PodstawoweParametry wartoscJednostkowaParametru(TypAtrybutu);

		STyp::Poziom pobierzPoziom()const;
		STyp::Ilosc pobierzIlosc()const;

		/**
		* \brief Konstruktor
		*
		* Podstawowy konstruktor obiektu. Ustawia poziom i identyfikator planety, do kt�rej przypisany jest dany obiekt.
		* \param[in] atrybut - Atrybut obiektu.
		* \param[in] typ - typ atrybutu
		* \param[in] identyfikatorPlanety - Identyfikator planety zawieraj�cej obiekt.
		*/
		PodstawoweParametry(const AtrybutPodstawowy& atrybut, TypAtrybutu typ, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		PodstawoweParametry(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		PodstawoweParametry(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		PodstawoweParametry(PodstawoweParametry&&);

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca atrybut obiektu.
		*/
		const AtrybutPodstawowy& pobierzAtrybut() const;

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] atrybut - Nowa warto�� atrybutu obiektu.
		*/
		void ustawAtrybut(const AtrybutPodstawowy& atrybut);

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca identyfiaktor planety rodzica obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikatorPlanety() const;

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] identyfikatorPlanety - Nowa warto�� identyfikatora planety rodzica obiektu.
		*/
		void ustawIdentyfikatorPlanety(const STyp::Identyfikator& identyfikatorPlanety);

		/**
		* \brief Metoda zwi�kszaj�ca atrybut podstawowy.
		*
		* Metoda zwi�ksza atrybut podstawowy o podan� ilo��.
		*/
		void wzrostAtrybutu(const AtrybutPodstawowy& atrybut);

		/**
		* \brief Metoda pobieraj�ca typ atrybutu podstawowego.
		*
		* Metoda pobiera typ atrybutu podstawowego przechowywwanego przez klas�.
		* \return Typ atrybutu podstawowego.
		*/
		TypAtrybutu typAtrybutu()const;

		/**
		* \brief Metoda ustawia poziom i identyfikator planety rodzica.
		*
		* Metoda przypisuje warto�ci atrybut�w z obiektu podanego jako parametr do obiektu docelowego.
		* \param[in] podstawoweParametry - Obiekt zawieraj�cy atrybuty, kt�re maj� zosta� przypisane do obiektu docelowego.
		*/
		void ustawKontekst(const PodstawoweParametry& podstawoweParametry);

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
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
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

	protected:

		PodstawoweParametry(const PodstawoweParametry&) = default;

	private:
		TypAtrybutu typAtrybutu_; /// Typ atrybutu podstawowego.
		AtrybutPodstawowy atrybutPodstawowy_;/// Atrybut poziomu obiektu.
		STyp::Identyfikator identyfikatorPlanety_;/// Atrybut identyfikatora planety rodzica obiektu.
	};
}