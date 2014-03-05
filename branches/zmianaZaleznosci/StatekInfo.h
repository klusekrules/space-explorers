#pragma once
#include "ObiektInfo.h"
#include "LadowniaInfo.h"
#include "JednostkaLatajacaInfo.h"
#include "JednostkaAtakujacaInfo.h"
#include "HangarInfo.h"
#include "Statek.h"

namespace SpEx{
	/**
	* \brief Klasa opisowa dla statku
	*
	* Klasa gromadzi wszytkie niezb�dne klasy bazowe dla obiektu biznesowego typu statek.
	* \author Daniel Wojdak
	* \version 1
	* \date 24-07-2013
	*/
	class StatekInfo :
		public ObiektInfo,
		public JednostkaLatajacaInfo,
		public JednostkaAtakujacaInfo,
		public LadowniaInfo,
		public HangarInfo,
		virtual public SLog::LoggerInterface
	{
	public:

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		*/
		explicit StatekInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~StatekInfo() = default;

		/**
		* Metoda zwracaj�ca Identyfikator obiektu.
		* \return Identyfikator obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* Metoda zwracaj�ca informacje czy mo�na statek przechowa� w hangarze.
		* \return true je�eli mo�na dodac do hangaru, false w przeciwnym wypadku.
		*/
		bool czyMoznaDodacDoHangaru() const;

		/**
		* \brief Metoda tworz�ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu dla podanej planety.
		* \param[in] ilosc - ilo�� obiekt�w.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Metoda zwraca wska�nika na obiekt.
		*/
		Statek* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;

		STyp::Powierzchnia pobierzPowierzchnie(const PodstawoweParametry& podstawoweParametry)const;

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
		* \param[in] poziom - Poziom nowo tworzonego obiektu.
		* \return Metoda zwraca true je�eli tworzenie zako�czy si� sukcesem. Zwraca false w przeciwnym wypadku.
		*/
		bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const override;
		bool tworz(Planeta& planeta, const XmlBO::ElementWezla element) const override;

		STyp::Bool przechowywanyWHangarze_; /// Informacja czy statek mo�e by� przechowywwany w hangarze drugiego statku.

		STyp::Masa masa_;
		Zmiana zmianaMasy_;

		STyp::Powierzchnia powierzchnia_;
		Zmiana zmianaPowierzchni_;
	};
}
