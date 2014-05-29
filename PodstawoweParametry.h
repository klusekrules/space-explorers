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
		* Podstawowy konstruktor obiektu. Ustawia poziom i identyfikator planety, do której przypisany jest dany obiekt.
		* \param[in] atrybut - Atrybut obiektu.
		* \param[in] typ - typ atrybutu
		* \param[in] identyfikatorPlanety - Identyfikator planety zawieraj¹cej obiekt.
		*/
		PodstawoweParametry(const AtrybutPodstawowy& atrybut, TypAtrybutu typ, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		PodstawoweParametry(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		PodstawoweParametry(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety = STyp::Identyfikator(0));

		PodstawoweParametry(PodstawoweParametry&&);

		/**
		* \brief Metoda pobieraj¹ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca atrybut obiektu.
		*/
		const AtrybutPodstawowy& pobierzAtrybut() const;

		/**
		* \brief Metoda ustawiaj¹ca atrybut.
		*
		* Metoda ustawiaj¹ca atrybut obiektu.
		* \param[in] atrybut - Nowa wartoœæ atrybutu obiektu.
		*/
		void ustawAtrybut(const AtrybutPodstawowy& atrybut);

		/**
		* \brief Metoda pobieraj¹ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca identyfiaktor planety rodzica obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikatorPlanety() const;

		/**
		* \brief Metoda ustawiaj¹ca atrybut.
		*
		* Metoda ustawiaj¹ca atrybut obiektu.
		* \param[in] identyfikatorPlanety - Nowa wartoœæ identyfikatora planety rodzica obiektu.
		*/
		void ustawIdentyfikatorPlanety(const STyp::Identyfikator& identyfikatorPlanety);

		/**
		* \brief Metoda zwiêkszaj¹ca atrybut podstawowy.
		*
		* Metoda zwiêksza atrybut podstawowy o podan¹ iloœæ.
		*/
		void wzrostAtrybutu(const AtrybutPodstawowy& atrybut);

		/**
		* \brief Metoda pobieraj¹ca typ atrybutu podstawowego.
		*
		* Metoda pobiera typ atrybutu podstawowego przechowywwanego przez klasê.
		* \return Typ atrybutu podstawowego.
		*/
		TypAtrybutu typAtrybutu()const;

		/**
		* \brief Metoda ustawia poziom i identyfikator planety rodzica.
		*
		* Metoda przypisuje wartoœci atrybutów z obiektu podanego jako parametr do obiektu docelowego.
		* \param[in] podstawoweParametry - Obiekt zawieraj¹cy atrybuty, które maj¹ zostaæ przypisane do obiektu docelowego.
		*/
		void ustawKontekst(const PodstawoweParametry& podstawoweParametry);

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
		std::string napis() const override;

	protected:

		PodstawoweParametry(const PodstawoweParametry&) = default;

	private:
		TypAtrybutu typAtrybutu_; /// Typ atrybutu podstawowego.
		AtrybutPodstawowy atrybutPodstawowy_;/// Atrybut poziomu obiektu.
		STyp::Identyfikator identyfikatorPlanety_;/// Atrybut identyfikatora planety rodzica obiektu.
	};
}