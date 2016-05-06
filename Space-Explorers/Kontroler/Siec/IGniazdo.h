#pragma once
#include "IDane.h"
#include <functional>

namespace SpEx {
	/**
	* \brief Interfejs klasy zarz¹dzaj¹cej gniazdami sieciowymi.
	*
	* Klasa abstrakcyjna zawieraj¹ca metody ogólne do zarz¹dania gniazdami sieciowymi.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-05-2016
	*/
	class IGniazdo {
	public:

		/**
		* \brief Wysy³anie danych przez gniazdo.
		*
		* Metoda wysy³a dane przez gniazdo.
		* \param[in] dane - Dane do wys³ania.
		* \param[in] rozmiar - Rozmiar przekazanych danych.
		* \param[in] flagi - Flagi przekazywane do funkcji wysy³aj¹cej.
		* \return Status zakoñczenia metody.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual int wyslij(const char* dane, int rozmiar, int flagi = 0) = 0;

		/**
		* \brief Odbieranie danych z gniazda.
		*
		* Metoda odbiera dane z gniazda.
		* \param[in] dane - Dane do wys³ania.
		* \param[in] rozmiar - Rozmiar bufora danych odbieranych.
		* \param[in] flagi - Flagi przekazywane do funkcji wysy³aj¹cej.
		* \return Status zakoñczenia metody.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual int odbierz(char* dane, int rozmiar, int flagi = 0) = 0;

		/**
		* \brief Wysy³anie danych przez gniazdo.
		*
		* Metoda wysy³a dane przez gniazdo.
		* \param[in] dane - Dane do wys³ania.
		* \param[in] flagi - Flagi przekazywane do funkcji wysy³aj¹cej.
		* \return Status zakoñczenia metody.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual int wyslij(IDane & dane, int flagi = 0) = 0;

		/**
		* \brief Odbieranie danych z gniazda.
		*
		* Metoda odbiera dane z gniazda.
		* \param[inout] dane - Dane odebrane.
		* \param[in] flagi - Flagi przekazywane do funkcji odbieraj¹cej.
		* \return Status zakoñczenia metody.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual int odbierz(IDane &dane, int flagi = 0) = 0;

		/**
		* \brief Pobieranie IP gniazda.
		*
		* Metoda zwraca IP powi¹zane z gniazdem.
		* \return IP gniazda.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual unsigned int pobierzIP() const = 0;

		/**
		* \brief Metoda ustawia warunek oczekiwania.
		*
		* Metoda ustawia warunek oczekiwania na gnieŸdzie.
		* \param[in] warunek - Nowy warunke oczekiwania. 
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual void ustawWarunekOczekiwania( std::function <bool(void)> warunek ) = 0;
	};
}