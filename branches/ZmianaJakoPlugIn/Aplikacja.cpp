#include "Aplikacja.h"
#include <time.h>
#include <sstream>
#include <iomanip>
#include "StatekInfo.h"
#include "plugin\plugin.h"

Aplikacja::Aplikacja()
	: pustyobiekBaseInfo( Info(Tekst(""),Tekst(""),IdType(0),Wymagania(nullptr)) , Poziom(0) ), pustyObiektBase( Ilosc(0), pustyobiekBaseInfo )
{
	//Wyswietlanie informacji o aplikacji
	LogApInfo();
	//Ladowanie potrzebnych bibliotek

	if(init()){
		Log::getInstance().info("Za³adowano pluginy");
	}else{
		Log::getInstance().warn("Nie za³adowano pluginow");
	}
	//_set_purecall_handler(myPurecallHandler);
	//TODO: zaimplementowanie logoowania podczas ka¿dej sytuacji wyj¹tkowej takiej jak wy¿ej
	/*
	// Rejestracja zmian w fabryce 
	ZmianaLiniowa::RejestrujZmianaLiniowa();
	ZmianaDekorator::RejestrujZmianaDekotor();
	ZmianaAgregacja::RejestrujZmianaAgregacja();	
	ZmianaPotegowa::RejestrujZmianaPotegowa();
	// -----------------------------------------*/

}

bool Aplikacja::WczytajDane( const string& sFile ){
	ticpp::Document opcje;
	ticpp::Document dane;
	//ticpp::Document komunikaty;
	try{
		/* TODO: £adowanie opcji przenieœæ do innej funkcji
 
		opcje.LoadFile(sFile);
		auto root = opcje.IterateChildren("SpaceGame",nullptr);
		auto b = root->IterateChildren("data",nullptr);
		if(b!=nullptr){
			string s = b->ToElement()->GetText();
			*/
		dane.LoadFile(sFile);
		auto root_data = dane.IterateChildren("SpaceGame",nullptr);
		if(root_data){
			if(!WczytajSurowce(root_data))
				return false;
			if(!WczytajStatki(root_data))
				return false;
		}
	}catch(ticpp::Exception& e){
		cout<< e.what();
		Log::getInstance().error("Nie uda³o siê otworzyæ pliku!");
		return false;
	}
	return true;
}

bool Aplikacja::WczytajSurowce(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		try{
			ptr = root->IterateChildren(CLASSNAME(SurowceInfo),ptr);
			if(ptr){
				SurowceInfo* t = new SurowceInfo(ptr);
				Log::getInstance().debug(*t);
				listaSurowcowInfo[t->ID()]=t;
			}
		}catch(OgolnyWyjatek& e){
			Log::getInstance().warn(e.generujKomunikat());
			Log::getInstance().debug(e);
			return false;
		}
	}while(ptr);
	return true;
}

bool Aplikacja::WczytajStatki(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		try{
			ptr = root->IterateChildren(CLASSNAME(StatekInfo),ptr);
			if(ptr){
				StatekInfo* t = new StatekInfo(ptr);
				Log::getInstance().debug(*t);
				listaStatkowInfo[t->ID()]=t;
			}
		}catch(OgolnyWyjatek& e){
			Log::getInstance().warn(e.generujKomunikat());
			Log::getInstance().debug(e);
			return false;
		}
	}while(ptr);
	return true;
}

Aplikacja::~Aplikacja()
{
	for(auto s : listaSurowcowInfo)
		if(s.second)
			delete s.second;
	for(auto s : listaStatkowInfo)
		if(s.second)
			delete s.second;
}
