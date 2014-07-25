#pragma once
#include "FabrykaSkryptow.h"
#include "Zmiana\ZmianaFabryka.h"

namespace SpEx{

	/**
	* \brief Klasa przechowuj�ca obiekty fabryk.
	*
	* Klasa przechowuje obiekty fabryk.
	* \author Daniel Wojdak
	* \version 1
	* \date 25-07-2014
	*/
	class Fabrykator
	{
	public:

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		Fabrykator();

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		~Fabrykator() = default;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych w w�le przez parametr.
		* \param[in] wezel - W�ze� opisuj�cy skrypt.
		* \return Zwracany jest wska�nik do skryptu, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych przez parametry.
		* \param[in] identyfikator - Identyfikator typu skryptu.
		* \param[in] wezel - W�ze� opisuj�cy skrypt.
		* \return Zwracany jest wska�nik do skryptu, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(const FabrykaSkryptow::Identyfikator& identyfikator, XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworz�ca zmian�.
		*
		* Metoda tworzy obiekt zmiany na podstawie danych przekazanych przez parametry.
		* \param[in] wezel - W�ze� opisuj�cy zmian�.
		* \return Zwracany jest wska�nik do skryptu, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \throw Metoda generuje wyj�tek, je�eli w�ze� nie zawiera odpowiedniego atrybutu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<SZmi::ZmianaInterfejs> TworzZmiane(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda pobieraj�ca fabryke zmian.
		*
		* Meoda pobiera raferencje do fabryki zmian.
		* \return Referencja do fabryki zmian.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		SZmi::ZmianaFabryka& pobierzFabrykeZmian();

	private:

		FabrykaSkryptow fabrykaSkryptow_; /// Obiekt tworz�cy instancje skrypt�w. Implementuje wzorzec fabryki.

		SZmi::ZmianaFabryka fabrykaZmian_; /// Instancja fabryki zmian.
	};
};
