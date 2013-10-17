#pragma once
#include "Identyfikator.h"
#include <memory>
#include <unordered_map>
#include "Galaktyka.h"
#include "GeneratorUkladow.h"
#include <vector>

using namespace std;

class ZarzadcaPamieci :
	public Serializacja
{
public:
	struct ObjPlaneta{
		Identyfikator idUkladu_;
		shared_ptr< Planeta > planeta_;
	};

	struct ObjUklad{
		Identyfikator idGalaktyki_;
		shared_ptr< UkladSloneczny > uklad_;
		vector< Identyfikator > planety_;
	};

	struct ObjGalakatyka{
		shared_ptr< Galaktyka > galaktyka_;
		vector< Identyfikator > uklady_;
	};

	typedef unordered_map< Identyfikator, ObjGalakatyka, IdTypeHash > Galaktyki;
	typedef unordered_map< Identyfikator, ObjUklad, IdTypeHash > UkladySloneczne;
	typedef unordered_map< Identyfikator, ObjPlaneta, IdTypeHash > Planety;

	ZarzadcaPamieci();

	shared_ptr< Planeta > pobierzPlanete( const Identyfikator& identyfikator  );

	int pobierzIloscGalaktyk() const;

	bool generujNowaGalaktyke();

	~ZarzadcaPamieci();
	
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

private:

	bool wczytajUkladSloneczny( const Identyfikator& identyfikator );
	bool zapiszUkladSloneczny( shared_ptr<UkladSloneczny> uklad ) const;

	GeneratorUkladow generator_;

	Galaktyki galaktyki_;
	UkladySloneczne ukladySloneczne_;
	Planety planety_;

};
