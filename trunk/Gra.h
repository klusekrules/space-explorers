#pragma once
#include "SurowceInfo.h"
#include "StatekInfo.h"
#include "TechnologiaInfo.h"
#include "BudynekInfo.h"
#include "FuncTransf\ZmianaFabryka.h"
#include "Uzytkownik.h"
#include <unordered_map>
#include "Licznik.h"

class Gra
{
	friend class Aplikacja;
private:
	Gra( Aplikacja& app );
	Gra( const Gra& g );
	Gra& operator=(const Gra& g);
	
	ZmianaFabryka &fabryka;
	
	unordered_map<IdType, shared_ptr<SurowceInfo>, IdTypeHash > listaSurowcowInfo;
	unordered_map<IdType, shared_ptr<StatekInfo>, IdTypeHash > listaStatkowInfo;
	unordered_map<IdType, shared_ptr<TechnologiaInfo>, IdTypeHash > listaTechnologiInfo;
	unordered_map<IdType, shared_ptr<BudynekInfo>, IdTypeHash > listaBudynkowInfo;

	Licznik idPlanety;
	Uzytkownik::ListaPlanet wolnePlanety;

	bool WczytajSurowce(ticpp::Node* root);
	bool WczytajStatki(ticpp::Node* root);
	bool WczytajTechnologie(ticpp::Node* root);
	bool WczytajBudynki(ticpp::Node* root);

	Aplikacja& aplikacja;
	shared_ptr<Uzytkownik> uzytkownik;

public:

	bool WczytajDane( const string& sFile );

	Uzytkownik& getUzytkownik() const throw (NieznalezionoObiektu);

	IdType generujPlanete();

	bool przeniesPlaneteDoUzytkownika( const IdType& );

	bool wybudujNaPlanecie( Planeta& , const IdType&, const Ilosc& )const;

	bool Logowanie(const string& nazwa, const string& hash);

	ZmianaFabryka& getZmianaFabryka();

	~Gra();
	
	StatekInfo& getStatek(const IdType& id)const throw (NieznalezionoObiektu);
	SurowceInfo& getSurowce(const IdType& id)const throw (NieznalezionoObiektu);
	TechnologiaInfo& getTechnologia(const IdType& id)const throw (NieznalezionoObiektu);
	BudynekInfo& getBudynek(const IdType& id)const throw (NieznalezionoObiektu);

};
