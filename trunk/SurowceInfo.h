#pragma once
#include "ObiektInfo.h"
#include "Surowce.h"

namespace SpEx{

	/**
	* \brief Klasa opisowa surowca.
	*
	* Klasa opisowa surowca.
	* \author Daniel Wojdak
	* \version 2
	* \date 16-07-2014
	*/
	class SurowceInfo :
		public ObiektInfo,
		virtual public SLog::LoggerInterface
	{
	public:
		typedef std::shared_ptr<const SurowceInfo> ConstSharedPtr;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		explicit SurowceInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destrutkor.
		*/
		virtual ~SurowceInfo() = default;

		/**
		* \brief Metoda informuj�ca czy obiekt jest typu przyrostowego.
		*
		* Metoda sprawdzaj�ca czy dany surowiec jest typu przyrostowego.
		* \return true je�eli surowiec jest typu przyrostowego, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool czyTypPrzyrostowy()const;

		/**
		* \brief Metoda wyliczaj�ca czas budowy.
		*
		* Metoda wylicza czas na podstawie ilo�ci surowca i zmiany.
		* \param[in] parametryPodstawowe - Podstawowe parametry potrzebne do wyliczenia czasu.
		* \return Czas budowy dla podanej ilo�ci u�ytych surowc�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Czas pobierzCzasBudowy(const PodstawoweParametry& parametryPodstawowe)const override;

		/**
		* \brief Metoda tworz�ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu dla podanej planety.
		* \param[in] parametry - parametry obiektu
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Metoda zwraca wska�nika na obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;

		/**
		* \brief Metoda wyliczaj�ca obj�to�� surowca.
		*
		* Metoda wylicza obj�to�� dla danego obiektu.
		* \param[in] parametry - Parametry obiektu dla kt�rego wyliczana jest masa.
		* \return Obj�to��.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Objetosc pobierzObjetosc(const PodstawoweParametry& parametry)const;

		/**
		* \brief Metoda wyliczaj�ca mas� surowca.
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
		* \date 25-07-2013
		*/
		bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy &atrybut) const override;

		/**
		* \brief Metoda tworz�ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U�ywana jest podczas wywo�ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] element - Wezel zawieraj�cy dane obiektu.
		* \return Metoda zwraca true je�eli tworzenie zako�czy si� sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool tworz(Planeta& planeta, const XmlBO::ElementWezla& element) const override;

		STyp::Bool przyrostowy_; /// Informacja czy podany tym jest przyrostowy

		Zmiana zmianaCzasu_; /// Wska�nik do zmiany wyliczaj�cej czas budowy.

		STyp::Objetosc objetosc_; /// Podstawowa warto�� obj�to�ci surowca.
		Zmiana zmianaObjetosci_; /// Zmiana obj�to�ci surowca.

		STyp::Masa masa_; /// Podstawowa warto�� masy surowca.
		Zmiana zmianaMasy_; /// Zmiana masy surowca.
	};
}
