#pragma once
#include <functional>

namespace SpEx{

	/**
	* \brief Klasa opakowuj¹ca zadanie.
	*
	* Klasa przechowuj¹ca funkcjê wykonuj¹c¹ zlecone zadanie.
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
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
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
		* \brief Metoda wykonuj¹ca funkcjê.
		*
		* Metoda wykonuj¹ca funkcjê.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void wykonaj();

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		~Zadanie(void) = default;
	};
};
