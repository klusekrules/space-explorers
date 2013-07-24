#pragma once
#include <vector>
#include <memory>
#include "parser\ticpp.h"
#include "FuncTransf\ZmianaInterfejs.h"
#include "PodstawoweParametry.h"
#include "Czas.h"

class Surowce;
class ObiektBazowyInfo;

#include "SzablonKosztow.h"

/**
* \brief Klasa zarz¹dzaj¹ca wymaganiami.
* 
* Klasa gromadzi i zarz¹dza wymaganiami obiektu.
* \author Daniel Wojdak
* \version 1
* \date 23-07-2013
*/
class Wymagania :
	virtual public LoggerInterface
{
public:
	typedef Surowce TypCeny;
	typedef SzablonKosztow< TypCeny > Cena;
	typedef vector< Cena::TypObiektu > PrzetworzonaCena;
	typedef vector< Cena > ListaCen;	

	typedef ObiektBazowyInfo TypWymogu;
	typedef SzablonKosztow< TypWymogu > Wymog;
	typedef vector< Wymog::TypObiektu > PrzetworzoneWymogi;
	typedef vector< Wymog > ListaWymogow;

	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit Wymagania( TiXmlElement* wezel );

	/**
	* \brief Destruktor.
	*/
	virtual ~Wymagania();

	/**
	* \brief Metoda wyliczaj¹ca czas trwania budowy obiektu.
	*
	* Metoda wylicza czas jaki jest potrzebny, aby wybudowaæ obiekty o podanej iloœci, na planecie przekazanej przez parametry.
	* \param[in] ilosc - Iloœæ obiektów dla których jest wyliczany czas.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia czasu.
	* \return Czas jaki zosta³ wyliczony.
	*/
	virtual Czas pobierzCzasBudowy( const Ilosc& ilosc, const PodstawoweParametry& parametry )const;

	/**
	* \brief Metoda wyliczaj¹ca koszty budowy obiektu.
	*
	* Metoda wylicza potrzebne koszty, aby wybudowaæ obiekty o podanej iloœci, na planecie przekazanej przez parametry.
	* \param[in] ilosc - Iloœæ obiektów dla których s¹ wyliczane koszty.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia kosztów.
	* \return Lista kosztów jaka zosta³a wyliczona.
	*/
	PrzetworzonaCena pobierzKoszty(const Ilosc& ilosc, const PodstawoweParametry& parametry ) const;

	/**
	* \brief Metoda sprawdzaj¹ca czy obiekt spe³nia koszty budowy.
	*
	* Metoda wylicza potrzebne koszty, a nastêpnie sprawdza czy na planecie znajduje siê odpowiednia liczba zasobów.
	* \param[in] ilosc - Iloœæ obiektów dla których s¹ wyliczane koszty.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia kosztów.
	* \return true je¿eli mo¿na wybudowaæ obiekty, false w przeciwnym wypadku.
	*/
	bool czySpelniaKoszty( const Ilosc& ilosc, const PodstawoweParametry& parametry ) const;

	/**
	* \brief Metoda wyliczaj¹ca wymagania budowy obiektu.
	*
	* Metoda wylicza potrzebne wymagania, aby wybudowaæ obiekty, na planecie przekazanej przez parametry.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymagañ.
	* \return Lista wymagañ jaka zosta³a wyliczona.
	*/
	PrzetworzoneWymogi pobierzWymogi( const PodstawoweParametry& parametry ) const;

	/**
	* \brief Metoda sprawdzaj¹ca czy obiekt spe³nia wymagania budowy.
	*
	* Metoda wylicza potrzebne wymagania, a nastêpnie sprawdza czy planeta spe³nia wymagania.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymagañ.
	* \return true je¿eli mo¿na wybudowaæ obiekty, false w przeciwnym wypadku.
	*/
	bool czySpelniaWymogi( const PodstawoweParametry& parametry ) const;

	/**
	* \brief Metoda sprawdzaj¹ca czy obiekt spe³nia wymagania i koszty budowy.
	*
	* Metoda wylicza potrzebne wymagania i koszty, a nastêpnie sprawdza czy planeta spe³nia wymagania i zawiera potrzebne zasoby.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymagañ i kosztów.
	* \return true je¿eli mo¿na wybudowaæ obiekty, false w przeciwnym wypadku.
	*/
	bool czySpelniaWymagania( const Ilosc& ilosc , const PodstawoweParametry& parametry )const;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;
private:
	ListaCen koszty_; /// Lista kosztów.
	ListaWymogow warunki_; /// Lista wymogów.
	shared_ptr <ZmianaInterfejs> zmianaCzasuBudowy_; /// Zmiana czasu budowy.

	/**
	* \brief Metoda dodaj¹ca wymóg do listy.
	*
	* Metoda dodaje wymóg do listy. Sprawdza czy istnieje odpowiadaj¹cy wymóg i je¿eli znajduj¹cy siê na liœcie jest mniej rygorystyczny zostanie nadpisany przez przekazany wymóg.
	* \param[in] wymog - Wymóg dodany do listy.
	* \return true je¿eli dodano wymóg, false w przeciwnym wypadku.
	* \remark Mniej rygorystyczny tzn. podstawowa wartoœæ poziomu jest mniejsza do dodawanego wymogu.
	*/
	bool dodajWymog( Wymog& wymog );

	/**
	* \brief Metoda dodaj¹ca cenê do listy.
	*
	* Metoda dodaje cenê do listy. Sprawdza czy istnieje odpowiadaj¹ca cena i je¿eli znajduj¹ca siê na liœcie jest mniej rygorystyczny zostanie nadpisany przez przekazan¹ cenê.
	* \param[in] wymog - Wymóg dodany do listy.
	* \return true je¿eli dodano wymóg, false w przeciwnym wypadku.
	* \remark Mniej rygorystyczny tzn. podstawowa wartoœæ iloœci jest mniejsza od dodawanej ceny.
	*/
	bool dodajCene( Cena& cena );
};
