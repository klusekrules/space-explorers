#include "Gra.h"
#include "Aplikacja.h"

Gra::Gra(Aplikacja& app)
	: aplikacja(app), fabryka(ZmianaFabryka::pobierzInstancje()), uzytkownik(new Uzytkownik()),
	pustyobiekBaseInfo( Info(Tekst(""),Tekst(""),IdType(0),Wymagania(nullptr)) , Poziom(0) ), 
	pustyObiektBase( Ilosc(0), pustyobiekBaseInfo )
{
}

Gra::Gra(const Gra& g)
	: aplikacja(g.aplikacja), fabryka(ZmianaFabryka::pobierzInstancje()),uzytkownik(g.uzytkownik),
	pustyobiekBaseInfo( Info(Tekst(""),Tekst(""),IdType(0),Wymagania(nullptr)) , Poziom(0) ), 
	pustyObiektBase( Ilosc(0), pustyobiekBaseInfo )
{
}

Gra& Gra::operator=(const Gra& g){
	return *this;
}

ZmianaFabryka& Gra::getZmianaFabryka(){
	return fabryka;
}

Gra::~Gra()
{
}

StatekInfo& Gra::getStatek(const Klucz& id)const throw (NieznalezionoObiektu) {
	auto iter = listaStatkowInfo.find(id);
	if(iter==listaStatkowInfo.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
	return *(iter->second);
}

SurowceInfo& Gra::getSurowce(const Klucz& id)const throw (NieznalezionoObiektu) {
	auto iter = listaSurowcowInfo.find(id);
	if(iter==listaSurowcowInfo.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
	return *(iter->second);
}

const ObiektBase& Gra::getObiekt(IdType id)const{
	return pustyObiektBase;
}
	
const ObiektBase& Gra::getObiekt(Klucz k) const{
	return pustyObiektBase;
}

bool Gra::WczytajDane( const string& sFile ){
	ticpp::Document dane;
	try{
		dane.LoadFile( sFile );
		auto root_data = dane.IterateChildren("SpaceGame",nullptr);
		if(root_data){
			if(!WczytajSurowce(root_data))
				return false;
			if(!WczytajStatki(root_data))
				return false;
		}
	}catch(ticpp::Exception& e){
		cout<< e.what();
		aplikacja.getLog().error("Nie uda³o siê otworzyæ pliku!");
		return false;
	}
	return true;
}

bool Gra::WczytajSurowce(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		try{
			ptr = root->IterateChildren(CLASSNAME(SurowceInfo),ptr);
			if(ptr){
				shared_ptr<SurowceInfo> t(new SurowceInfo(ptr));
				aplikacja.getLog().debug(*t);
				listaSurowcowInfo[t->ID()]=t;
			}
		}catch(OgolnyWyjatek& e){
			aplikacja.getLog().warn(e.generujKomunikat());
			aplikacja.getLog().debug(e);
			return false;
		}
	}while(ptr);
	return true;
}

bool Gra::WczytajStatki(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		try{
			ptr = root->IterateChildren(CLASSNAME(StatekInfo),ptr);
			if(ptr){
				shared_ptr<StatekInfo> t(new StatekInfo(ptr));
				aplikacja.getLog().debug(*t);
				listaStatkowInfo[t->ID()]=t;
			}
		}catch(OgolnyWyjatek& e){
			aplikacja.getLog().warn(e.generujKomunikat());
			aplikacja.getLog().debug(e);
			return false;
		}
	}while(ptr);
	return true;
}
