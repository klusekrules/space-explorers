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
		* \brief Konstruktor.
		* \param[in] obiektInfo - Referencja do obiektu opisujacego.
		* \param[in] jednostkaLatajacaInfo - Referencja do obiektu opisujacego.
		* \param[in] jednostkaAtakujacaInfo - Referencja do obiektu opisujacego.
		* \param[in] ladowniaInfo - Referencja do obiektu opisujacego.
		* \param[in] hangarInfo - Referencja do obiektu opisuj¹cego.
		*/
		StatekInfo(const ObiektInfo& obiektInfo, const JednostkaLatajacaInfo& jednostkaLatajacaInfo, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo, const LadowniaInfo& ladowniaInfo, const HangarInfo& hangarInfo) throw();

		/**
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		*/
		explicit StatekInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~StatekInfo() = default;

		/**
		* Metoda zwracaj¹ca Identyfikator obiektu.
		* \return Identyfikator obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* Metoda zwracaj¹ca informacje czy mo¿na statek przechowaæ w hangarze.
		* \return true je¿eli mo¿na dodac do hangaru, false w przeciwnym wypadku.
		*/
		bool czyMoznaDodacDoHangaru() const;

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu dla podanej planety.
		* \param[in] ilosc - iloœæ obiektów.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Metoda zwraca wskaŸnika na obiekt.
		*/
		Statek* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;

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
		* \param[in] gra - Referencja do obiektu gry.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] ilosc - Iloœæ tworzonych obiektów.
		* \param[in] poziom - Poziom nowo tworzonego obiektu.
		* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
		*/
		bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const override;

		STyp::Bool przechowywanyWHangarze_; /// Informacja czy statek mo¿e byæ przechowywwany w hangarze drugiego statku.
	};
}
