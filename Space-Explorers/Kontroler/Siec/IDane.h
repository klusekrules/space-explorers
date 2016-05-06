#pragma once

namespace SpEx {

	/**
	* \brief Interfejs klasy zarządzającej danymi.
	*
	* Klasa abstrakcyjna zawierająca metody ogólne do zarządania danymi.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-05-2016
	*/
	class IDane {
	public:

		virtual ~IDane() = default;

		/**
		* \brief Pobierz flagi sterujące danymi.
		*
		* Metoda pobiera flagi sterujące danymi.
		* \return Flagi sterujące danymi.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual unsigned __int64 pobierzFlagi() const {
			return flagi_;
		}

		/**
		* \brief Ustaw flagi sterujące danymi.
		*
		* Metoda ustawia flagi sterujące danymi.
		* \param [in] flagi - Nowe flagi sterujące danymi.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual void ustawFlagi(unsigned __int64 flagi) {
			flagi_ = flagi;
		}

		/**
		* \brief Rozmiar przechowywanych danych.
		*
		* Metoda zwraca rozmiar danych jakie przechowuje.
		* \return Rozmiar przechowywanych danych.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual unsigned __int64 rozmiar() const = 0;

		/**
		* \brief Wprowadzenie danych do kontenera
		*
		* Metoda dodaje wprowadza dane przekazane w parametrach do kontenera wewnętrzenego.
		* \param[in] dane - Dane do przekazania.
		* \param[in] rozmiar - Rozmiar przekazanych danych.
		* \return Status zakończenia metody.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual int wez(const char * dane, unsigned __int64 rozmiar) = 0;

		/**
		* \brief Pobranie danych z kontenera.
		*
		* Metoda wystawia dane z kontenera.
		* \param[inout] rozmiar - Rozmiar przekazanych danych.
		* \return Wskaźnik do przekazanych danych.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		virtual int daj(const char ** dane, unsigned __int64& rozmiar) = 0;

	protected:
		unsigned __int64 flagi_;
	};
}