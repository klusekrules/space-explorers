#pragma once
#include "Obiekt.h"

/**
* \brief Klasa Budynku
*
* Klasa implementuje metody zale�ne od dzia�ania obiektu. Dodaje metody pobieraj�ce zapotrzebowanie i produkcje obiektu.
* \author Daniel Wojdak
* \version 1
* \date 24-07-2013
*/
class Budynek :
	public Obiekt,
	virtual public LoggerInterface
{
	friend class BudynekInfo;
public:

	/**
	* \brief Konstruktor.
	*
	* \param[in] poziom - Poziom tworzonych obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] obiektInfo - Referencja do obiektu opisuj�cego.
	*/
	Budynek(const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const BudynekInfo& obiektInfo);

	/**
	* \brief Konstruktor.
	*
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
	* \param[in] obiektInfo - Referencja do obiektu opisuj�cego.
	*/
	Budynek(const PodstawoweParametry& podstawoweParametry, const BudynekInfo& obiektInfo);

	/**
	* \brief Destruktor.
	*/
	virtual ~Budynek();

	/**
	* \brief Metoda wyliczaj�ca zapotrzebowanie.
	*
	* Metoda wylicza zapotrzebowanie dla danego obiektu.
	* \return Lista element�w zapotrzebowania obiektu.
	*/
	Wymagania::PrzetworzonaCena pobierzZapotrzebowanie( )const;

	/**
	* \brief Metoda wyliczaj�ca produkcj�.
	*
	* Metoda wylicza produkcj� dla danego obiektu.
	* \return Lista element�w produkcji obiektu.
	*/
	Wymagania::PrzetworzonaCena pobierzProdukcje( )const;

	/**
	* Metoda kopiuj�ca obiekt. 
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	Budynek* kopia() const override;

	/**
	* Metoda dziel�ca obiekt, nie jest wspierana dla budynku, zawsze zwraca nullptr.
	* \param[in] ilosc - Nieu�ywany.
	* \return  Metoda zawsze zwraca nullptr.
	*/
	Budynek* podziel( const Ilosc& ilosc ) override;

	/**
	* Metoda ��czy obiekt bazowy z obiektem przekazanym przez parametr.
	* \param[in] obiektbazowy - Nieu�ywany.
	* \return Zawsze zwraca warto�� false.
	*/
	bool polacz( const ObiektBazowy& obiektbazowy ) override;
	
	/**
	* Metoda sprawdzaj�ca warunki po��czenia obiekt�w.
	* \param[in] obiektbazowy - Nieu�ywany.
	* \return Zawsze zwraca warto�� false.
	*/
	bool czyMoznaPolaczyc( const ObiektBazowy& obiektbazowy ) const override;

	/**
	* Metoda sprawdzaj�ca czy mo�na podzieli� obiekt wed�ug podanej ilo�ci.
	* \param[in] ilosc - Nieu�ywany.
	* \return Zawsze zwraca warto�� false.
	*/
	bool czyMoznaPodzielic( const Ilosc& ilosc ) const override;

	/**
	* Metoda buduj�ca obiekty o podanej ilo�ci.
	* \warning Metoda nie sprawdza czy obiekty moga by� wybudowane.
	*/
	void wybuduj(const Ilosc&) override;

	/**
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
	* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( TiXmlElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	* \warning Metoda nie modyfikuje w�z�a.
	* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
	*/
	bool odczytaj( TiXmlElement* wezel ) override;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis()const override;

protected:
	const BudynekInfo& budynekInfo_; /// Referencja do obiektu opisowego.
};
