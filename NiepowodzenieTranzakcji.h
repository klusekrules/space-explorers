#pragma once
#include "OgolnyWyjatek.h"

/**
* \brief Wyj¹tek b³êdu krytycznego wykonywanej tranzakcji.
*
* Wyj¹tek zostaje wyrzucony kiedy w trakcie cofania tranzakcji wyst¹pi³ wyj¹tek, b¹dŸ funkcja siê nie powiod³a.
*/
class NiepowodzenieTranzakcji :
	public OgolnyWyjatek,
	virtual public LoggerInterface
{
public:
	static const Identyfikator domyslnyNiepowodzenieTranzakcjiID; /// Domyœlna wartoœæ id klasy.

	/**
	* \brief Konstruktor.
	*
	* \param[in] tPlik - Plik wyst¹pienia wyj¹tku.
	* \param[in] iLinia - Linia wytapienia wyj¹tku.
	* \param[in] tranzakcja - Opis tranzakcji dla ktorej wyst¹pi³ wyj¹tek.
	*/
	NiepowodzenieTranzakcji(const Tekst& tPlik, const Ilosc& iLinia, const Tekst& tranzakcja);

	/**
	* \brief Destruktor.
	*/
	virtual ~NiepowodzenieTranzakcji(void);

	/**
	* \brief Metoda tworz¹ca komunikat opisuj¹cyh wyj¹tek.
	* \return Tekst opisuj¹cy wyj¹tek.
	*/
	Tekst generujKomunikat() const override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;

protected:
	Tekst tranzakcja_; /// Opis tranzakcji

private:
	static const Tekst domyslnyNiepowodzenieTranzakcjiTytul; /// Domyœlny tytu³ wyjatku
	static const Tekst domyslnyNiepowodzenieTranzakcjiTresc; /// Domyœlna treœæ wyj¹tku
};

