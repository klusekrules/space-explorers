#pragma once
#include <functional>
#include "Wymagania.h"

/**
* \brief Klasa pomocnicza do wyliczania kosztów obiektu.
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
	* \param[in] parametry - Referencja do obiektu podstwowych parametrów.
	*/
	LiczenieKosztow( Wymagania::Cena& cena, Wymagania::PrzetworzonaCena& zbiornik, const Ilosc& ilosc, const PodstawoweParametry& parametry );

	/**
	* \brief Operator wywo³uj¹cy metodê.
	* \return Rezultat zwrócony przez metodê.
	*/
	bool operator()();

private:

	/**
	* \brief Metoda wywo³ywana na rzecz kosztu.
	* \param[in] obiekt - Koszt na którym pracuje metoda.
	* \param[in] zmiana - Zmiana kosztu na którym pracuje metoda.
	* \return true je¿eli metoda zakoñczy³a dzia³anie sukcesem, false w przeciwnym wypadku.
	*/
	bool wykonaj( Wymagania::Cena::TypObiektu obiekt, Wymagania::Cena::Zmiana zmiana);
	Wymagania::Cena& cena_; /// Koszt na którym pracuje metoda wykonaj.
	Wymagania::PrzetworzonaCena& zbiornik_; /// Zbiornik do którego zostanie dodana przetworzona cena.
	const Ilosc& ilosc_; /// Iloœæ obiektów dla których jest wyliczana cena.
	const PodstawoweParametry& parametry_; /// Parametry podstawowe obiektu.
};
