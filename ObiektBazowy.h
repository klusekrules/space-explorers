#pragma once
#include "Bazowa.h"
#include "Ilosc.h"
#include "PodstawoweParametry.h"
#include "Klucz.h"
#include "Wymagania.h"

class ObiektBazowyInfo;

/**
* \brief Klasa bazowa dla obiektów gry. 
* 
* Gromadzi informacje o identyfikatorze, poziomie i iloœci obiektów.
* Klasa umo¿liwa jednoznaczne zidentyfikowanie obiektów w grze.
* Klasa dodaje interfejs kopiowania, ³aczenia i dzielenia obiektów.
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
	Ilosc ilosc_; /// Iloœæ obiektów.
	const ObiektBazowyInfo& obiektBazowyInfo_; /// Referencja do klasy opisuj¹cej.

public:

	/**
	* \brief Konstruktor.
	*
	* Podstawowy konstruktor obiektu.
	* \param[in] ilosc - Iloœæ obiektów.
	* \param[in] poziom - Poziom obiektu.	
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] obiektBazowyInfo - Referencja do obiektu opisuj¹cego tworzony obiekt.
	*/
	ObiektBazowy( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const ObiektBazowyInfo& obiektBazowyInfo) throw();

	/**
	* \brief Konstruktor.
	*
	* Podstawowy konstruktor obiektu.
	* \param[in] ilosc - Iloœæ obiektów.
	* \param[in] parametryPodstawowe - Parametry podstawowe obiektu.
	* \param[in] obiektBazowyInfo - Referencja do obiektu opisuj¹cego tworzony obiekt.
	*/
	ObiektBazowy( const Ilosc& ilosc, const PodstawoweParametry& parametryPodstawowe, const ObiektBazowyInfo& obiektBazowyInfo) throw();

	/**
	* Metoda kopiuj¹ca obiekt. 
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	virtual ObiektBazowy* kopia() const;

	/**
	* Metoda dziel¹ca klasê wzdlêdem iloœci podanej przez argument.
	* Zwrócony obiekt ma iloœæ równ¹ podan¹ przez parametr.
	* Obiekt bazowy ma iloœæ zmniejszon¹ o podan¹ przez parametr wartoœæ.
	* \param[in] ilosc - Iloœæ obiektów wzglêdem, którego jest podzielony obiekt.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Wskazanie na podzielony obiekt. Je¿eli nie mo¿na by³o podzieliæ obiektu, zostaje zwrócony nullptr.
	* \remark Metoda jest tranzakcyjna.
	*/
	virtual ObiektBazowy* podziel( const Ilosc& ilosc );

	/**
	* Metoda ³¹czy obiekt bazowy z obiektem przekazanym przez parametr.
	* \param[in] obiektbazowy - Obiekt do po³¹czenia.
	* \warning Metoda nie zwalnia pamiêci przekazanego obiektu.
	* \return Kiedy obiekty zostan¹ po³¹czone, zwracana wartoœæ to true, w przeciwnym wypadku zwrócona wartoœæ to false.
	* \remark Metoda jest tranzakcyjna.
	*/
	virtual bool polacz( const ObiektBazowy& obiektbazowy );

	/**
	* Metoda sprawdzaj¹ca warunki po³¹czenia obiektów.
	* \param[in] obiektbazowy - Obiekt dla którego maj¹ byæ sprawdzone warunki po³¹czenia.
	* \return Kiedy obiekt mo¿e byæ po³¹czony, zwracana wartoœæ to true, w przeciwnym wypadku zwrócona wartoœæ to false.
	*/
	virtual bool czyMoznaPolaczyc( const ObiektBazowy& obiektbazowy ) const;

	/**
	* Metoda sprawdzaj¹ca czy mo¿na podzieliæ obiekt wed³ug podanej iloœci.
	* \param[in] ilosc - Iloœæ w zglêdem, której s¹ sprawdzane warunki podzia³u.
	* \return Je¿eli mo¿na podzieliæ, zwracana jest wartoœæ true, w przeciwnym wypadku zwrócona wartoœæ to false.
	*/
	virtual bool czyMoznaPodzielic( const Ilosc& ilosc ) const;

	/**
	* Metoda buduj¹ca obiekty o podanej iloœci.
	* \warning Metoda nie sprawdza czy obiekty moga byæ wybudowane.
	*/
	virtual void wybuduj(const Ilosc& ilosc);

	/**
	* \brief Metoda pobieraj¹ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca iloœæ obiektów.
	*/
	const Ilosc& pobierzIlosc() const;

	/**
	* \brief Metoda ustawiaj¹ca atrybut.
	*
	* Metoda ustawiaj¹ca atrybut obiektu.
	* \param[in] ilosc - Nowa wartoœæ iloœci obiektów.
	*/
	void ustawIlosc( const Ilosc& ilosc );

	/**
	* Metoda s³u¿y do zwrócenia klucza jednozancznie identyfikuj¹cego typ obiektu. 
	* Klucz sk³ada siê z identyfikatora obiektu i poziomu obiektu.
	* \return Klucz identyfikuj¹cy obiekt.
	*/
	Klucz ID() const;

	/**
	* Metoda pobieraj¹ca przetworzone warunki dostêpnoœci obiektu
	* \return Warunki po przetworzeniu przez klasy zmieniaj¹ce
	*/
	Wymagania::PrzetworzoneWymogi pobierzWarunkiRozbudowy()const;

	/**
	* Metoda pobieraj¹ca przetworzone koszty dostêpnoœci obiektu
	* \return Koszty po przetworzeniu przez klasy zmieniaj¹ce
	*/
	Wymagania::PrzetworzonaCena pobierzKosztyRozbudowy() const;

	/**
	* Metoda wyliczaj¹ca czas trwania rozbudowy jednego obiektu na kolejny poziom.
	* \return Czas trwania rozbudowy.
	*/
	Czas pobierzCzasRozbudowy( )const;

	/**
	* Metoda sprawdzaj¹ca wymagania obiektu.
	* \return Je¿eli obiekt spe³nia wymagania zwrócona jest wartoœæ true. Je¿eli nie spe³nia wymagañ zwrócona jest wartoœæ false.
	*/
	bool czyMoznaRozbudowac()const;

	/**
	* Metoda zwracaj¹ca referencej do obiektu opisuj¹cego.
	* \return referencja do obiektu opisuj¹cego.
	*/
	const ObiektBazowyInfo& getObiektBaseInfo()const;

	/**
	* \brief Metoda zapisuj¹ca.
	*
	* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
	* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
	* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( TiXmlElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj¹ca.
	*
	* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
	* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
	* \warning Metoda nie modyfikuje wêz³a.
	* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
	*/
	bool odczytaj( TiXmlElement* wezel ) override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;
};
