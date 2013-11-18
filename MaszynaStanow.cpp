#include "MaszynaStanow.h"
#include "TestyJednostkowe.h"
#include "OknoGry.h"

MaszynaStanow::MaszynaStanow()
	: aktualnyStan_(StanGry::StanyGry::Niezainicjalizowana,0,std::chrono::milliseconds(0)), watekGraficzny_(true)
{
}

MaszynaStanow::MaszynaStanow( const MaszynaStanow& o )
	: aktualnyStan_(o.aktualnyStan_), watekGraficzny_(true)
{
}

MaszynaStanow::MaszynaStanow( MaszynaStanow&& o )
	: aktualnyStan_(o.aktualnyStan_), watekGraficzny_(true)
{
}

MaszynaStanow& MaszynaStanow::operator=(const MaszynaStanow& o){
	aktualnyStan_ = o.aktualnyStan_;
	return *this;
}

MaszynaStanow::~MaszynaStanow(){
}

StanGry& MaszynaStanow::pobierzStan(){
	return aktualnyStan_;
}

MaszynaStanow& MaszynaStanow::pobierzInstancje(){
	static MaszynaStanow maszyna;
	return maszyna;
}

void MaszynaStanow::start(){
	if(aktualnyStan_ != StanGry::StanyGry::Niezainicjalizowana)
		return;

	aktualnyStan_.ustawStan( StanGry::StanyGry::EkranStartowy );
	aktualnyStan_.ustawNastepnyStan( StanGry::StanyGry::EkranStartowy );
	watekGraficzny_.odblokuj();

	while(aktualnyStan_ != StanGry::StanyGry::Wylacznie)
	{
		petlaGlowna();
		aktualnyStan_.przejdzDoNastepnegoStanu();
		std::this_thread::yield();
	}
	watekGraficzny_.czekajNaZakonczenie();
}

void MaszynaStanow::petlaGlowna(){
	switch(aktualnyStan_.pobierzStan())
	{
	case StanGry::StanyGry::Testowanie :	
		TestyJednostkowe::pobierzInstancje().wykonajTesty();
		aktualnyStan_.ustawNastepnyStan( StanGry::StanyGry::MenuGlowne );
		break;
	default:
		break;
	}
}
