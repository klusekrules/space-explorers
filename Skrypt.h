#pragma once
#include <string>
#include "NonCopyable.h"

namespace SpEx{

	/**
	* \brief Klasa ujednolicaj�ca interfejs dla skryptu.
	*
	* Klasa zawieraj�ca podstawowy interfejs do wykonywania skrypt�w.
	* \author Daniel Wojdak
	* \version 1
	* \date 09-07-2014
	*/
	class Skrypt :
		public se::NonCopyable
	{
	public:
		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		Skrypt() = default;

		/**
		* \brief Metoda �aduj�ca skrypt.
		*
		* Metoda s�u��ca do ��dowania skryptu.
		* \param[in] lokalizacja - Napis lokalizuj�cy �r�d�o skryptu.
		* \return Zwracana jest warto�� true, je�eli uda si� za�adowa� skrypt lub false w przeciwnym wypadku.
		*/
		virtual bool zaladuj(const std::string& lokalizacja) = 0;

		/**
		* \brief Metoda wykonuj�ca skrypt.
		*
		* Metoda s�u��ca do wykonywania skryptu.
		* \param[in] metoda - Nazwa metody.
		* \return Zwracana jest warto�� true, je�eli uda si� wykona� skrypt lub false w przeciwnym wypadku.
		*/
		virtual bool wykonaj(const std::string& metoda = std::string()) = 0;

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Skrypt() = default;
	};
}
