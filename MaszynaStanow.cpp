#include "MaszynaStanow.h"
#include "TestyJednostkowe.h"
#include "OknoGry.h"
#include "Aplikacja.h"
#include "parser\ticpp.h"
#include "XmlBO.h"

MaszynaStanow::MaszynaStanow()
	: watekGraficzny_(true), stan_(nullptr), stanNastepny_(nullptr)
{
	TiXmlDocument doc;
	doc.LoadFile("resource\\state.xml");
	TiXmlElement* root = doc.RootElement();
	XmlBO::WczytajAtrybut<THROW>(root,ATRYBUT_XML_STAN_POCZATKOWY,idStanuPoczatkowy_);
	for(TiXmlElement* element = root->FirstChildElement(WEZEL_XML_STAN); element ; element = element->NextSiblingElement(WEZEL_XML_STAN)){
		auto stan = std::make_shared<StanInfo>(element);
		wszystkieStany_.insert(std::make_pair(stan->pobierzIdentyfikator(), stan));
	}
	watekGraficzny_.zatrzymajPoInicjalizacji();
	watekGraficzny_.odblokuj();
}

bool MaszynaStanow::kolejkujOkno( int id ){
	auto ptr = watekGraficzny_.pobierzEkran(Identyfikator(id));
	if(ptr!=nullptr){
		std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
		stosEkranow_.push_back(ptr);
		return true;
	}
	return false;
}
void MaszynaStanow::wyczyscKolejkeOkien( ){
	std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
	stosEkranow_.clear();
}

MaszynaStanow::~MaszynaStanow(){
}

Stan MaszynaStanow::pobierzStan( OknoGry::StosEkranow& stos ) const{
	std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
	stos = stosEkranow_;
	return stan_;
}

Stan MaszynaStanow::pobierzStan( ) const{
	std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
	return stan_;
}

void MaszynaStanow::dodajKomunikat( const Zdarzenie &komunikat ){
	std::lock_guard<std::mutex> blokada(mutexZdarzen_);
	kolejkaZdarzen_.push_back(komunikat);
}

std::shared_ptr<StanInfo> MaszynaStanow::pobierzOpisStanu( const Identyfikator& id ) const{
	auto iter = wszystkieStany_.find(id);
	if(iter != wszystkieStany_.end())
		return iter->second;
	else
		return nullptr;
}

bool MaszynaStanow::pobierzKomunikat( Zdarzenie &komunikat ){
	std::lock_guard<std::mutex> blokada(mutexZdarzen_);
	if(kolejkaZdarzen_.empty())
		return false;
	komunikat = kolejkaZdarzen_.front();
	kolejkaZdarzen_.pop_front();
	return true;
}

void MaszynaStanow::start(){
	wlaczone = true;
	Stan s(wszystkieStany_.at(idStanuPoczatkowy_));
	ustawNastepnyStan(s);

	while(!watekGraficzny_.zainicjalizowe())
		std::this_thread::yield();

	przejdzDoNastepnegoStanu();
	watekGraficzny_.uruchom();

	while( wlaczone )
	{
		petlaGlowna();
		przejdzDoNastepnegoStanu();
		std::this_thread::yield();
	}
	watekGraficzny_.czekajNaZakonczenie();
}

void MaszynaStanow::przejdzDoNastepnegoStanu(){
	std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
	if(stanNastepny_.opisStanu()){
		stan_.akcjaWyjscia();
		stan_ = stanNastepny_;
		stan_.akcjaWejscia();
	}else{
		stan_.numer_ = stanNastepny_.numer_;
		stan_.akcjaWewnetrzna();
	}
	stanNastepny_ = Stan(nullptr);
	stanNastepny_.numer_ = stan_.numer_;
}

void MaszynaStanow::petlaGlowna(){
	
	Zdarzenie komunikat;
	Stan aktualny = pobierzStan();
	Stan nowy(nullptr);
	nowy.numer_ = aktualny.numer_;

	if(pobierzKomunikat(komunikat)){
		if(aktualny == komunikat ){
			auto opisStanu = aktualny.opisStanu();
			auto opisZdarzenia = opisStanu->pobierzZdarzenie(komunikat.idZdarzenia_);
			if(opisZdarzenia){
				opisZdarzenia->wykonaj();

				auto idNowegoStanu = opisZdarzenia->pobierzStan();
				if(idNowegoStanu){
					auto nowyStan = pobierzOpisStanu(*idNowegoStanu);
					if(nowyStan){
						nowy=Stan(nowyStan);
					}
				}
				
				auto numerNowegoStanu = opisZdarzenia->pobierzNumer();
				if(numerNowegoStanu){
					nowy.numer_ = *numerNowegoStanu;
				}
			}
		}
	}

	ustawNastepnyStan(nowy);
}

void MaszynaStanow::ustawNastepnyStan( Stan& stan ){
	stanNastepny_ = stan;
}

void MaszynaStanow::inicjujZamykanie(){
	watekGraficzny_.zakmnij();
	wlaczone = false;
}
