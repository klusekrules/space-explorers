#pragma once
#include "IDane.h"
#include <functional>
#include <WinSock2.h>

namespace SpEx {
	/**
	* \brief Klasa opakowuj¹ce interfejs wysy³ania danych przez gniazda sieciowe.
	*
	* Klasa zawiera metody u³atwiaj¹ce wysy³anie danych z ró¿nych Ÿróde³ przez gniazda sieciowe.
	* \author Daniel Wojdak
	* \version 2
	* \date 10-05-2016
	*/
	class GniazdoWinSock {
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
		int wyslij(const char* dane, int rozmiar, int flagi = 0) {
			return send(gniazdo_, dane, rozmiar, flagi);
		}

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
		int odbierz(char* dane, int rozmiar, int flagi = 0) {
			return recv(gniazdo_, dane, rozmiar, flagi);
		}

		/**
		* \brief Wysy³anie danych przez gniazdo.
		*
		* Metoda wysy³a dane przez gniazdo.
		* \param[in] dane - Dane do wys³ania.
		* \param[in] flagi - Flagi przekazywane do funkcji wysy³aj¹cej.
		* \return Status zakoñczenia metody.
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
		* \param[in] flagi - Flagi przekazywane do funkcji odbieraj¹cej.
		* \return Status zakoñczenia metody.
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
		* Metoda zwraca IP powi¹zane z gniazdem.
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
		* Metoda ustawia warunek oczekiwania na gnieŸdzie.
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
		struct sockaddr_in addr_; // Struktura opisuj¹ca gniazdo.
		std::function <bool(void)> warunek_; // Dodatkowy warunek przerwania pêtli pobieraj¹cej lub wysy³aj¹cej dane.
	};
}