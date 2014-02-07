#pragma once
#include "ObiektInfo.h"
#include "JednostkaAtakujacaInfo.h"
#include "Obrona.h"

namespace SpEx{
	/**
	* \brief Klasa opisowa dla obrony
	*
	* Klasa gromadzi wszytkie niezbêdne klasy bazowe dla obiektu biznesowego typu obrona.
	* \author Daniel Wojdak
	* \version 1
	* \date 29-08-2013
	*/
	class ObronaInfo :
		public ObiektInfo,
		public JednostkaAtakujacaInfo,
		virtual public SLog::LoggerInterface
	{
	public:
		/**
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		*/
		explicit ObronaInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~ObronaInfo() = default;
		
		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu dla podanej planety.
		* \param[in] ilosc - iloœæ obiektów.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] poziom - Poziom tworzonego obiektu.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Metoda zwraca wskaŸnika na obiekt.
		*/
		Obrona* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;
		
		STyp::Powierzchnia pobierzPowierzchnie(const PodstawoweParametry& podstawoweParametry)const;
		
		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	private:
		STyp::Powierzchnia powierzchnia_;
		Zmiana zmianaPowierzchni_;

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
		* \param[in] gra - Referencja do obiektu gry.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] ilosc - Iloœæ tworzonych obiektów.
		* \param[in] poziom - Poziom tworzonego obiektu.
		* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
		*/
		bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const override;
	};

}