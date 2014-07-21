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
	* \version 2
	* \date 16-07-2014
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
		* \brief Konstruktor.
		*
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		explicit StatekInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~StatekInfo() = default;

		/**
		* \brief Metoda pobieraj�ca identyfikator obiektu.
		*
		* Metoda zwracaj�ca Identyfikator obiektu.
		* \return Identyfikator obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* \brief Metoda sprawdzaj�ca czy mo�na doda� obiekt do hangaru.
		*
		* Metoda zwracaj�ca informacje czy mo�na statek przechowa� w hangarze.
		* \return true je�eli mo�na przechowywa� statek w hangarze, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool czyMoznaDodacDoHangaru() const;

		/**
		* \brief Metoda tworz�ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu dla podanej planety.
		* \param[in] parametry - parametry obiektu
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Metoda zwraca wska�nika na obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Statek* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;

		/**
		* \brief Metoda wyliczaj�ca powierzchni� statku.
		*
		* Metoda wylicza powierzchni� dla danego obiektu.
		* \param[in] parametry - Parametry obiektu dla kt�rego wyliczana jest powierzchnia.
		* \return Powierzchnia.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Powierzchnia pobierzPowierzchnie(const PodstawoweParametry& parametry)const;

		/**
		* \brief Metoda wyliczaj�ca mas� statku.
		*
		* Metoda wylicza mas� dla danego obiektu.
		* \param[in] parametry - Parametry obiektu dla kt�rego wyliczana jest masa.
		* \return Masa.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Masa pobierzMase(const PodstawoweParametry& parametry)const;

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
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] atrybut - Atrybut tworzonego obiektu.
		* \return Metoda zwraca true je�eli tworzenie zako�czy si� sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy& atrybut) const override;

		/**
		* \brief Metoda tworz�ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U�ywana jest podczas wywo�ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] element - Wezel zawieraj�cy dane obiektu.
		* \return Metoda zwraca true je�eli tworzenie zako�czy si� sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool tworz(Planeta& planeta, const XmlBO::ElementWezla& element) const override;

		STyp::Bool przechowywanyWHangarze_; /// Informacja czy statek mo�e by� przechowywwany w hangarze drugiego statku.

		STyp::Masa masa_; /// Podstawowa warto�� masy statku.
		Zmiana zmianaMasy_;  ///Zmiana masy statku.

		STyp::Powierzchnia powierzchnia_; /// Podstawowa warto�� powierzchni statku.
		Zmiana zmianaPowierzchni_; /// Zmiana powierzchni statku.

	};
}
