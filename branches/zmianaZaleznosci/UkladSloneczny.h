#pragma once
#include <memory>
#include "Planeta.h"
#include "Ilosc.h"
#include "Dystans.h"
#include "Temperatura.h"
#include "Moc.h"
#include "Serializacja.h"
#include <unordered_map>

using namespace std;

/**
* \brief Klasa reprezentuj�ca uk�ad s�oneczny
*
* Klasa reprezentuj�ca uk�ad s�oneczny.
* \author Daniel Wojdak
* \version 1
* \date 18-10-2013
*/
class UkladSloneczny :
	virtual public LoggerInterface,
	public Serializacja,
	public Bazowa
{
	friend class ZarzadcaPamieci;
public:
	typedef shared_ptr<Planeta> Planeta;
	typedef unordered_map< Identyfikator, Planeta , IdTypeHash > Planety; /// Typ listy planet

	/**
	* \brief Konstruktor
	*
	* \param[in] identyfikator - Numer identyfikuj�cy uk�ad s�oneczny
	* \param[in] identyfikatorGalaktyki - Numer identyfikuj�cy galaktyk� w kt�rej znajduje sie uk�ad s�oneczny.
	*/
	UkladSloneczny( const Identyfikator& identyfikator, const Identyfikator& identyfikatorGalaktyki );

	/**
	* \brief Destruktor
	*/
	virtual ~UkladSloneczny();
	
	/**
	* \brief Metoda ustawiaj�ca �rednic� gwiazdy.
	*
	* Metoda ustawia �rednic� gwiazdy na podan� w parametrze.
	* \param[in] srednica - nowa warto�c srednicy gwiazdy uk�adu s�onecznego.
	*/
	void ustawSredniceGwiazdy(SPG::Dystans srednica);

	/**
	* \brief Metoda zwraca �rednic� gwiazdy uk�adu.
	*
	* Metoda zwraca �rednic� gwiazdy uk�adu w mln km.
	* \return �rednica gwiady uk�adu.
	*/
	const Dystans& pobierzSredniceGwiazdy() const;

	/**
	* \brief Metoda ustawia �redni� temperatur� gwiazdy.
	*
	* Metoda ustawia �redni� temperatur� gwiazdy na podan� w parametrze.
	* \param[in] temperatura - nowa warto�� �redniej temperatury gwiazdy w kelwinach.
	*/
	void ustawSredniaTemperatureGwiazdy(SPG::Temperatura temperatura);

	/**
	* \brief Metoda zwraca �redni� temperatu� gwiazdy.
	*
	* Metoda zwraca �redni� temperatur� gwiazdy podan� w kelwinach.
	* \return �rednia temperatura gwiazdy.
	*/
	const Temperatura& pobierzSredniaTemperatureGwiazdy() const;

	/**
	* \brief Metoda zwraca moc gwiazdy.
	*
	* Metoda zwraca moc gwiazdy.
	* \return Moc gwiazdy.
	*/
	Moc pobierzMocGwiazdy() const;

	/**
	* \brief Metoda dodaje planet� do listy planet nale��cych do uk�adu.
	*
	* Metoda dodaj planet� do listy planet znajduj�cych sie w uk�adzie.
	* \param[in] planeta - Wska�nik na planet� dodawan� do listy.
	* \return true je�eli uda si� doda� planet�, false w przeciwnym wypadku.
	*/
	bool dodajPlanete( UkladSloneczny::Planeta planeta );

	/**
	* \brief Metoda zwracaj�ca planet� z uk�adu.
	*
	* Metoda zwraca planet� o podanym id, kt�ra znajduje si� na li�cie planet uk�adu.
	* \param[in] identyfikator - Numer identyfikuj�cy planet�.
	* \return Wska�nik na planet� lub nullptr je�eli planeta nie zostanie znaleziona.
	*/
	UkladSloneczny::Planeta pobierzPlanete( const Identyfikator& identyfikator );

	/**
	* \brief Metoda zwraca liczb� planet w uk�adzie.
	*
	* Metoda zwraca liczb� planet znajduj�cych w uk�adzie s�onecznym.
	* \return liczba planet.
	*/
	int liczbaPlanet() const;

	/**
	* \brief Metoda zwracaj�ca identyfikator galaktyki. 
	*
	* Metoda zwraca identyfikator galaktyki w kt�rej le�y uk�ad.
	* \return Identyfikator galaktyki.
	*/
	const Identyfikator& pobierzIdGalaktyki() const;

	/**
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
	* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( tinyxml2::XMLElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	* \warning Metoda nie modyfikuje w�z�a.
	* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
	*/
	bool odczytaj( tinyxml2::XMLElement* wezel ) override;

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	std::string napis() const override;

private:

	Identyfikator idGalaktyki_; /// Identyfikator galaktyki do kt�rej nale�y uk�ad s�oneczny

	Dystans srednicaGwiazdy_; /// �rednica gwiazdy
	Temperatura sredniaTemperaturaGwiazdy_; /// �rednia temperatura  gwiazdy
	
	Planety planety_; /// Lista planet przynale�nych  do uk�adu.
};
