#pragma once
#include "Main.h"
#include "ObiektBase.h"
#include "ObiektBaseInfo.h"
#include <Windows.h>
#include "Info.h"
#include "Biblioteki.h"
#include "SurowceInfo.h"
#include "StatekInfo.h"

/**
* Klasa reprezentuj¹ca instancjê aplikacji.
*/
class Aplikacja
{
	friend class Testy;
private:
	void LogApInfo();

protected:

	Aplikacja();
	
	ObiektBaseInfo pustyobiekBaseInfo;
	ObiektBase pustyObiektBase;

	hash_map<Klucz, SurowceInfo* > listaSurowcowInfo;
	hash_map<Klucz, StatekInfo* > listaStatkowInfo;

	bool WczytajSurowce(ticpp::Node* root);
	bool WczytajStatki(ticpp::Node* root);

public:

	bool WczytajDane( const string& sFile );

	static Aplikacja& getInstance(){
		static Aplikacja app;
		return app;
	}
	
	~Aplikacja();

	const ObiektBase& getObiekt(IdType id)const{
		return pustyObiektBase;
	}

	StatekInfo& getStatek(const Klucz& id)const throw (NieznalezionoObiektu) {
		auto iter = listaStatkowInfo.find(id);
		if(iter==listaStatkowInfo.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
		return *(iter->second);
	}

	SurowceInfo& getSurowce(const Klucz& id)const throw (NieznalezionoObiektu) {
	auto iter = listaSurowcowInfo.find(id);
	if(iter==listaSurowcowInfo.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
	return *(iter->second);
	}

	const ObiektBase& getObiekt(Klucz k) const{
		return pustyObiektBase;
	}
};

