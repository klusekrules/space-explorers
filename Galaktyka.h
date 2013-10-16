#pragma once
#include "Bazowa.h"
#include "UkladSloneczny.h"
#include <unordered_map>

class Galaktyka :
	virtual public LoggerInterface,
	public Serializacja,
	public Bazowa
{
public:
	typedef unordered_map< Identyfikator, shared_ptr<UkladSloneczny>, IdTypeHash > UkladySloneczne;

	Galaktyka(const Identyfikator& identyfikator);

	virtual ~Galaktyka();

	shared_ptr<UkladSloneczny> pobierzUklad( const Identyfikator& identyfikator ) const;

	bool dodajUklad( shared_ptr<UkladSloneczny> uklad );

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

	UkladySloneczne uklady_;
};

