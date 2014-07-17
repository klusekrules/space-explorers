
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
	struct __declspec(dllexport) Stan_t{
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
	struct __declspec(dllexport) Zdarzenie_t{
		int idStanu_; /// Numer stanu.
		int numer_; /// Numer dodatkowy.
		int idZdarzenia_; /// Numer zdarzenia.
	};
};

/** @} */
