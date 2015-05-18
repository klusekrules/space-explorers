#pragma once
#include <string>
#include "Narzedzia\NonCopyable.h"

namespace SpEx{

	/**
	* \brief Klasa ujednolicaj¹ca interfejs dla skryptu.
	*
	* Klasa zawieraj¹ca podstawowy interfejs do wykonywania skryptów.
	* \author Daniel Wojdak
	* \version 2
	* \date 05-08-2014
	*/
	class Skrypt :
		public se::NonCopyable
	{
	public:
		/**
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		Skrypt() = default;

		/**
		* \brief Metoda wykonuj¹ca skrypt.
		*
		* Metoda s³u¿¹ca do wykonywania skryptu.
		* \param[in] metoda - Nazwa metody.
		* \return Zwracana jest wartoœæ true, je¿eli uda siê wykonaæ skrypt lub false w przeciwnym wypadku.
		*/
		virtual bool wykonaj(const std::string& metoda = std::string()) = 0;

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Skrypt() = default;
	};
}
