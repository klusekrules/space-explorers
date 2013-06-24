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

	unordered_map<Klucz, shared_ptr<SurowceInfo>, KluczHash > listaSurowcowInfo;
	unordered_map<Klucz, shared_ptr<StatekInfo>, KluczHash > listaStatkowInfo;
	
	bool WczytajSurowce(ticpp::Node* root);
	bool WczytajStatki(ticpp::Node* root);

	Aplikacja& aplikacja;
	shared_ptr<Uzytkownik> uzytkownik;

public:

	bool WczytajDane( const string& sFile );

	ZmianaFabryka& getZmianaFabryka();

	~Gra();

	const ObiektBase& getObiekt(IdType id)const;	
	const ObiektBase& getObiekt(Klucz k) const;

	StatekInfo& getStatek(const Klucz& id)const throw (NieznalezionoObiektu);
	SurowceInfo& getSurowce(const Klucz& id)const throw (NieznalezionoObiektu);

};

