#pragma once
#include "ObiektInfo.h"
#include "Surowce.h"
#include "Bool.h"

/**
* \brief Klasa opisowa surowca.
*
* Klasa opisowa surowca.
* \author Daniel Wojdak
* \version 1
* \date 25-07-2013
*/
class SurowceInfo :
	public ObiektInfo,
	virtual public LoggerInterface
{
public:

	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit SurowceInfo( TiXmlElement* wezel );

	/**
	* \brief Destruktor.
	*/
	virtual ~SurowceInfo();

	/**
	* \brief Metoda informuj¹ca czy obiekt jest typu przyrostowego.
	*
	* \return true je¿eli surowiec jest typu przyrostowego, false w przeciwnym wypadku.
	*/
	bool czyTypPrzyrostowy()const;

	/**
	* \brief Metoda wyliczaj¹ca czas budowy.
	*
	* Metoda wylicza czas na podstawie iloœci surowca i zmiany.
	* \param[in] ilosc - Iloœæ surowców na bazie których bêdzie wyliczany czas.
	* \param[in] parametryPodstawowe - Podstawowe parametry potrzebne do wyliczenia czasu.
	* \return Czas budowy dla podanej iloœci u¿ytych surowców.
	*/
	Czas pobierzCzas( const Ilosc& ilosc, const PodstawoweParametry& parametryPodstawowe )const;

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu dla podanej planety.
	* \param[in] ilosc - nieu¿ywana
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Metoda zwraca wskaŸnika na obiekt.
	*/
	Surowce* tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const override;

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu dla podanej planety.
	* \param[in] ilosc - nieu¿ywana
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Metoda zwraca wskaŸnika na obiekt.
	*/
	Surowce* tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety, const Poziom& poziom ) const override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;
private:

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu na planecie.
	*
	*  Metoda tworzy egzemplarz obiektu na planecie. U¿ywana jest podczas wywo³ywania metody wybuduj w klasie Planeta.
	* \param[in] gra - Referencja do obiektu gry.
	* \param[in] planeta - Referencja do obiektu planety
	* \param[in] ilosc - Iloœæ tworzonych obiektów.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return Metoda zwraca true je¿eli tworzenie zakoñczy siê sukcesem. Zwraca false w przeciwnym wypadku.
	*/
	bool tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc, const Poziom& poziom ) const override;

	Bool przyrostowy_; /// Informacja czy podany tym jest przyrostowy

	shared_ptr<ZmianaInterfejs> zmianaCzasu_; /// WskaŸnik do zmiany wyliczaj¹cej czas budowy.
};
