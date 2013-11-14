#include "MaszynaStanow.h"
#include "TestyJednostkowe.h"

MaszynaStanow::MaszynaStanow()
	: aktualnyStan_(StanyGry::Niezainicjalizowana,0,std::chrono::milliseconds(0)), watekGraficzny_(true)
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

MaszynaStanow::StanGry& MaszynaStanow::pobierzStan(){
	return aktualnyStan_;
}

MaszynaStanow& MaszynaStanow::pobierzInstancje(){
	static MaszynaStanow maszyna;
	return maszyna;
}

void MaszynaStanow::start(){
	if(aktualnyStan_ != StanyGry::Niezainicjalizowana)
		return;

	aktualnyStan_.ustawStan( StanyGry::EkranStartowy );
	watekGraficzny_.odblokuj();

	while(aktualnyStan_ != StanyGry::Wylacznie)
	{
		petlaGlowna();
		std::this_thread::yield();
	}
	watekGraficzny_.czekajNaZakonczenie();
}

void MaszynaStanow::petlaGlowna(){
	switch(aktualnyStan_.pobierzStan())
	{
	case StanyGry::EkranStartowy:
		break;
	case StanyGry::Testowanie :	
		TestyJednostkowe::pobierzInstancje().wykonajTesty();
		aktualnyStan_.ustawStan( StanyGry::EkranStartowy );
		break;
	default:
		break;
	}
}
