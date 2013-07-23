#pragma once
#include "Bazowa.h"
#include "Ilosc.h"
#include "PodstawoweParametry.h"
#include "Klucz.h"
#include "Wymagania.h"

class ObiektBazowyInfo;

/**
* \brief Klasa bazowa dla obiekt�w gry. 
* 
* Gromadzi informacje o identyfikatorze, poziomie i ilo�ci obiekt�w.
* Klasa umo�liwa jednoznaczne zidentyfikowanie obiekt�w w grze.
* Klasa dodaje interfejs kopiowania, �aczenia i dzielenia obiekt�w.
* \author Daniel Wojdak
* \version 1
* \date 22-07-2013
*/
class ObiektBazowy :
	public Bazowa,
	virtual public PodstawoweParametry,
	virtual public LoggerInterface,
	virtual public Serializacja
{
protected:	
	Ilosc ilosc_; /// Ilo�� obiekt�w.
	const ObiektBazowyInfo& obiektBazowyInfo_; /// Referencja do klasy opisuj�cej.

public:

	/**
	* \brief Konstruktor.
	*
	* Podstawowy konstruktor obiektu.
	* \param[in] ilosc - Ilo�� obiekt�w.
	* \param[in] poziom - Poziom obiektu.	
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] obiektBazowyInfo - Referencja do obiektu opisuj�cego tworzony obiekt.
	*/
	ObiektBazowy( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const ObiektBazowyInfo& obiektBazowyInfo) throw();

	/**
	* \brief Konstruktor.
	*
	* Podstawowy konstruktor obiektu.
	* \param[in] ilosc - Ilo�� obiekt�w.
	* \param[in] parametryPodstawowe - Parametry podstawowe obiektu.
	* \param[in] obiektBazowyInfo - Referencja do obiektu opisuj�cego tworzony obiekt.
	*/
	ObiektBazowy( const Ilosc& ilosc, const PodstawoweParametry& parametryPodstawowe, const ObiektBazowyInfo& obiektBazowyInfo) throw();

	/**
	* Metoda kopiuj�ca obiekt. 
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	virtual ObiektBazowy* kopia() const;

	/**
	* Metoda dziel�ca klas� wzdl�dem ilo�ci podanej przez argument.
	* Zwr�cony obiekt ma ilo�� r�wn� podan� przez parametr.
	* Obiekt bazowy ma ilo�� zmniejszon� o podan� przez parametr warto��.
	* \param[in] ilosc - Ilo�� obiekt�w wzgl�dem, kt�rego jest podzielony obiekt.
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Wskazanie na podzielony obiekt. Je�eli nie mo�na by�o podzieli� obiektu, zostaje zwr�cony nullptr.
	* \remark Metoda jest tranzakcyjna.
	*/
	virtual ObiektBazowy* podziel( const Ilosc& ilosc );

	/**
	* Metoda ��czy obiekt bazowy z obiektem przekazanym przez parametr.
	* \param[in] obiektbazowy - Obiekt do po��czenia.
	* \warning Metoda nie zwalnia pami�ci przekazanego obiektu.
	* \return Kiedy obiekty zostan� po��czone, zwracana warto�� to true, w przeciwnym wypadku zwr�cona warto�� to false.
	* \remark Metoda jest tranzakcyjna.
	*/
	virtual bool polacz( const ObiektBazowy& obiektbazowy );

	/**
	* Metoda sprawdzaj�ca warunki po��czenia obiekt�w.
	* \param[in] obiektbazowy - Obiekt dla kt�rego maj� by� sprawdzone warunki po��czenia.
	* \return Kiedy obiekt mo�e by� po��czony, zwracana warto�� to true, w przeciwnym wypadku zwr�cona warto�� to false.
	*/
	virtual bool czyMoznaPolaczyc( const ObiektBazowy& obiektbazowy ) const;

	/**
	* Metoda sprawdzaj�ca czy mo�na podzieli� obiekt wed�ug podanej ilo�ci.
	* \param[in] ilosc - Ilo�� w zgl�dem, kt�rej s� sprawdzane warunki podzia�u.
	* \return Je�eli mo�na podzieli�, zwracana jest warto�� true, w przeciwnym wypadku zwr�cona warto�� to false.
	*/
	virtual bool czyMoznaPodzielic( const Ilosc& ilosc ) const;

	/**
	* Metoda buduj�ca obiekty o podanej ilo�ci.
	* \warning Metoda nie sprawdza czy obiekty moga by� wybudowane.
	*/
	virtual void wybuduj(const Ilosc& ilosc);

	/**
	* \brief Metoda pobieraj�ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca ilo�� obiekt�w.
	*/
	const Ilosc& pobierzIlosc() const;

	/**
	* \brief Metoda ustawiaj�ca atrybut.
	*
	* Metoda ustawiaj�ca atrybut obiektu.
	* \param[in] ilosc - Nowa warto�� ilo�ci obiekt�w.
	*/
	void ustawIlosc( const Ilosc& ilosc );

	/**
	* Metoda s�u�y do zwr�cenia klucza jednozancznie identyfikuj�cego typ obiektu. 
	* Klucz sk�ada si� z identyfikatora obiektu i poziomu obiektu.
	* \return Klucz identyfikuj�cy obiekt.
	*/
	Klucz ID() const;

	/**
	* Metoda pobieraj�ca przetworzone warunki dost�pno�ci obiektu
	* \return Warunki po przetworzeniu przez klasy zmieniaj�ce
	*/
	Wymagania::PrzetworzoneWymogi pobierzWarunkiRozbudowy()const;

	/**
	* Metoda pobieraj�ca przetworzone koszty dost�pno�ci obiektu
	* \return Koszty po przetworzeniu przez klasy zmieniaj�ce
	*/
	Wymagania::PrzetworzonaCena pobierzKosztyRozbudowy() const;

	/**
	* Metoda wyliczaj�ca czas trwania rozbudowy jednego obiektu na kolejny poziom.
	* \return Czas trwania rozbudowy.
	*/
	Czas pobierzCzasRozbudowy( )const;

	/**
	* Metoda sprawdzaj�ca wymagania obiektu.
	* \return Je�eli obiekt spe�nia wymagania zwr�cona jest warto�� true. Je�eli nie spe�nia wymaga� zwr�cona jest warto�� false.
	*/
	bool czyMoznaRozbudowac()const;

	/**
	* Metoda zwracaj�ca referencej do obiektu opisuj�cego.
	* \return referencja do obiektu opisuj�cego.
	*/
	const ObiektBazowyInfo& getObiektBaseInfo()const;

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
	string napis() const override;
};
