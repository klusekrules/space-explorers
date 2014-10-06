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
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		explicit SurowceInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destrutkor.
		*/
		virtual ~SurowceInfo() = default;

		/**
		* \brief Metoda informuj¹ca czy obiekt jest typu przyrostowego.
		*
		* Metoda sprawdzaj¹ca czy dany surowiec jest typu przyrostowego.
		* \return true je¿eli surowiec jest typu przyrostowego, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool czyTypPrzyrostowy()const;

		/**
		* \brief Metoda wyliczaj¹ca czas budowy.
		*
		* Metoda wylicza czas na podstawie iloœci surowca i zmiany.
		* \param[in] parametryPodstawowe - Podstawowe parametry potrzebne do wyliczenia czasu.
		* \return Czas budowy dla podanej iloœci u¿ytych surowców.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Czas pobierzCzasBudowy(const PodstawoweParametry& parametryPodstawowe)const override;

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu dla podanej planety.
		* \param[in] parametry - parametry obiektu
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Metoda zwraca wskaŸnika na obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce* tworzEgzemplarz(const PodstawoweParametry& parametry) const override;

		/**
		* \brief Metoda wyliczaj¹ca objêtoœæ surowca.
		*
		* Metoda wylicza objêtoœæ dla danego obiektu.
		* \param[in] parametry - Parametry obiektu dla którego wyliczana jest masa.
		* \return Objêtoœæ.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Objetosc pobierzObjetosc(const PodstawoweParametry& parametry)const;

		/**
		* \brief Metoda wyliczaj¹ca masê surowca.
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
		* \date 25-07-2013
		*/
		bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy &atrybut) const override;

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] element - Wezel zawieraj¹cy dane obiektu.
		* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool tworz(Planeta& planeta, const XmlBO::ElementWezla& element) const override;

		STyp::Bool przyrostowy_; /// Informacja czy podany tym jest przyrostowy

		Zmiana zmianaCzasu_; /// WskaŸnik do zmiany wyliczaj¹cej czas budowy.

		STyp::Objetosc objetosc_; /// Podstawowa wartoœæ objêtoœci surowca.
		Zmiana zmianaObjetosci_; /// Zmiana objêtoœci surowca.

		STyp::Masa masa_; /// Podstawowa wartoœæ masy surowca.
		Zmiana zmianaMasy_; /// Zmiana masy surowca.
	};
}
