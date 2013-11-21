#include "MaszynaStanow.h"
#include "TestyJednostkowe.h"
#include "OknoGry.h"
#include "Aplikacja.h"
#include "parser\ticpp.h"

MaszynaStanow::MaszynaStanow()
	: aktualnyStan_(StanGry::StanyGry::Niezainicjalizowana,0,std::chrono::milliseconds(0),Identyfikator(0x0)),
	nastepnyStan_(StanGry::StanyGry::Niezainicjalizowana,0,std::chrono::milliseconds(0),Identyfikator(0x0)), watekGraficzny_(true)
{
	TiXmlDocument doc;
	doc.LoadFile("resource\\state.xml");
	for(TiXmlElement* element = doc.RootElement()->FirstChildElement(WEZEL_XML_STAN); element ; element = element->NextSiblingElement(WEZEL_XML_STAN)){
		auto stan = std::make_shared<StanInfo>(element);
		wszystkieStany_.insert(std::make_pair(stan->pobierzIdentyfikator(), stan));
		//Test
		stan->wykonaj(StanInfo::AkcjaWewnetrzna);
		stan->wykonaj(StanInfo::AkcjaWewnetrzna);
		stan->wykonaj(StanInfo::AkcjaWewnetrzna);
		stan->pobierzZdarzenie(Identyfikator(0x1))->wykonaj();
		stan->pobierzZdarzenie(Identyfikator(0x1))->wykonaj();
		//----
	}
}

MaszynaStanow::MaszynaStanow( const MaszynaStanow& o )
	: aktualnyStan_(o.aktualnyStan_), nastepnyStan_(o.nastepnyStan_), watekGraficzny_(true), wszystkieStany_(o.wszystkieStany_)
{
}

MaszynaStanow::MaszynaStanow( MaszynaStanow&& o )
	: aktualnyStan_(o.aktualnyStan_), nastepnyStan_(o.nastepnyStan_), watekGraficzny_(true), wszystkieStany_(o.wszystkieStany_)
{
}

MaszynaStanow& MaszynaStanow::operator=(const MaszynaStanow& o){
	return *this;
}

MaszynaStanow::~MaszynaStanow(){
}

StanGry MaszynaStanow::pobierzStan(){
	std::lock_guard<std::mutex> blokada(mutexStanu_);
	return aktualnyStan_;
}

void MaszynaStanow::scalStan( const StanGry& stan ){
	std::lock_guard<std::mutex> blokada(mutexStanu_);
	nastepnyStan_ = stan;
}

MaszynaStanow& MaszynaStanow::pobierzInstancje(){
	static MaszynaStanow maszyna;
	return maszyna;
}

void MaszynaStanow::start(){
	if(aktualnyStan_ != StanGry::StanyGry::Niezainicjalizowana)
		return;

	aktualnyStan_.ustawStan( StanGry::StanyGry::ZmianaEkranu );
	aktualnyStan_.ustawNastepnyStan( StanGry::StanyGry::ZmianaEkranu );
	aktualnyStan_.ustawIdEkranu( Aplikacja::pobierzInstancje().pobierzIdEkranuStartowego() );
	nastepnyStan_ = aktualnyStan_;
	watekGraficzny_.odblokuj();

	while(aktualnyStan_ != StanGry::StanyGry::Wylacznie)
	{
		petlaGlowna();
		przejdzDoNastepnegoStanu();
		std::this_thread::yield();
	}
	watekGraficzny_.czekajNaZakonczenie();
}

void MaszynaStanow::przejdzDoNastepnegoStanu(){
	std::lock_guard<std::mutex> blokada(mutexStanu_);
	aktualnyStan_ = nastepnyStan_;
	aktualnyStan_.przejdzDoNastepnegoStanu();
}

void MaszynaStanow::petlaGlowna(){
	switch(aktualnyStan_.pobierzStan())
	{
	case StanGry::StanyGry::Testowanie :	
		TestyJednostkowe::pobierzInstancje().wykonajTesty();
		nastepnyStan_.ustawNastepnyStan( StanGry::StanyGry::Menu );
		break;
	default:
		break;
	}
}
