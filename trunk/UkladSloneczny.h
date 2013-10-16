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
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis() const override;

private:
	Dystans srednicaGwiazdy_;
	Temperatura sredniaTemperaturaGwiazdy_;
	
	Planety planety_;
};

