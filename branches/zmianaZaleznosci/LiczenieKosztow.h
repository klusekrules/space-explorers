#pragma once
#include <functional>
#include "Wymagania.h"

/**
* \brief Klasa pomocnicza do wyliczania koszt�w obiektu.
* 
* Klasa wylicza koszt przekazany w konstruktorze.
* \author Daniel Wojdak
* \version 1
* \date 23-07-2013
*/
class LiczenieKosztow
{
public:
	/**
	* \brief Konstruktor.
	* 
	* \param[in] cena - Referencja do obiektu ceny.
	* \param[in] zbiornik - Referencja do obiektu zbiornika.
	* \param[in] ilosc - Referencja do obiektu ilosc.
	* \param[in] parametry - Referencja do obiektu podstwowych parametr�w.
	*/
	LiczenieKosztow( Wymagania::Cena& cena, Wymagania::PrzetworzonaCena& zbiornik, const Ilosc& ilosc, const PodstawoweParametry& parametry );

	/**
	* \brief Operator wywo�uj�cy metod�.
	* \return Rezultat zwr�cony przez metod�.
	*/
	bool operator()();

private:

	/**
	* \brief Metoda wywo�ywana na rzecz kosztu.
	* \param[in] obiekt - Koszt na kt�rym pracuje metoda.
	* \param[in] zmiana - Zmiana kosztu na kt�rym pracuje metoda.
	* \return true je�eli metoda zako�czy�a dzia�anie sukcesem, false w przeciwnym wypadku.
	*/
	bool wykonaj( Wymagania::Cena::TypObiektu obiekt, Wymagania::Cena::Zmiana zmiana);
	Wymagania::Cena& cena_; /// Koszt na kt�rym pracuje metoda wykonaj.
	Wymagania::PrzetworzonaCena& zbiornik_; /// Zbiornik do kt�rego zostanie dodana przetworzona cena.
	const Ilosc& ilosc_; /// Ilo�� obiekt�w dla kt�rych jest wyliczana cena.
	const PodstawoweParametry& parametry_; /// Parametry podstawowe obiektu.
};
