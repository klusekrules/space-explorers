#pragma once
#include "Budynek.h"
#include "ObiektInfo.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	/**
	* \brief Klasa opisowa budynku.
	*
	* Klasa zawieraj�ca komplet atrybut�w i metod opisuj�cych budynek.
	* \author Daniel Wojdak
	* \version 2
	* \date 15-07-2014
	*/
	class BudynekInfo :
		public ObiektInfo,
		virtual public SLog::LoggerInterface
	{
	public:
		typedef std::shared_ptr<const BudynekInfo> ConstSharedPtr;

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		explicit BudynekInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~BudynekInfo() = default;

		/**
		* \brief Metoda wyliczaj�ca zapotrzebowanie.
		*
		* Metoda wylicza na podstawie przekazanych parametr�w zapotrzebowanie budynku na zasoby.
		* \param[in] parametry - Parametry obiektu wymagane do wykonania oblicze�.
		* \return Lista element�w zapotrzebowania obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Wymagania::PrzetworzoneWarunki pobierzZapotrzebowanie(const PodstawoweParametry& parametry)const;

		/**
		* \brief Metoda wyliczaj�ca produkcj�.
		*
		* Metoda wylicza na podstawie przekazanych parametr�w produkcj� budynku.
		* \param[in] parametry - Parametry obiektu wymagane do wykonania oblicze�.
		* \return Lista element�w produkcji obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Wymagania::PrzetworzoneWarunki pobierzProdukcje(const PodstawoweParametry& parametry)const;

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
		Budynek* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;
		
		/**
		* \brief Metoda wyliczaj�ca powierzchni� budynku.
		*
		* Metoda wylicza powierzchni� budynku na podstawie przekazanych parametr�w.
		* \param[in] parametry - Parametry obiektu dla kt�rego wyliczana jest powierzchnia.
		* \return Wyliczona powierzchnia.
		* \author Daniel Wojdak
		* \version 1
		* \date 15-07-2014
		*/
		STyp::Powierzchnia pobierzPowierzchnie(const PodstawoweParametry& parametry)const;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis()const override;

	protected:
		Wymagania::ListaWarunkow zapotrzebowanie_; /// Lista bazowych element�w zapotrzebowania.
		Wymagania::ListaWarunkow produkcja_; /// Lista bazowych element�w produkcji.

	private:
		STyp::Powierzchnia powierzchnia_; /// Podstawowa warto�c powierzchni budynku.
		Zmiana zmianaPowierzchni_; /// Zmiana powierzchni budynku.

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
	};
}
