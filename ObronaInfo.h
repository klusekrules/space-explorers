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
	* \version 2
	* \date 16-07-2014
	*/
	class ObronaInfo :
		public ObiektInfo,
		public JednostkaAtakujacaInfo,
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
		* \date 29-08-2013
		*/
		explicit ObronaInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~ObronaInfo() = default;
		
		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu dla podanej planety.
		* \param[in] parametry - parametry obiektu
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Metoda zwraca wskaŸnika na obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
		*/
		Obrona* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;
		
		/**
		* \brief Metoda wyliczaj¹ca powierzchniê budynku.
		*
		* Metoda wylicza powierzchniê budynku na podstawie przekazanych parametrów.
		* \param[in] parametry - Parametry obiektu dla którego wyliczana jest powierzchnia.
		* \return Wyliczona powierzchnia.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Powierzchnia pobierzPowierzchnie(const PodstawoweParametry& podstawoweParametry)const;
		
		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	private:
		STyp::Powierzchnia powierzchnia_; /// Podstawowa wartoœc powierzchni obrony.
		Zmiana zmianaPowierzchni_; /// Zmiana powierzchni obrony.

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] atrybut - Atrybut tworzonego obiektu.
		* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
		*/
		bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const override;

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] element - Wezel zawieraj¹cy dane obiektu.
		* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 29-08-2013
		*/
		bool tworz(Planeta& planeta, const XmlBO::ElementWezla element) const override;
	};

}