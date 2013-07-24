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
* \brief Klasa zarz�dzaj�ca wymaganiami.
* 
* Klasa gromadzi i zarz�dza wymaganiami obiektu.
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
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	explicit Wymagania( TiXmlElement* wezel );

	/**
	* \brief Destruktor.
	*/
	virtual ~Wymagania();

	/**
	* \brief Metoda wyliczaj�ca czas trwania budowy obiektu.
	*
	* Metoda wylicza czas jaki jest potrzebny, aby wybudowa� obiekty o podanej ilo�ci, na planecie przekazanej przez parametry.
	* \param[in] ilosc - Ilo�� obiekt�w dla kt�rych jest wyliczany czas.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia czasu.
	* \return Czas jaki zosta� wyliczony.
	*/
	virtual Czas pobierzCzasBudowy( const Ilosc& ilosc, const PodstawoweParametry& parametry )const;

	/**
	* \brief Metoda wyliczaj�ca koszty budowy obiektu.
	*
	* Metoda wylicza potrzebne koszty, aby wybudowa� obiekty o podanej ilo�ci, na planecie przekazanej przez parametry.
	* \param[in] ilosc - Ilo�� obiekt�w dla kt�rych s� wyliczane koszty.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia koszt�w.
	* \return Lista koszt�w jaka zosta�a wyliczona.
	*/
	PrzetworzonaCena pobierzKoszty(const Ilosc& ilosc, const PodstawoweParametry& parametry ) const;

	/**
	* \brief Metoda sprawdzaj�ca czy obiekt spe�nia koszty budowy.
	*
	* Metoda wylicza potrzebne koszty, a nast�pnie sprawdza czy na planecie znajduje si� odpowiednia liczba zasob�w.
	* \param[in] ilosc - Ilo�� obiekt�w dla kt�rych s� wyliczane koszty.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia koszt�w.
	* \return true je�eli mo�na wybudowa� obiekty, false w przeciwnym wypadku.
	*/
	bool czySpelniaKoszty( const Ilosc& ilosc, const PodstawoweParametry& parametry ) const;

	/**
	* \brief Metoda wyliczaj�ca wymagania budowy obiektu.
	*
	* Metoda wylicza potrzebne wymagania, aby wybudowa� obiekty, na planecie przekazanej przez parametry.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymaga�.
	* \return Lista wymaga� jaka zosta�a wyliczona.
	*/
	PrzetworzoneWymogi pobierzWymogi( const PodstawoweParametry& parametry ) const;

	/**
	* \brief Metoda sprawdzaj�ca czy obiekt spe�nia wymagania budowy.
	*
	* Metoda wylicza potrzebne wymagania, a nast�pnie sprawdza czy planeta spe�nia wymagania.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymaga�.
	* \return true je�eli mo�na wybudowa� obiekty, false w przeciwnym wypadku.
	*/
	bool czySpelniaWymogi( const PodstawoweParametry& parametry ) const;

	/**
	* \brief Metoda sprawdzaj�ca czy obiekt spe�nia wymagania i koszty budowy.
	*
	* Metoda wylicza potrzebne wymagania i koszty, a nast�pnie sprawdza czy planeta spe�nia wymagania i zawiera potrzebne zasoby.
	* \param[in] parametry - Podstawowe parametry potrzebne do wyliczenia wymaga� i koszt�w.
	* \return true je�eli mo�na wybudowa� obiekty, false w przeciwnym wypadku.
	*/
	bool czySpelniaWymagania( const Ilosc& ilosc , const PodstawoweParametry& parametry )const;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;
private:
	ListaCen koszty_; /// Lista koszt�w.
	ListaWymogow warunki_; /// Lista wymog�w.
	shared_ptr <ZmianaInterfejs> zmianaCzasuBudowy_; /// Zmiana czasu budowy.

	/**
	* \brief Metoda dodaj�ca wym�g do listy.
	*
	* Metoda dodaje wym�g do listy. Sprawdza czy istnieje odpowiadaj�cy wym�g i je�eli znajduj�cy si� na li�cie jest mniej rygorystyczny zostanie nadpisany przez przekazany wym�g.
	* \param[in] wymog - Wym�g dodany do listy.
	* \return true je�eli dodano wym�g, false w przeciwnym wypadku.
	* \remark Mniej rygorystyczny tzn. podstawowa warto�� poziomu jest mniejsza do dodawanego wymogu.
	*/
	bool dodajWymog( Wymog& wymog );

	/**
	* \brief Metoda dodaj�ca cen� do listy.
	*
	* Metoda dodaje cen� do listy. Sprawdza czy istnieje odpowiadaj�ca cena i je�eli znajduj�ca si� na li�cie jest mniej rygorystyczny zostanie nadpisany przez przekazan� cen�.
	* \param[in] wymog - Wym�g dodany do listy.
	* \return true je�eli dodano wym�g, false w przeciwnym wypadku.
	* \remark Mniej rygorystyczny tzn. podstawowa warto�� ilo�ci jest mniejsza od dodawanej ceny.
	*/
	bool dodajCene( Cena& cena );
};
