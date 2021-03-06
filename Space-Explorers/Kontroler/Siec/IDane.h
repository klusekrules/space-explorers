#pragma once

#define FLAGA_KOMPRESJA		0x1
#define FLAGA_SZYFROWANIE	0x2
#define FLAGA_WERSJA		0x1

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
		friend class GniazdoWinSock;
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

		virtual int przygotujDane() = 0;
		
	protected:
		unsigned __int64 flagi_; //Flagi sterujące danymi.

		virtual int wyslij(GniazdoWinSock& e, int flagi) = 0;

		virtual int odbierz(GniazdoWinSock& e, int flagi) = 0;
		
	};
}