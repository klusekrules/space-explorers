#pragma once
#include <functional>
#include "Wymagania.h"

/**
* \brief Klasa pomocnicza do wyliczania wymog�w obiektu.
* 
* Klasa wylicza wym�g przekazany w konstruktorze.
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
	* \param[in] parametry - Referencja do obiektu podstwowych parametr�w.
	*/
	LiczenieWymogow( Wymagania::Wymog& wymog, Wymagania::PrzetworzoneWymogi& zbiornik, const PodstawoweParametry& parametry );

	/**
	* \brief Operator wywo�uj�cy metod�.
	* \return Rezultat zwr�cony przez metod�.
	*/
	bool operator()();

private:

	/**
	* \brief Metoda wywo�ywana na rzecz wymogu.
	* \param[in] obiekt - Wym�g na kt�rym pracuje metoda.
	* \param[in] zmiana - Zmiana wymogu na kt�rym pracuje metoda.
	* \return true je�eli metoda zako�czy�a dzia�anie sukcesem, false w przeciwnym wypadku.
	*/
	bool wykonaj( Wymagania::Wymog::TypObiektu obiekt, Wymagania::Wymog::Zmiana zmiana);
	Wymagania::Wymog& wymog_; /// Wym�g na kt�rym pracuje metoda wykonaj.
	Wymagania::PrzetworzoneWymogi& zbiornik_; /// Zbiornik do kt�rego zostanie dodany przetworzony wym�g.
	const PodstawoweParametry& parametry_; /// Parametry podstawowe obiektu.
};
