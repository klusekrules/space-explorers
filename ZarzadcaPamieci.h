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

private:

	bool wczytajUkladSloneczny( const Identyfikator& identyfikator );
	bool zapiszUkladSloneczny( shared_ptr<UkladSloneczny> uklad ) const;

	GeneratorUkladow generator_;

	Galaktyki galaktyki_;
	UkladySloneczne ukladySloneczne_;
	Planety planety_;

};
