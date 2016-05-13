#pragma once
#include "IDane.h"
#include <functional>
#include <WinSock2.h>

namespace SpEx {
	/**
	* \brief Klasa opakowuj�ce interfejs wysy�ania danych przez gniazda sieciowe.
	*
	* Klasa zawiera metody u�atwiaj�ce wysy�anie danych z r�nych �r�de� przez gniazda sieciowe.
	* \author Daniel Wojdak
	* \version 2
	* \date 10-05-2016
	*/
	class GniazdoWinSock {
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
		int wyslij(const char* dane, int rozmiar, int flagi = 0) {
			return send(gniazdo_, dane, rozmiar, flagi);
		}

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
		int odbierz(char* dane, int rozmiar, int flagi = 0) {
			return recv(gniazdo_, dane, rozmiar, flagi);
		}

		/**
		* \brief Wysy�anie danych przez gniazdo.
		*
		* Metoda wysy�a dane przez gniazdo.
		* \param[in] dane - Dane do wys�ania.
		* \param[in] flagi - Flagi przekazywane do funkcji wysy�aj�cej.
		* \return Status zako�czenia metody.
		* \author Daniel Wojdak
		* \version 2
		* \date 10-05-2016
		*/
		inline int wyslij(IDane & dane, int flagi = 0) {
			return dane.wyslij(*this, flagi);
		}

		/**
		* \brief Odbieranie danych z gniazda.
		*
		* Metoda odbiera dane z gniazda.
		* \param[inout] dane - Dane odebrane.
		* \param[in] flagi - Flagi przekazywane do funkcji odbieraj�cej.
		* \return Status zako�czenia metody.
		* \author Daniel Wojdak
		* \version 2
		* \date 10-05-2016
		*/
		inline int odbierz(IDane &dane, int flagi = 0) {
			return dane.odbierz(*this,flagi);
		}

		/**
		* \brief Pobieranie IP gniazda.
		*
		* Metoda zwraca IP powi�zane z gniazdem.
		* \return IP gniazda.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		unsigned int pobierzIP() const {
			return addr_.sin_addr.S_un.S_addr;
		}

		/**
		* \brief Metoda ustawia warunek oczekiwania.
		*
		* Metoda ustawia warunek oczekiwania na gnie�dzie.
		* \param[in] warunek - Nowy warunke oczekiwania. 
		* \author Daniel Wojdak
		* \version 1
		* \date 06-05-2016
		*/
		void ustawWarunekOczekiwania(std::function <bool(void)> warunek) {
			warunek_ = warunek;
		}

		inline bool sprawdzWarunek() {
			return warunek_ == nullptr || warunek_();
		}
	private:
		SOCKET gniazdo_; // Uchwyt gniazda.
		struct sockaddr_in addr_; // Struktura opisuj�ca gniazdo.
		std::function <bool(void)> warunek_; // Dodatkowy warunek przerwania p�tli pobieraj�cej lub wysy�aj�cej dane.
	};
}