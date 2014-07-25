#pragma once
#include "FabrykaSkryptow.h"
#include "Zmiana\ZmianaFabryka.h"

namespace SpEx{

	/**
	* \brief Klasa przechowuj¹ca obiekty fabryk.
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
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		~Fabrykator() = default;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych w wêŸle przez parametr.
		* \param[in] wezel - Wêze³ opisuj¹cy skrypt.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
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
		* \param[in] wezel - Wêze³ opisuj¹cy skrypt.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(const FabrykaSkryptow::Identyfikator& identyfikator, XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworz¹ca zmianê.
		*
		* Metoda tworzy obiekt zmiany na podstawie danych przekazanych przez parametry.
		* \param[in] wezel - Wêze³ opisuj¹cy zmianê.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \throw Metoda generuje wyj¹tek, je¿eli wêze³ nie zawiera odpowiedniego atrybutu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<SZmi::ZmianaInterfejs> TworzZmiane(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda pobieraj¹ca fabryke zmian.
		*
		* Meoda pobiera raferencje do fabryki zmian.
		* \return Referencja do fabryki zmian.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		SZmi::ZmianaFabryka& pobierzFabrykeZmian();

	private:

		FabrykaSkryptow fabrykaSkryptow_; /// Obiekt tworz¹cy instancje skryptów. Implementuje wzorzec fabryki.

		SZmi::ZmianaFabryka fabrykaZmian_; /// Instancja fabryki zmian.
	};
};
