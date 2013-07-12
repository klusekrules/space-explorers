#pragma once
#include "SurowceInfo.h"
#include "StatekInfo.h"
#include "TechnologiaInfo.h"
#include "BudynekInfo.h"
#include "FuncTransf\ZmianaFabryka.h"
#include "Uzytkownik.h"
#include <unordered_map>
#include "Licznik.h"

class Gra :
	virtual public Serializacja
{
	friend class Aplikacja;
private:
	Gra( Aplikacja& app );
	Gra( const Gra& g );
	Gra& operator=(const Gra& g);
	
	ZmianaFabryka &fabryka;
	
	unordered_map<Identyfikator, shared_ptr<SurowceInfo>, IdTypeHash > listaSurowcowInfo;
	unordered_map<Identyfikator, shared_ptr<StatekInfo>, IdTypeHash > listaStatkowInfo;
	unordered_map<Identyfikator, shared_ptr<TechnologiaInfo>, IdTypeHash > listaTechnologiInfo;
	unordered_map<Identyfikator, shared_ptr<BudynekInfo>, IdTypeHash > listaBudynkowInfo;
	unordered_map<Identyfikator, shared_ptr<ObiektInfo>, IdTypeHash > listaObiektowInfo;
	unordered_map<Identyfikator, shared_ptr<ObiektBaseInfo>, IdTypeHash > listaObiektowBaseInfo;

	Licznik idPlanety;
	Uzytkownik::ListaPlanet wolnePlanety;

	bool WczytajSurowce(TiXmlElement* root);
	bool WczytajStatki(TiXmlElement* root);
	bool WczytajTechnologie(TiXmlElement* root);
	bool WczytajBudynki(TiXmlElement* root);

	Aplikacja& aplikacja;
	shared_ptr<Uzytkownik> uzytkownik;

public:

	bool WczytajDane( const string& sFile );

	Uzytkownik& getUzytkownik() const throw (NieznalezionoObiektu);

	Identyfikator generujPlanete();

	bool przeniesPlaneteDoUzytkownika( const Identyfikator& );

	bool wybudujNaPlanecie( Planeta& , const Identyfikator&, const Ilosc& )const;
	bool wybudujNaPlanecie( Planeta& , const BudynekInfo&, const Ilosc& )const;
	bool wybudujNaPlanecie( Planeta& , const TechnologiaInfo&, const Ilosc& )const;
	bool wybudujNaPlanecie( Planeta& , const StatekInfo&, const Ilosc& )const;
	bool wybudujNaPlanecie( Planeta& , const SurowceInfo&, const Ilosc& )const;

	bool Logowanie(const string& nazwa, const string& hash);

	ZmianaFabryka& getZmianaFabryka();

	bool zapisz( TiXmlElement* e ) const override;

	bool odczytaj( TiXmlElement* e ) override;

	~Gra();
	
	StatekInfo& getStatek(const Identyfikator& id)const throw (NieznalezionoObiektu);
	SurowceInfo& getSurowce(const Identyfikator& id)const throw (NieznalezionoObiektu);
	TechnologiaInfo& getTechnologia(const Identyfikator& id)const throw (NieznalezionoObiektu);
	BudynekInfo& getBudynek(const Identyfikator& id)const throw (NieznalezionoObiektu);
	ObiektInfo& getObiekt(const Identyfikator& id)const throw (NieznalezionoObiektu);
};

