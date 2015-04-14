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
	* Klasa gromadzi wszytkie niezbêdne klasy bazowe dla obiektu biznesowego typu statek.
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
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		explicit StatekInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~StatekInfo() = default;

		/**
		* \brief Metoda pobieraj¹ca identyfikator obiektu.
		*
		* Metoda zwracaj¹ca Identyfikator obiektu.
		* \return Identyfikator obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* \brief Metoda sprawdzaj¹ca czy mo¿na dodaæ obiekt do hangaru.
		*
		* Metoda zwracaj¹ca informacje czy mo¿na statek przechowaæ w hangarze.
		* \return true je¿eli mo¿na przechowywaæ statek w hangarze, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool czyMoznaDodacDoHangaru() const;

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu dla podanej planety.
		* \param[in] parametry - parametry obiektu
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Metoda zwraca wskaŸnika na obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Statek* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;

		/**
		* \brief Metoda wyliczaj¹ca powierzchniê statku.
		*
		* Metoda wylicza powierzchniê dla danego obiektu.
		* \param[in] parametry - Parametry obiektu dla którego wyliczana jest powierzchnia.
		* \return Powierzchnia.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Powierzchnia pobierzPowierzchnie(const PodstawoweParametry& parametry)const;

		/**
		* \brief Metoda wyliczaj¹ca masê statku.
		*
		* Metoda wylicza masê dla danego obiektu.
		* \param[in] parametry - Parametry obiektu dla którego wyliczana jest masa.
		* \return Masa.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Masa pobierzMase(const PodstawoweParametry& parametry)const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	private:

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] atrybut - Atrybut tworzonego obiektu.
		* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy& atrybut) const override;

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] element - Wezel zawieraj¹cy dane obiektu.
		* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool tworz(Planeta& planeta, const XmlBO::ElementWezla& element) const override;

		STyp::Bool przechowywanyWHangarze_; /// Informacja czy statek mo¿e byæ przechowywwany w hangarze drugiego statku.

		STyp::Masa masa_; /// Podstawowa wartoœæ masy statku.
		Zmiana zmianaMasy_;  ///Zmiana masy statku.

		STyp::Powierzchnia powierzchnia_; /// Podstawowa wartoœæ powierzchni statku.
		Zmiana zmianaPowierzchni_; /// Zmiana powierzchni statku.

	};
}
