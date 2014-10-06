#pragma once
#include "Info.h"
#include "Wymagania.h"

namespace SpEx{
	class Obiekt;
	/**
	* \brief Klasa opisowa obiektu.
	*
	* Klasa zawieraj¹ca elementy opisowe obiektu gry.
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
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] typ - Typ obiektu przechowywanego przez instancjê.
		* \param[in] typAtrybutu - Typ atrybutu obiektu jaki bêdzie reprezentowany przez dan¹ instancjê.
		* \param[in] wezel - Wêze³ XML, opisuj¹cy obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		explicit ObiektInfo(const STyp::Identyfikator& typ, PodstawoweParametry::TypAtrybutu typAtrybutu, XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu.
		*
		*  Metoda tworzy egzemplarz obiektu o podanej iloœci i dla podanej planety.
		* \param[in] parametry - Iloœæ tworzonych obiektów.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Metoda zwraca wskaŸnika na obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		virtual Obiekt* tworzEgzemplarz(const PodstawoweParametry& parametry) const = 0;

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~ObiektInfo() = default;

		/**
		* \brief Metoda pobieraj¹ca typ atrybutu.
		*
		* Metoda pobiera typ atrybutu jakiego u¿ywa dany obiekt.
		* \return Typ atrybutu.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		PodstawoweParametry::TypAtrybutu pobierzTypAtrybutu()const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	protected:
		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] atrybut - Atrybut tworzonego obiektu.
		* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		virtual bool tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy &atrybut) const = 0;

		/**
		* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
		*
		*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
		* \param[in] planeta - Referencja do obiektu planety
		* \param[in] element - Wêze³ z opisem tworzonego obiektu.
		* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		virtual bool tworz(Planeta& planeta, const XmlBO::ElementWezla& element) const = 0;

		PodstawoweParametry::TypAtrybutu typAtrybutu_; /// Typ atrybutu u¿ywanego w obiekcie.
	};
}
