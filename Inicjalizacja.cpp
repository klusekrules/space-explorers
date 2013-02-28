
#include "Biblioteki.h"
/*

Inicjalizacja::Inicjalizacja( ){
}

Inicjalizacja::~Inicjalizacja()
{
	for(auto iter = surowceInfo.begin();iter!=surowceInfo.end();iter++)
		delete *iter;
	for(auto iter = statekInfo.begin();iter!=statekInfo.end();iter++)
		delete *iter;
}

Inicjalizacja* Inicjalizacja::getSingleton(){
	static Inicjalizacja singleton;
	return &singleton;
}

StatekInfo* Inicjalizacja::getStatekInfo( int numer ){
	auto iter = statekInfo.begin();
	for(; iter!= statekInfo.end() && numer>0; iter++, --numer);
	if(iter == statekInfo.end())
		return NULL;
	return *iter;
}

SurowceInfo* Inicjalizacja::getSurowceInfo( int numer ){
	auto iter = surowceInfo.begin();
	for(; iter!= surowceInfo.end() && numer>0; iter++, --numer);
	if(iter == surowceInfo.end())
		return NULL;
	return *iter;
}

bool Inicjalizacja::addSurowceInfo( SurowceInfo* obj ){
	for(auto iter = surowceInfo.begin(); iter!= surowceInfo.end(); iter++){
		if( (*iter)->ID() == obj->ID() )
			return false;
	}
	surowceInfo.push_back(obj);
	return true;
}

bool Inicjalizacja::addStatekInfo( StatekInfo* obj ){
	for(auto iter = statekInfo.begin(); iter!= statekInfo.end(); iter++){
		if( (*iter)->ID() == obj->ID() )
			return false;
	}
	statekInfo.push_back(obj);
	return true;
}

list<StatekInfo*> Inicjalizacja::getStatekInfo( ){
	return statekInfo;
}

list<SurowceInfo*> Inicjalizacja::getSurowceInfo( ){
	return surowceInfo;
}

string Inicjalizacja::communique( const string& id ){
	return getSingleton()->getKomunikat(id);
}

pair<string,string> Inicjalizacja::message( const string& id ){
	return getSingleton()->getWiadomosc(id);
}

bool Inicjalizacja::addKomunikat( const pair< string , string > & kom ){
	auto iter = Komunikaty.find(kom.first);
	if(iter==Komunikaty.end()){
		Komunikaty.insert(kom);
		return true;
	}
	return false;
}

bool Inicjalizacja::addWiadomosc( const pair< string , pair< string , string > >& wiad ){
	auto iter = Wiadomosci.find(wiad.first);
	if(iter==Wiadomosci.end()){
		Wiadomosci.insert(wiad);
		return true;
	}
	return false;
}	

string Inicjalizacja::getKomunikat( const string& klucz ) const{
	for(auto iter = Komunikaty.begin();iter!=Komunikaty.end();++iter){
		if(iter->first == klucz)
			return iter->second;
	}
	return string();
}

pair< string , string > Inicjalizacja::getWiadomosc( const string& klucz ) const{
	for(auto iter = Wiadomosci.begin();iter!=Wiadomosci.end();++iter){
		if(iter->first == klucz)
			return iter->second;
	}
	return make_pair(string(),string());
}

	
void Inicjalizacja::zaladuj( const string& plik ){
	
	ticpp::Document opcje;
	ticpp::Document dane;
	ticpp::Document komunikaty;
	
	try{
		opcje.LoadFile(plik);

		ticpp::Iterator<ticpp::Element> messages = find("messages" , opcje.FirstChildElement());
		string message;
		messages->GetText(&message);
		komunikaty.LoadFile(message);
		
		/* £adowanie Wiadomosci 
		ZaladujWiadomosci(komunikaty);

	}catch(ticpp::Exception& ex){
		throw WyjatekParseraXML("Blad wczytywania pliku.Oryginalna wiadomosc:",ex);
	}

	try{

		ticpp::Iterator<ticpp::Element> lokalizacja = find("locale" , opcje.FirstChildElement());
		ticpp::Iterator<ticpp::Element> plikdanych = find("data" , opcje.FirstChildElement());
		

		string value;
		lokalizacja->GetText(&value);
		locale pl( value );
		locale::global(pl);

		plikdanych->GetText(&value);
		
		try{
			dane.LoadFile(value);
		}catch(ticpp::Exception& ex){
			throw WyjatekParseraXML("Blad wczytywania pliku.Oryginalna wiadomosc:",ex);
		}
				
		/* £adowanie Komunikatów 
		ZaladujKomunikaty(komunikaty);

		/*G³owna Maska
		ticpp::Iterator<ticpp::Element> SpaceGame ;
		SpaceGame = SpaceGame.begin(dane.To<const ticpp::Node>());
		mapaMask.insert(ZaladujMaske( SpaceGame ));
		
		/* £adowanie surowców 
		zaladujSurowceInfo( dane );

		/* £adowanie statków 
		zaladujStatekInfo( dane );


	}catch(invalid_argument& ex){
		throw WyjatekSTL(ex);
	}catch(out_of_range& ex){
		throw WyjatekSTL(ex);
	}catch(ticpp::Exception& ex){
		throw WyjatekParseraXML(ex);
    }catch(OgolnyWyjatek& ex ){
		throw ex;
	}catch(std::exception& ex){
		throw OgolnyWyjatek(OgolnyWyjatek::idOgolnyWyjatek,"Wykryto nieznany wyjatek.",ex.what());
	}catch(...){
		throw OgolnyWyjatek(0,"Fatal Error","Undefined exception");
	}

}

void Inicjalizacja::ZaladujKomunikaty( const ticpp::Document& dokument ){
	ticpp::Iterator<ticpp::Element> zbior = find("ZbiorKomunikatow" , dokument.FirstChildElement());
	ticpp::Iterator<ticpp::Element> child;
	for( child = child.begin( &(*zbior) ) ; child != child.end() ; ++child ){
		addKomunikat(ZaladujKomunikat(child));
	}
}

void Inicjalizacja::ZaladujWiadomosci( const ticpp::Document& dokument ){
	ticpp::Iterator<ticpp::Element> zbior = find("ZbiorWiadomosci" , dokument.FirstChildElement());
	ticpp::Iterator<ticpp::Element> child;
	for( child = child.begin( &(*zbior) ) ; child != child.end() ; ++child ){
		addWiadomosc(ZaladujWiadomosc(child));
	}
}

pair< string, string > Inicjalizacja::ZaladujKomunikat( const ticpp::Iterator<ticpp::Element>& element ) const{
	string tresc;
	element->GetText(&tresc);
	return make_pair< string , string >(element->GetAttribute("id"), string(tresc));
}

pair< string, pair< string, string > > Inicjalizacja::ZaladujWiadomosc( const ticpp::Iterator<ticpp::Element>& element ) const{
	string tresc;
	element->GetText(&tresc);
	return make_pair( element->GetAttribute("id") , make_pair< string , string > ( element->GetAttribute("tytul") , string(tresc) ) );
}

void Inicjalizacja::zaladujSurowceInfo( const ticpp::Document & doc ){
	/* £adowanie surowców 
	ticpp::Iterator<ticpp::Element> iSurowce = find("Surowce" , doc.FirstChildElement());
	mapaMask.insert(ZaladujMaske( iSurowce ));
	ticpp::Iterator<ticpp::Element> iterSurowce;
	for( iterSurowce = iterSurowce.begin( &(*iSurowce) ); iterSurowce != iterSurowce.end(); iterSurowce++){
		if( !czyNazwane( "Klasa" , *iterSurowce ) )
			continue;

		mapaMask.insert(ZaladujMaske( iterSurowce ));
		ticpp::Iterator<ticpp::Element> child;			
		for(child = child.begin( &(*iterSurowce) ); child != child.end(); child++){
			if( !czyNazwane( "Surowiec" , *child ) )
				continue;
			SurowceInfo* tmp = ZaladujObiektSurowceInfo(child);
			if( !addSurowceInfo(tmp) ){
				delete tmp;
			}
		}
	}
}

void Inicjalizacja::zaladujStatekInfo( const ticpp::Document & doc ){
	/* £adowanie statków 
	ticpp::Iterator<ticpp::Element> iStatki = find("Statki" , doc.FirstChildElement());
	mapaMask.insert(ZaladujMaske( iStatki ));
	ticpp::Iterator<ticpp::Element> iterStatek;
	for( iterStatek = iterStatek.begin( &(*iStatki) ); iterStatek != iterStatek.end(); iterStatek++){
		if( !czyNazwane( "Statek" , *iterStatek ) )
			continue;
		StatekInfo* tmp = ZaladujObiektStatekInfo(iterStatek);
		if( !addStatekInfo(tmp) ){
			delete tmp;
		}
	}
}

pair< string ,  SPG::IdType > Inicjalizacja::ZaladujMaske( const ticpp::Iterator<ticpp::Element>& child) const{
	
	auto maska = pobierzAtrybut( "maska" , *child );
	try{
		return make_pair< string ,  SPG::IdType >( pobierzAtrybut( "nazwa" , *child ) , stoul( maska , NULL , 16 ) );
	}catch(invalid_argument& ex){
		throw WyjatekSTL(string("Maska jest w niepoprawnym formacie. Wartosc maski: ")+ maska + ". Oryginalny komunikat:",ex);
	}catch(out_of_range& ex){
		throw WyjatekSTL(string("Wartosc maski wyszla poza dozwolony zakres. Wartosc maski: ")+ maska + ". Oryginalny komunikat:",ex);
	}	
}

SurowceInfo* Inicjalizacja::ZaladujObiektSurowceInfo( const ticpp::Iterator<ticpp::Element>& child ) const{
	Obiekt* obiekt = ZaladujObiekt(child);
	Info* info;
	try{
		info = ZaladujInfo(child);
	}catch(...){
		delete obiekt;
		throw;
	}
	SurowceInfo* temp;
	try{
		auto para = ZaladujMaske(child);
		SPG::IdType id = para.second;
		id |= pobierzMaske( "Domyslny" ) | pobierzMaske( "Surowce" ) 
			| pobierzMaske( pobierzAtrybut( "nazwa", *(child->Parent()->ToElement()) ) ); 
		
		temp = new SurowceInfo( *info , *obiekt);
		temp->setId(id);

	}catch(ticpp::Exception& ex){
		delete obiekt;
		delete info;
		throw WyjatekParseraXML("Brak wartosci elementu.Oryginalna wiadomosc:",ex);
	}
	delete obiekt;
	delete info;
	return temp;
}

StatekInfo* Inicjalizacja::ZaladujObiektStatekInfo( const ticpp::Iterator<ticpp::Element>& child ) const{
	Obiekt* obiekt = ZaladujObiekt(child);
	Info* info;
	Cena* cena;
	Ladownia* ladownia;
	try{
		info = ZaladujInfo(find("Info",&(*child)));
	}catch(...){
		delete obiekt;
		throw;
	}
	try{
		cena = ZaladujCena(find("Cena",&(*child)));
	}catch(...){
		delete obiekt;
		delete info;
		throw;
	}
	try{
		ladownia = new Ladownia( stold( pobierzAtrybut( "pojemnosc", *child ) ) );
	}catch(...){
		delete obiekt;
		delete cena;
		delete info;
		throw;
	}
	StatekInfo* temp;
	try{
		SPG::IdType id = pobierzMaske( "Domyslny" ) | pobierzMaske( "Statki" ) | stoul( pobierzAtrybut( "maska", *child ) , NULL , 16 );
		temp = new StatekInfo( *obiekt , *cena , *info , *ladownia ,
			static_cast<SPG::RodzajNapedu>(stoul( pobierzAtrybut( "rodzajNapedu", *child ) )),
			stold( pobierzAtrybut( "mocSilnika", *child ) ),
			stold( pobierzAtrybut( "zuzyciePaliwa", *child ) ),
			stold( pobierzAtrybut( "atak", *child ) ),
			stold( pobierzAtrybut( "pancerz", *child ) ),
			stold( pobierzAtrybut( "tarcza", *child ) ));
		temp->setId(id);

	}catch(ticpp::Exception& ex){
		delete obiekt;
		delete info;
		delete cena;
		delete ladownia;
		throw WyjatekParseraXML("Brak wartosci elementu.Oryginalna wiadomosc:",ex);
	}
	delete obiekt;
	delete info;
	delete cena;
	delete ladownia;
	return temp;
}

Cena* Inicjalizacja::ZaladujCena( const ticpp::Iterator<ticpp::Element>& element ) const{
	ticpp::Iterator<ticpp::Element> child;
	SPG::ZbiornikObiektow zbiornik;
	try{
		for(child = child.begin( &(*element) ); child != child.end(); child++){
			if(!czyNazwane( "Surowiec" , *child))
				continue;
			auto klucz = make_pair< SPG::IdType , SPG::Poziom >( stoul(pobierzAtrybut( "id" , *child),NULL,16) , stoul(pobierzAtrybut( "poziom" , *child)) );
			auto iter = surowceInfo.begin();
			for(;iter!=surowceInfo.end();iter++)
			{
				if(klucz== (*iter)->ID())
					break;
			}
			if(iter==surowceInfo.end())
				throw OgolnyWyjatek(OgolnyWyjatek::idOgolnyWyjatek,"Brak opisu surowca.","Surowiec podany jako element ceny nie ma opisu!");
			zbiornik.insert( make_pair<SPG::Klucz,Obiekt*>( SPG::Klucz(klucz) , (*iter)->TworzEgzemplarz( stoul(pobierzAtrybut( "ilosc" , *child)) ) ));
		}
	}catch(...){
		for( auto iter = zbiornik.begin(); iter!=zbiornik.end(); iter++)
			delete iter->second;
	}

	Cena *cena = new Cena();
	cena->setKoszty(zbiornik);
	return cena;
}

Obiekt* Inicjalizacja::ZaladujObiekt( const ticpp::Iterator<ticpp::Element>& child ) const{
	try{
		return new Obiekt( idDomyslny, stoul(pobierzAtrybut( "poziom" , *child )) 
						, stold(pobierzAtrybut( "objetosc" , *child )) 
						, stold(pobierzAtrybut( "masa" , *child )) 
						, stold(pobierzAtrybut( "powierzchnia" , *child )) );
	}catch(invalid_argument& ex){
		throw WyjatekSTL("Atrybut objetosc, masa, lub powierzchnia maja niedozwolony format. Oryginalny komunikat:",ex);
	}catch(out_of_range& ex){
		throw WyjatekSTL("Atrybut objetosc, masa, lub powierzchnia wyszedl poza dozwolony zakres. Oryginalny komunikat:",ex);
	}
}

Info* Inicjalizacja::ZaladujInfo( const ticpp::Iterator<ticpp::Element>& child ) const{
	try{
		return new Info( pobierzAtrybut( "nazwa" , *child ) , child->GetText() );
	}catch(ticpp::Exception& ex){
		throw WyjatekParseraXML("Brak opisu! Oryginalny komunikat:",ex);
	}
}

ticpp::Iterator<ticpp::Element> Inicjalizacja::find( const string& nazwa , ticpp::Element *element , bool wglab ) const{	
	ticpp::Iterator<ticpp::Element> child;
	if(element == NULL)
		return child.end();

	for(child = child.begin(element); child != child.end(); child++){
		if(czyNazwane( nazwa , *child))
			return child;
		if(wglab){
			auto iter = find(nazwa,&(*child),true);
			if(iter!=child.end())
				return iter;
		}
	}
	return child.end();
}

string Inicjalizacja::toString() const{
	Logger str("Inicjalizacja");
	str.dodajListaC("Lista Surowcow",this->surowceInfo);
	str.dodajListaC("Lista Statkow",this->statekInfo);
	str.dodajMapaT("Mapa mask",this->mapaMask);
	str.dodajMapaT("Lista Komunikatów",this->Komunikaty);
	str.dodajMapaParVT("Lista Wiadomosci",this->Wiadomosci);
	return str.toString();
}

bool Inicjalizacja::czyNazwane( const string& nazwa , const ticpp::Element& element ){
	string strName;
	element.GetValue(&strName);
	return strName == nazwa;
}

string Inicjalizacja::pobierzAtrybut( const string& nazwa , const ticpp::Element& element ){
	if( !element.HasAttribute(nazwa) )
		throw BrakAtrybutuXML(nazwa);
	return element.GetAttribute(nazwa);
}

SPG::IdType Inicjalizacja::pobierzMaske( const string& nazwa ) const{
	auto iter = mapaMask.find(nazwa);
	if(iter == mapaMask.end())
		throw BrakMaski(nazwa);
	return iter->second;
}*/