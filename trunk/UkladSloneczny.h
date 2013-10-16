#pragma once
#include <memory>
#include "SygnaturaPlanety.h"
#include "Ilosc.h"
#include "Dystans.h"
#include "Temperatura.h"
#include "Moc.h"
#include "Serializacja.h"

using namespace std;
class UkladSloneczny :
	virtual public LoggerInterface,
	public Serializacja,
	public Bazowa
{
public:
	typedef shared_ptr<SygnaturaPlanety> Sygnatura;
	typedef vector< Sygnatura > Planety;

	UkladSloneczny( const Identyfikator& id );
	virtual ~UkladSloneczny();
	
	void ustawSredniceGwiazdy(SPG::Dystans srednica);

	const Dystans& pobierzSredniceGwiazdy() const;

	void ustawSredniaTemperatureGwiazdy(SPG::Temperatura temperatura);

	const Temperatura& pobierzSredniaTemperatureGwiazdy() const;

	Moc pobierzMocGwiazdy() const;

	bool dodajPlanete( Sygnatura planeta );

	Sygnatura pobierzPlanete( int numer ) const ;

	int liczbaPlanet() const;

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
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override;

private:
	Dystans srednicaGwiazdy_;
	Temperatura sredniaTemperaturaGwiazdy_;
	
	Planety planety_;
};

