#pragma once
#include "Budynek.h"
#include "ObiektInfo.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	/**
	* \brief Klasa opisowa budynku.
	*
	* Klasa zawieraj¹ca komplet atrybutów i metod opisuj¹cych budynek.
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
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		explicit BudynekInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~BudynekInfo() = default;

		/**
		* \brief Metoda wyliczaj¹ca zapotrzebowanie.
		*
		* Metoda wylicza na podstawie przekazanych parametrów zapotrzebowanie budynku na zasoby.
		* \param[in] parametry - Parametry obiektu wymagane do wykonania obliczeñ.
		* \return Lista elementów zapotrzebowania obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Wymagania::PrzetworzoneWarunki pobierzZapotrzebowanie(const PodstawoweParametry& parametry)const;

		/**
		* \brief Metoda wyliczaj¹ca produkcjê.
		*
		* Metoda wylicza na podstawie przekazanych parametrów produkcjê budynku.
		* \param[in] parametry - Parametry obiektu wymagane do wykonania obliczeñ.
		* \return Lista elementów produkcji obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Wymagania::PrzetworzoneWarunki pobierzProdukcje(const PodstawoweParametry& parametry)const;

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
		Budynek* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;
		
		/**
		* \brief Metoda wyliczaj¹ca powierzchniê budynku.
		*
		* Metoda wylicza powierzchniê budynku na podstawie przekazanych parametrów.
		* \param[in] parametry - Parametry obiektu dla którego wyliczana jest powierzchnia.
		* \return Wyliczona powierzchnia.
		* \author Daniel Wojdak
		* \version 1
		* \date 15-07-2014
		*/
		STyp::Powierzchnia pobierzPowierzchnie(const PodstawoweParametry& parametry)const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis()const override;

	protected:
		Wymagania::ListaWarunkow zapotrzebowanie_; /// Lista bazowych elementów zapotrzebowania.
		Wymagania::ListaWarunkow produkcja_; /// Lista bazowych elementów produkcji.

	private:
		STyp::Powierzchnia powierzchnia_; /// Podstawowa wartoœc powierzchni budynku.
		Zmiana zmianaPowierzchni_; /// Zmiana powierzchni budynku.

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
	};
}
