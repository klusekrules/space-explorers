#pragma once
#include "ObiektBazowy.h"

class TechnologiaInfo;

/**
* \brief Klasa reprezentuj¹ca technologie.
*
* Klasa reprezentuj¹ca technologie.
* \author Daniel Wojdak
* \version 1
* \date 25-07-2013
*/
class Technologia :
	public ObiektBazowy,
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:

	/**
	* \brief Konstruktor.
	*
	* \param[in] poziom - Poziom tworzonych obiektów.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] technologiaInfo - Referencja do obiektu opisuj¹cego.
	*/
	Technologia( const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const TechnologiaInfo& technologiaInfo );

	/**
	* \brief Konstruktor.
	*
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
	* \param[in] technologiaInfo - Referencja do obiektu opisuj¹cego.
	*/
	Technologia( const PodstawoweParametry& podstawoweParametry, const TechnologiaInfo& technologiaInfo);

	/**
	* \brief Destruktor.
	*/
	virtual ~Technologia();

	/**
	* Metoda kopiuj¹ca obiekt. 
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	Technologia* kopia() const override;

	/**
	* Metoda dziel¹ca obiekt, nie jest wspierana dla budynku, zawsze zwraca nullptr.
	* \param[in] ilosc - Nieu¿ywany.
	* \return  Metoda zawsze zwraca nullptr.
	*/
	Technologia* podziel( const Ilosc& ilosc) override;

	/**
	* Metoda ³¹czy obiekt bazowy z obiektem przekazanym przez parametr.
	* \param[in] obiektbazowy - Nieu¿ywany.
	* \return Zawsze zwraca wartoœæ false.
	*/
	bool polacz( const ObiektBazowy& obiektBase) override;
	
	/**
	* Metoda sprawdzaj¹ca warunki po³¹czenia obiektów.
	* \param[in] obiektbazowy - Nieu¿ywany.
	* \return Zawsze zwraca wartoœæ false.
	*/
	bool czyMoznaPolaczyc( const ObiektBazowy& obiektbazowy ) const override;

	/**
	* Metoda sprawdzaj¹ca czy mo¿na podzieliæ obiekt wed³ug podanej iloœci.
	* \param[in] ilosc - Nieu¿ywany.
	* \return Zawsze zwraca wartoœæ false.
	*/
	bool czyMoznaPodzielic( const Ilosc& ilosc ) const override;

	/**
	* Metoda buduj¹ca obiekty o podanej iloœci.
	* \param[in] ilosc - nieu¿ywany
	* \warning Metoda nie sprawdza czy obiekty moga byæ wybudowane.
	*/
	void wybuduj(const Ilosc& ilosc) override;

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
	string napis()const override;
	
protected:
	const TechnologiaInfo& technologiaInfo_; /// Referencja do obiektu opisuj¹cego.
};
