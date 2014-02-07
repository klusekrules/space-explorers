#pragma once
#include "ObiektInfo.h"
#include "JednostkaAtakujacaInfo.h"
#include "Obrona.h"

namespace SpEx{
	/**
	* \brief Klasa opisowa dla obrony
	*
	* Klasa gromadzi wszytkie niezb�dne klasy bazowe dla obiektu biznesowego typu obrona.
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
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		*/
		explicit ObronaInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~ObronaInfo() = default;
		
		/**
		* \brief Metoda tworz�ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu dla podanej planety.
		* \param[in] ilosc - ilo�� obiekt�w.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] poziom - Poziom tworzonego obiektu.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Metoda zwraca wska�nika na obiekt.
		*/
		Obrona* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;
		
		STyp::Powierzchnia pobierzPowierzchnie(const PodstawoweParametry& podstawoweParametry)const;
		
		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

	private:
		STyp::Powierzchnia powierzchnia_;
		Zmiana zmianaPowierzchni_;

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
	};

}