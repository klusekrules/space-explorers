#pragma once
#include <functional>
#include "Wymagania.h"

/**
* \brief Klasa pomocnicza do wyliczania wymogów obiektu.
* 
* Klasa wylicza wymóg przekazany w konstruktorze.
* \author Daniel Wojdak
* \version 1
* \date 23-07-2013
*/
class LiczenieWymogow
{
public:
	/**
	* \brief Konstruktor.
	* 
	* \param[in] wymog - Referencja do obiektu wymogu.
	* \param[in] zbiornik - Referencja do obiektu zbiornika.
	* \param[in] parametry - Referencja do obiektu podstwowych parametrów.
	*/
	LiczenieWymogow( Wymagania::Wymog& wymog, Wymagania::PrzetworzoneWymogi& zbiornik, const PodstawoweParametry& parametry );

	/**
	* \brief Operator wywo³uj¹cy metodê.
	* \return Rezultat zwrócony przez metodê.
	*/
	bool operator()();

private:

	/**
	* \brief Metoda wywo³ywana na rzecz wymogu.
	* \param[in] obiekt - Wymóg na którym pracuje metoda.
	* \param[in] zmiana - Zmiana wymogu na którym pracuje metoda.
	* \return true je¿eli metoda zakoñczy³a dzia³anie sukcesem, false w przeciwnym wypadku.
	*/
	bool wykonaj( Wymagania::Wymog::TypObiektu obiekt, Wymagania::Wymog::Zmiana zmiana);
	Wymagania::Wymog& wymog_; /// Wymóg na którym pracuje metoda wykonaj.
	Wymagania::PrzetworzoneWymogi& zbiornik_; /// Zbiornik do którego zostanie dodany przetworzony wymóg.
	const PodstawoweParametry& parametry_; /// Parametry podstawowe obiektu.
};
