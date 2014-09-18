#pragma once
#ifdef SPACE_EXPLORERS_API_EXPORT
#define SPACE_EXPLORERS_API __declspec(dllexport)
#else
#define SPACE_EXPLORERS_API __declspec(dllimport)
#endif

/** @weakgroup group1 
*  @{
*/

extern "C"{ 
	/**
	* \brief Struktura opisuj¹ca stan
	*
	* Struktura przechowuje informacje o stanie aplikacji. Struktura przeznaczona do u¿ywania w skryptach.
	* \author Daniel Wojdak
	* \version 1
	* \date 09-07-2014
	*/
	struct SPACE_EXPLORERS_API Stan_t{
		int idStanu_; /// Numer stanu.
		int numer_; /// Numer dodatkowy.
	};

	/**
	* \brief Struktura zdarzenia
	*
	* Struktura przechowuje informacje o zdarzeniu. Struktura przeznaczona do u¿ywania w skryptach.
	* \author Daniel Wojdak
	* \version 1
	* \date 09-07-2014
	*/
	struct SPACE_EXPLORERS_API Zdarzenie_t{
		int idStanu_; /// Numer stanu.
		int numer_; /// Numer dodatkowy.
		int idZdarzenia_; /// Numer zdarzenia.
	};
};

/** @} */
