#pragma once
#include <functional>

namespace SpEx{

	/**
	* \brief Klasa opakowuj�ca zadanie.
	*
	* Klasa przechowuj�ca funkcj� wykonuj�c� zlecone zadanie.
	* \author Daniel Wojdak
	* \version 1
	* \date 10-07-2014
	*/
	class Zadanie
	{
	private:
		std::function<void()> funkcja_; /// Uchwyt do funkcji z zadaniem.
	public:

		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		Zadanie() = default;
		
		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] zadanie - Funkcja do wykonania.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		Zadanie(std::function<void()>& zadanie);

		/**
		* \brief Metoda wykonuj�ca funkcj�.
		*
		* Metoda wykonuj�ca funkcj�.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void wykonaj();

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		~Zadanie(void) = default;
	};
};
