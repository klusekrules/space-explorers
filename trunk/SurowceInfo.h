#pragma once
#include "ObiektInfo.h"
#include "Surowce.h"

namespace SpEx{

	/**
	* \brief Klasa opisowa surowca.
	*
	* Klasa opisowa surowca.
	* \author Daniel Wojdak
	* \version 1
	* \date 25-07-2013
	*/
	class SurowceInfo :
		public ObiektInfo,
		virtual public SLog::LoggerInterface
	{
	public:

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		*/
		explicit SurowceInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~SurowceInfo() = default;

		/**
		* \brief Metoda informuj�ca czy obiekt jest typu przyrostowego.
		*
		* \return true je�eli surowiec jest typu przyrostowego, false w przeciwnym wypadku.
		*/
		bool czyTypPrzyrostowy()const;

		/**
		* \brief Metoda wyliczaj�ca czas budowy.
		*
		* Metoda wylicza czas na podstawie ilo�ci surowca i zmiany.
		* \param[in] ilosc - Ilo�� surowc�w na bazie kt�rych b�dzie wyliczany czas.
		* \param[in] parametryPodstawowe - Podstawowe parametry potrzebne do wyliczenia czasu.
		* \return Czas budowy dla podanej ilo�ci u�ytych surowc�w.
		*/
		STyp::Czas pobierzCzasBudowy(const PodstawoweParametry& parametryPodstawowe)const override;

		/**
		* \brief Metoda tworz�ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu dla podanej planety.
		* \param[in] ilosc - nieu�ywana
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Metoda zwraca wska�nika na obiekt.
		*/
		Surowce* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;

		STyp::Objetosc pobierzObjetosc(const PodstawoweParametry& podstawoweParametry)const;

		STyp::Masa pobierzMase(const PodstawoweParametry& podstawoweParametry)const;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;
	private:

		/**
		* \brief Metoda tworz�ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U�ywana jest podczas wywo�ywania metody wybuduj w klasie Planeta.
		* \param[in] gra - Referencja do obiektu gry.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] ilosc - Ilo�� tworzonych obiekt�w.
		* \param[in] poziom - Poziom tworzonego obiektu.
		* \return Metoda zwraca true je�eli tworzenie zako�czy si� sukcesem. Zwraca false w przeciwnym wypadku.
		*/
		bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const override;
		bool tworz(Planeta& planeta, const XmlBO::ElementWezla element) const override;

		STyp::Bool przyrostowy_; /// Informacja czy podany tym jest przyrostowy

		Zmiana zmianaCzasu_; /// Wska�nik do zmiany wyliczaj�cej czas budowy.

		STyp::Objetosc objetosc_;
		Zmiana zmianaObjetosci_;

		STyp::Masa masa_;
		Zmiana zmianaMasy_;
	};
}
