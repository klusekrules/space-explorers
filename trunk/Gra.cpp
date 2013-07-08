#include "Gra.h"
#include "Aplikacja.h"

Gra::Gra(Aplikacja& app)
	: aplikacja(app), fabryka(ZmianaFabryka::pobierzInstancje()), uzytkownik(new Uzytkownik())
{
	idPlanety.ustawWartosc(Ilosc(1));
}

Gra::Gra(const Gra& g)
	: aplikacja(g.aplikacja), fabryka(ZmianaFabryka::pobierzInstancje()),uzytkownik(g.uzytkownik), idPlanety(g.idPlanety)
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

Uzytkownik& Gra::getUzytkownik() const throw (NieznalezionoObiektu) {
	if(!uzytkownik)
		throw NieznalezionoObiektu(EXCEPTION_PLACE,Tekst("Uzytkownik"));
	return *uzytkownik;
}

//TODO: Dopisanie poprawnego logowania
bool Gra::Logowanie(const string& nazwa, const string& hash){
	uzytkownik = shared_ptr<Uzytkownik>(new Uzytkownik());
	return true;
}
//TODO: Dopisanie poprawnego generowania planet
IdType Gra::generujPlanete(){
	auto p = shared_ptr<Planeta>( new Planeta(idPlanety()));
	wolnePlanety.insert(make_pair(p->getId(),p));
	return p->getId();
}

bool Gra::przeniesPlaneteDoUzytkownika( const IdType& p ){
	if(!uzytkownik)
		return false;
	auto iter = wolnePlanety.find(p);
	if(iter==wolnePlanety.end())
		return false;
	if(uzytkownik->dodajPlanete(iter->second)){
		wolnePlanety.erase(iter);
		return true;
	}
	return false;
}

bool Gra::wybudujNaPlanecie( Planeta& p , const IdType& id , const Ilosc& ilosc )const{
	auto iterObiektow = listaObiektowInfo.find(id);
	if(iterObiektow != listaObiektowInfo.end()){
		return iterObiektow->second->Tworz(*this,p,ilosc);
	}
	return false;
}

bool Gra::wybudujNaPlanecie( Planeta& p, const BudynekInfo& b, const Ilosc& ilosc )const{
	p.dodajObiekt(shared_ptr<Budynek>(b.TworzEgzemplarz(ilosc,p.getId())));
	return true;
}

bool Gra::wybudujNaPlanecie( Planeta& p, const TechnologiaInfo& b, const Ilosc& ilosc )const{
	p.dodajObiekt(shared_ptr<Technologia>(b.TworzEgzemplarz(ilosc,p.getId())));
	return true;
}

bool Gra::wybudujNaPlanecie( Planeta& p, const StatekInfo& b, const Ilosc& ilosc )const{
	p.dodajObiekt(shared_ptr<Statek>(b.TworzEgzemplarz(ilosc,p.getId())));
	return true;
}

bool Gra::wybudujNaPlanecie( Planeta& p, const SurowceInfo& b, const Ilosc& ilosc )const{
	p.dodajObiekt(shared_ptr<Surowce>(b.TworzEgzemplarz(ilosc,p.getId())));
	return true;
}

StatekInfo& Gra::getStatek(const IdType& id)const throw (NieznalezionoObiektu) {
	auto iter = listaStatkowInfo.find(id);
	if(iter==listaStatkowInfo.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
	return *(iter->second);
}

SurowceInfo& Gra::getSurowce(const IdType& id)const throw (NieznalezionoObiektu) {
	auto iter = listaSurowcowInfo.find(id);
	if(iter==listaSurowcowInfo.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
	return *(iter->second);
}

TechnologiaInfo& Gra::getTechnologia(const IdType& id)const throw (NieznalezionoObiektu) {
	auto iter = listaTechnologiInfo.find(id);
	if(iter==listaTechnologiInfo.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
	return *(iter->second);
}

BudynekInfo& Gra::getBudynek(const IdType& id)const throw (NieznalezionoObiektu) {
	auto iter = listaBudynkowInfo.find(id);
	if(iter==listaBudynkowInfo.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,id.toString());
	return *(iter->second);
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
			if(!WczytajTechnologie(root_data))
				return false;
			if(!WczytajBudynki(root_data))
				return false;
		}
	}catch(ticpp::Exception& e){
		cout<< e.what();
		aplikacja.getLog().error("Nie uda³o siê otworzyæ pliku!");
		return false;
	}
	return true;
}

bool Gra::WczytajTechnologie(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		try{
			ptr = root->IterateChildren(CLASSNAME(TechnologiaInfo),ptr);
			if(ptr){
				shared_ptr<TechnologiaInfo> t(new TechnologiaInfo(ptr));
				aplikacja.getLog().debug(*t);
				if(listaObiektowInfo.find(t->getId())!=listaObiektowInfo.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaTechnologiInfo[t->getId()]=t;
				listaObiektowInfo[t->getId()]=t;
			}
		}catch(OgolnyWyjatek& e){
			aplikacja.getLog().warn(e.generujKomunikat());
			aplikacja.getLog().debug(e);
			return false;
		}
	}while(ptr);
	return true;
}

bool Gra::WczytajBudynki(ticpp::Node* root){
	ticpp::Node* ptr = nullptr;
	do{
		try{
			ptr = root->IterateChildren(CLASSNAME(BudynekInfo),ptr);
			if(ptr){
				shared_ptr<BudynekInfo> t(new BudynekInfo(ptr));
				aplikacja.getLog().debug(*t);
				if(listaObiektowInfo.find(t->getId())!=listaObiektowInfo.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaBudynkowInfo[t->getId()]=t;
				listaObiektowInfo[t->getId()]=t;
			}
		}catch(OgolnyWyjatek& e){
			aplikacja.getLog().warn(e.generujKomunikat());
			aplikacja.getLog().debug(e);
			return false;
		}
	}while(ptr);
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
				if(listaObiektowInfo.find(t->getId())!=listaObiektowInfo.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaSurowcowInfo[t->getId()]=t;
				listaObiektowInfo[t->getId()]=t;
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
				if(listaObiektowInfo.find(t->getId())!=listaObiektowInfo.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaStatkowInfo[t->getId()]=t;
				listaObiektowInfo[t->getId()]=t;
			}
		}catch(OgolnyWyjatek& e){
			aplikacja.getLog().warn(e.generujKomunikat());
			aplikacja.getLog().debug(e);
			return false;
		}
	}while(ptr);
	return true;
}

bool Gra::zapisz( TiXmlElement* e ) const{
	TiXmlElement* n = new TiXmlElement(CLASSNAME(Gra));
	e->LinkEndChild( n );
	for(auto o :  wolnePlanety)
		if(!o.second->zapisz(n))
			return false;
	return idPlanety.zapisz(n) && ( uzytkownik ? uzytkownik->zapisz(n) : true );
}

bool Gra::odczytaj( TiXmlElement* n ){

	return false;
}
