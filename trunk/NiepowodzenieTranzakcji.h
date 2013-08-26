#pragma once
#include "OgolnyWyjatek.h"

/**
* \brief Wyj�tek b��du krytycznego wykonywanej tranzakcji.
*
* Wyj�tek zostaje wyrzucony kiedy w trakcie cofania tranzakcji wyst�pi� wyj�tek, b�d� funkcja si� nie powiod�a.
*/
class NiepowodzenieTranzakcji :
	public OgolnyWyjatek,
	virtual public LoggerInterface
{
public:
	static const Identyfikator domyslnyNiepowodzenieTranzakcjiID; /// Domy�lna warto�� id klasy.

	/**
	* \brief Konstruktor.
	*
	* \param[in] tPlik - Plik wyst�pienia wyj�tku.
	* \param[in] iLinia - Linia wytapienia wyj�tku.
	* \param[in] tranzakcja - Opis tranzakcji dla ktorej wyst�pi� wyj�tek.
	*/
	NiepowodzenieTranzakcji(const Tekst& tPlik, const Ilosc& iLinia, const Tekst& tranzakcja);

	/**
	* \brief Destruktor.
	*/
	virtual ~NiepowodzenieTranzakcji(void);

	/**
	* \brief Metoda tworz�ca komunikat opisuj�cyh wyj�tek.
	* \return Tekst opisuj�cy wyj�tek.
	*/
	Tekst generujKomunikat() const override;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;

protected:
	Tekst tranzakcja_; /// Opis tranzakcji

private:
	static const Tekst domyslnyNiepowodzenieTranzakcjiTytul; /// Domy�lny tytu� wyjatku
	static const Tekst domyslnyNiepowodzenieTranzakcjiTresc; /// Domy�lna tre�� wyj�tku
};

