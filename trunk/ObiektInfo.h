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
	* \version 2
	* \date 14-07-2014
	*/
	class ObiektInfo:
		public Wymagania,
		public Info,
		virtual public SLog::LoggerInterface
	{
		friend class Planeta;
	public:
		typedef std::shared_ptr<const ObiektInfo> ConstSharedPtr;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] typ - Typ obiektu przechowywanego przez instancj�.
		* \param[in] typAtrybutu - Typ atrybutu obiektu jaki b�dzie reprezentowany przez dan� instancj�.
		* \param[in] wezel - W�ze� XML, opisuj�cy obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		explicit ObiektInfo(const STyp::Identyfikator& typ, PodstawoweParametry::TypAtrybutu typAtrybutu, XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda tworz�ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu o podanej ilo�ci i dla podanej planety.
		* \param[in] parametry - Ilo�� tworzonych obiekt�w.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Metoda zwraca wska�nika na obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		virtual Obiekt* tworzEgzemplarz(const PodstawoweParametry& parametry) const = 0;

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~ObiektInfo() = default;

		/**
		* \brief Metoda pobieraj�ca typ atrybutu.
		*
		* Metoda pobiera typ atrybutu jakiego u�ywa dany obiekt.
		* \return Typ atrybutu.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
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
		* \param[in] atrybut - Atrybut tworzonego obiektu.
		* \return Metoda zwraca true je�eli tworzenie zako�czy si� sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		virtual bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy &atrybut) const = 0;

		/**
		* \brief Metoda tworz�ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U�ywana jest podczas wywo�ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] element - W�ze� z opisem tworzonego obiektu.
		* \return Metoda zwraca true je�eli tworzenie zako�czy si� sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		virtual bool tworz(Planeta& planeta, const XmlBO::ElementWezla& element) const = 0;

		PodstawoweParametry::TypAtrybutu typAtrybutu_; /// Typ atrybutu u�ywanego w obiekcie.
	};
}
