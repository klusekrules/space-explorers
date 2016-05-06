#pragma once
#include "IDane.h"
#include <functional>

namespace SpEx {
	/**
	* \brief Interfejs klasy zarz�dzaj�cej gniazdami sieciowymi.
	*
	* Klasa abstrakcyjna zawieraj�ca metody og�lne do zarz�dania gniazdami sieciowymi.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-05-2016
	*/
	class IGniazdo {
	public:

		/**
		* \brief Wysy�anie danych przez gniazdo.
		*
		* Metoda wysy�a dane przez gniazdo.
		* \param[in] dane - Dane do wys�ania.
		* \param[in] rozmiar - Rozmiar przekazanych danych.
		* \param[in] flagi - Flagi przekazywane do funkcji wysy�aj�cej.
		* \return Status zako�czenia metody.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual int wyslij(const char* dane, int rozmiar, int flagi = 0) = 0;

		/**
		* \brief Odbieranie danych z gniazda.
		*
		* Metoda odbiera dane z gniazda.
		* \param[in] dane - Dane do wys�ania.
		* \param[in] rozmiar - Rozmiar bufora danych odbieranych.
		* \param[in] flagi - Flagi przekazywane do funkcji wysy�aj�cej.
		* \return Status zako�czenia metody.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual int odbierz(char* dane, int rozmiar, int flagi = 0) = 0;

		/**
		* \brief Wysy�anie danych przez gniazdo.
		*
		* Metoda wysy�a dane przez gniazdo.
		* \param[in] dane - Dane do wys�ania.
		* \param[in] flagi - Flagi przekazywane do funkcji wysy�aj�cej.
		* \return Status zako�czenia metody.
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
		* \param[in] flagi - Flagi przekazywane do funkcji odbieraj�cej.
		* \return Status zako�czenia metody.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual int odbierz(IDane &dane, int flagi = 0) = 0;

		/**
		* \brief Pobieranie IP gniazda.
		*
		* Metoda zwraca IP powi�zane z gniazdem.
		* \return IP gniazda.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual unsigned int pobierzIP() const = 0;

		/**
		* \brief Metoda ustawia warunek oczekiwania.
		*
		* Metoda ustawia warunek oczekiwania na gnie�dzie.
		* \param[in] warunek - Nowy warunke oczekiwania. 
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual void ustawWarunekOczekiwania( std::function <bool(void)> warunek ) = 0;
	};
}