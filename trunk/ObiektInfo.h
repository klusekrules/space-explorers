#pragma once
#include "Info.h"
#include "Wymagania.h"

namespace SpEx{
	class Obiekt;
	/**
	* \brief Klasa opisowa obiektu.
	*
	* Klasa zawieraj�ca elementy opisowe obiektu gry.
	* \author Daniel Wojdak
	* \version 1
	* \date 22-07-2013
	*/
	class ObiektInfo:
		public Wymagania,
		public Info,
		virtual public SLog::LoggerInterface
	{
		friend class Planeta;
	public:

		/**
		* \brief Konstruktor.
		*
		* \param[in] masa - Masa obiektu.
		* \param[in] objetosc - Objeto�� obiektu.
		* \param[in] powierzchnia - Powierzchnia obiektu.
		* \param[in] obiektBazowyInfo - Referencja do obiektu bazowego.
		*/
		//ObiektInfo(const Wymagania& wymagania, const Info& info);

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		*/
		explicit ObiektInfo(const STyp::Identyfikator& typ, PodstawoweParametry::TypAtrybutu typAtrybutu, XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda tworz�ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu o podanej ilo�ci i dla podanej planety.
		* \param[in] parametry - Ilo�� tworzonych obiekt�w.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Metoda zwraca wska�nika na obiekt.
		*/
		virtual Obiekt* tworzEgzemplarz(const PodstawoweParametry& parametry) const = 0;

		/**
		* \brief Destruktor.
		*/
		virtual ~ObiektInfo() = default;

		PodstawoweParametry::TypAtrybutu pobierzTypAtrybutu()const;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

	protected:
		/**
		* \brief Metoda tworz�ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U�ywana jest podczas wywo�ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] atrybut - Ilo�� tworzonych obiekt�w.
		* \return Metoda zwraca true je�eli tworzenie zako�czy si� sukcesem. Zwraca false w przeciwnym wypadku.
		*/
		virtual bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const = 0;

		virtual bool tworz(Planeta& planeta, const XmlBO::ElementWezla element) const = 0;

		PodstawoweParametry::TypAtrybutu typAtrybutu_;
	};
}
