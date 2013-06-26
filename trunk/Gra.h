#pragma once
#include "SurowceInfo.h"
#include "StatekInfo.h"
#include "FuncTransf\ZmianaFabryka.h"
#include "Uzytkownik.h"
#include <unordered_map>

class Gra
{
	friend class Aplikacja;
private:
	Gra( Aplikacja& app );
	Gra( const Gra& g );
	Gra& operator=(const Gra& g);
	
	ZmianaFabryka &fabryka;

	ObiektBaseInfo pustyobiekBaseInfo;
	ObiektBase pustyObiektBase;

	unordered_map<IdType, shared_ptr<SurowceInfo>, IdTypeHash > listaSurowcowInfo;
	unordered_map<IdType, shared_ptr<StatekInfo>, IdTypeHash > listaStatkowInfo;
	
	bool WczytajSurowce(ticpp::Node* root);
	bool WczytajStatki(ticpp::Node* root);

	Aplikacja& aplikacja;
	shared_ptr<Uzytkownik> uzytkownik;

public:

	bool WczytajDane( const string& sFile );

	ZmianaFabryka& getZmianaFabryka();

	~Gra();

	const ObiektBase& getObiekt(IdType id)const;

	StatekInfo& getStatek(const IdType& id)const throw (NieznalezionoObiektu);
	SurowceInfo& getSurowce(const IdType& id)const throw (NieznalezionoObiektu);

};

