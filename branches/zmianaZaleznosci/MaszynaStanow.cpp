#include "MaszynaStanow.h"
#include "TestyJednostkowe.h"
#include "OknoGry.h"
#include "Aplikacja.h"
#include "XmlBO.h"

MaszynaStanow::LuaStan::LuaStan()
	: poprawne_aktualny_(false), poprawne_nastepny_(false), poprawne_poprzedni_(false), poprawne_zdarzenie_(false)
{
}

MaszynaStanow::MaszynaStanow()
	: watekGraficzny_(true), stan_(nullptr), stanNastepny_(nullptr), pulaWatkow_(4)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("resource\\state.xml");
	tinyxml2::XMLElement* root = doc.RootElement();
	XmlBO::WczytajAtrybut<THROW>(root,ATRYBUT_XML_STAN_POCZATKOWY,idStanuPoczatkowy_);
	for(tinyxml2::XMLElement* element = root->FirstChildElement(WEZEL_XML_STAN); element ; element = element->NextSiblingElement(WEZEL_XML_STAN)){
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

void MaszynaStanow::kolejkujZdarzenie( const Zdarzenie &komunikat ){
	std::lock_guard<std::mutex> blokada(mutexZdarzen_);
	kolejkaZdarzen_.push_back(komunikat);
}

void MaszynaStanow::wstawZdarzenie( const Zdarzenie &komunikat ){
	std::lock_guard<std::mutex> blokada(mutexZdarzen_);
	kolejkaZdarzen_.push_front(komunikat);
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
	Stan s(wszystkieStany_.at(idStanuPoczatkowy_));
	ustawNastepnyStan(s);
	
	wlaczone = watekGraficzny_.czekajNaInicjalizacje();

	if(wlaczone)
		przejdzDoNastepnegoStanu();

	watekGraficzny_.uruchom();

	while( wlaczone )
	{
		luaStan_.poprawne_zdarzenie_ = false;
		obslugaZdarzenia();
		przejdzDoNastepnegoStanu();
		std::this_thread::yield();
	}
	watekGraficzny_.czekajNaZakonczenie();
}

void MaszynaStanow::przejdzDoNastepnegoStanu(){
	std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
	if(stanNastepny_.opisStanu()){
		luaStan_.poprawne_poprzedni_= false;
		luaStan_.ustawAktualny(stan_);
		luaStan_.ustawNastepny(stanNastepny_);
		stan_.akcjaWyjscia();
		
		luaStan_.poprawne_nastepny_= false;
		luaStan_.ustawPoprzedni(stan_);
		stan_ = stanNastepny_;
		luaStan_.ustawAktualny(stan_);
		stan_.akcjaWejscia();

	}else{

		luaStan_.poprawne_nastepny_= false;
		luaStan_.ustawPoprzedni(stan_);
		stan_.numer_ = stanNastepny_.numer_;
		luaStan_.ustawAktualny(stan_);
		stan_.akcjaWewnetrzna();
	}
}

void MaszynaStanow::obslugaZdarzenia(){
	
	Zdarzenie komunikat;
	Stan aktualny = pobierzStan();
	Stan nowy(nullptr);
	nowy.numer_ = aktualny.numer_;

	if(pobierzKomunikat(komunikat)){
		if(aktualny == komunikat ){
			auto opisStanu = aktualny.opisStanu();
			auto opisZdarzenia = opisStanu->pobierzZdarzenie(komunikat.idZdarzenia_);
			if(opisZdarzenia){
				luaStan_.ustawAktualny(aktualny);
				auto idNowegoStanu = opisZdarzenia->pobierzStan();
				if(idNowegoStanu && *idNowegoStanu!=aktualny.id_){
					auto nowyStan = pobierzOpisStanu(*idNowegoStanu);
					if(nowyStan){
						nowy=Stan(nowyStan);
					}
				}
				
				auto numerNowegoStanu = opisZdarzenia->pobierzNumer();
				if(numerNowegoStanu){
					aktualny.numer_ = nowy.numer_ = *numerNowegoStanu;
				}

				if(idNowegoStanu){
					luaStan_.ustawNastepny(nowy);
				}else{
					luaStan_.ustawNastepny(aktualny);
				}

				luaStan_.ustawZdarzenie(komunikat);
				opisZdarzenia->wykonaj();
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

void MaszynaStanow::dodajZadanie( Zadanie& zadanie ){
	pulaWatkow_.dodajZadanie(zadanie);
}

bool MaszynaStanow::LuaStan::pobierzZdarzenie( struct Zdarzenie_t& z ){
	if(poprawne_zdarzenie_)
		z = zdarzenie_;
	return poprawne_zdarzenie_;
}

bool MaszynaStanow::LuaStan::pobierzPoprzedniStan( struct Stan_t& s ){
	if(poprawne_poprzedni_)
		s = poprzedni_;
	return poprawne_poprzedni_;
}

bool MaszynaStanow::LuaStan::pobierzAktualnyStan( struct Stan_t& s ){
	if(poprawne_aktualny_)
		s = aktualny_;
	return poprawne_aktualny_;
}

bool MaszynaStanow::LuaStan::pobierzNastepnyStan( struct Stan_t& s ){
	if(poprawne_nastepny_)
		s = nastepny_;
	return poprawne_nastepny_;
}

void MaszynaStanow::LuaStan::ustawZdarzenie(const Zdarzenie& z){
	poprawne_zdarzenie_ = true;
	zdarzenie_.idStanu_ = z.idStanu_();
	zdarzenie_.numer_ = z.numer_;
	zdarzenie_.idZdarzenia_ = z.idZdarzenia_();
}

void MaszynaStanow::LuaStan::ustawPoprzedni(const Stan& z){
	poprawne_poprzedni_ = true;
	poprzedni_.idStanu_ = z.id_();
	poprzedni_.numer_ = z.numer_;
	poprzedni_.dt_ = z.dt_.count();
}

void MaszynaStanow::LuaStan::ustawAktualny(const Stan& z){
	poprawne_aktualny_ = true;
	aktualny_.idStanu_ = z.id_();
	aktualny_.numer_ = z.numer_;
	aktualny_.dt_ = z.dt_.count();
}

void MaszynaStanow::LuaStan::ustawNastepny(const Stan& z){
	poprawne_nastepny_ = true;
	nastepny_.idStanu_ = z.id_();
	nastepny_.numer_ = z.numer_;
	nastepny_.dt_ = z.dt_.count();
}