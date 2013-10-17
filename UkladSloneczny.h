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
class UkladSloneczny :
	virtual public LoggerInterface,
	public Serializacja,
	public Bazowa
{
	friend class ZarzadcaPamieci;
public:
	typedef shared_ptr<Planeta> Planeta;
	typedef unordered_map< Identyfikator, Planeta , IdTypeHash > Planety;

	UkladSloneczny( const Identyfikator& id, const Identyfikator& idGalaktyki );
	virtual ~UkladSloneczny();
	
	void ustawSredniceGwiazdy(SPG::Dystans srednica);

	const Dystans& pobierzSredniceGwiazdy() const;

	void ustawSredniaTemperatureGwiazdy(SPG::Temperatura temperatura);

	const Temperatura& pobierzSredniaTemperatureGwiazdy() const;

	Moc pobierzMocGwiazdy() const;

	bool dodajPlanete( UkladSloneczny::Planeta planeta );

	UkladSloneczny::Planeta pobierzPlanete( const Identyfikator& numer );

	int liczbaPlanet() const;

	const Identyfikator& pobierzIdGalaktyki() const;

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

	Identyfikator idGalaktyki_;

	Dystans srednicaGwiazdy_;
	Temperatura sredniaTemperaturaGwiazdy_;
	
	Planety planety_;
};

