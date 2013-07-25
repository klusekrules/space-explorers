#pragma once
#include "Obiekt.h"
#include "OgolnyWyjatek.h"
#include "NiezgodnyTypSurowca.h"
#include "NiepoprawnaIloscObiektow.h"
#include "BladLaczeniaObiektow.h"
#include "PodstawoweParametry.h"

class SurowceInfo;
class Ladownia;

/**
* \brief Klasa reprezentuj¹ca surowiec.
*
* Klasa reprezentuj¹ca surowiec.
* \author Daniel Wojdak
* \version 1
* \date 25-07-2013
*/
class Surowce :
	public Obiekt,
	virtual public LoggerInterface,
	virtual public Serializacja
{
	friend class SurowceInfo;
public:

	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit Surowce( TiXmlElement* wezel  );

	/**
	* \brief Destruktor.
	*/
	virtual ~Surowce();

	/**
	* \brief Operator przypisania.
	*
	* \param[in] obiekt -  Obiekt jaki ma byæ przypisany do klasy.
	*/
	Surowce& operator=( const Surowce& obiekt ) throw ( NiezgodnyTypSurowca );

	/**
	* \brief Operator równoœci.
	*
	* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
	*/
	bool operator==( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca );

	/**
	* \brief Operator nierównoœci.
	*
	* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
	*/
	bool operator!=( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca );

	/**
	* \brief Operator s³abej wiêkszoœci.
	*
	* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
	*/
	bool operator>( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca );

	/**
	* \brief Operator s³abej mniejszoœci
	*
	* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
	*/
	bool operator<( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca );

	/**
	* \brief Operator wiêkszoœci.
	*
	* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
	*/
	bool operator>=( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca );

	/**
	* \brief Operator mniejszoœci.
	*
	* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
	*/
	bool operator<=( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca );

	/**
	* \brief Operator sumy.
	*
	* \param[in] obiekt - Obiekt dodany do aktualnej wartoœci.
	*/
	Surowce operator+( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca );

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] obiekt - Obiekt dodany do aktualnej wartoœci.
	*/
	Surowce& operator+=( const Surowce& obiekt ) throw ( NiezgodnyTypSurowca );

	/**
	* \brief Operator ró¿nicy.
	*
	* \param[in] obiekt - Obiekt odjêty od aktualnej wartoœci.
	*/
	Surowce operator-( const Surowce& obiekt ) const throw ( NiezgodnyTypSurowca );

	/**
	* \brief Operator przypisania i ró¿nicy.
	*
	* \param[in] obiekt - Obiekt odjêty od aktualnej wartoœci.
	*/
	Surowce& operator-=( const Surowce& obiekt ) throw ( NiezgodnyTypSurowca );

	/**
	* \brief Metoda dodaje obiekt surowca.
	*
	* \param[in] obiekt - obiekt dodany do aktualnego.
	* \return true je¿eli mo¿na dodaæ obiekt, false w przeciwnym wypadku.
	*/
	bool Dodaj( const Surowce& obiekt );

	/**
	* \brief Metoda odejmuj¹ca obiekt surowca.
	*
	* \param[in] obiekt - obiekt odjêty do aktualnego.
	* \return true je¿eli mo¿na odj¹æ obiekt, false w przeciwnym wypadku.
	*/
	bool Usun( const Surowce& obiekt );

	/**
	* \brief Metoda pobieraj¹ca obiekt opisowy.
	*
	* \return Obiekt opisowy surowca.
	*/
	const SurowceInfo& pobierzSurowceInfo() const;

	/**
	* \brief Metoda informuj¹ca czy obiekt jest typu przyrostowego.
	*
	* \return true je¿eli surowiec jest typu przyrostowego, false w przeciwnym wypadku.
	*/
	bool czyTypPrzyrostowy()const;

	/**
	* \brief Metoda wyliczaj¹ca czas budowy.
	*
	* Metoda wylicza czas budowy dla takiej obecnej iloœci surowców.
	* \return Czas budowy dla podanej iloœci u¿ytych surowców.
	*/
	Czas pobierzCzas()const;

	/**
	* Metoda kopiuj¹ca obiekt. 
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	Surowce* kopia() const override;

	/**
	* Metoda dziel¹ca klasê wzdlêdem iloœci podanej przez argument.
	* Zwrócony obiekt ma iloœæ równ¹ podan¹ przez parametr.
	* Obiekt bazowy ma iloœæ zmniejszon¹ o podan¹ przez parametr wartoœæ.
	* \param[in] ilosc - Iloœæ obiektów wzglêdem, którego jest podzielony obiekt.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Wskazanie na podzielony obiekt. Je¿eli nie mo¿na by³o podzieliæ obiektu, zostaje zwrócony nullptr.
	* \remark Metoda jest tranzakcyjna.
	*/
	Obiekt* podziel( const Ilosc& ilosc ) override;

	/**
	* \brief Metoda sparawdzaj¹ca teorertyczn¹ mo¿liwoœæ dodania do ³adowni.
	* 
	* Metoda sprawdza czy obiekt spe³nia wymagane za³o¿enia oby móg³by byæ rozpatrywany jako mo¿liwy dodania do ³adowni.
	* \param[in] ladownia - £adownia do której ma zostaæ dodany obiekt.
	* \return true je¿eli mo¿na dodaæ. False w przeciwnym wypadku.
	*/
	bool czyMoznaDodacDoLadownii( const Ladownia& ladownia ) const override;

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

private:
	/**
	* \brief Konstruktor.
	*
	* \param[in] ilosc - Iloœæ tworzonego obiektu.
	* \param[in] obiekt - Obiekt na bazie którego jest tworzona aktualna instancja.
	*/
	Surowce( const Ilosc& ilosc, const Surowce& obiekt );

	/**
	* \brief Konstruktor.
	*
	* \param[in] ilosc - Iloœæ tworzonego obiektu.
	* \param[in] poziom - Poziom tworoznego obiektu.
	* \param[in] identyfikatorPlanety - identyfikator planety na rzecz której jest tworzony obiekt.
	* \param[in] surowceInfo - Referencja do obiektu opisuj¹cego.
	*/
	Surowce( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const SurowceInfo& surowceInfo );

	/**
	* \brief Konstruktor.
	*
	* \param[in] ilosc - Iloœæ tworzonego obiektu.
	* \param[in] parametryPodstawowe - Podstawowe parametry.
	* \param[in] surowceInfo - Referencja do obiektu opisuj¹cego.
	*/
	Surowce( const Ilosc& ilosc, const PodstawoweParametry& parametryPodstawowe, const SurowceInfo& surowceInfo );

	const SurowceInfo& surowceInfo_; /// Referencja do obiektu opisowego.
};
