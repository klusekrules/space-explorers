#include "Wymagania.h"
#include "Logger.h"
#include "XmlBO.h"

Wymagania::Wymagania( ticpp::Node* n  )
	: Cennik( XmlBO::IterateChildren(n,Cennik::LogCennik::className(),false) ), wymogi(nullptr)
{
	if(n){
		//TODO wczytywanie wymogów.
	}
}

Wymagania::Wymagania( const Cennik& c, Warunek* w )
	: Cennik(c), wymogi(w)
{
}

bool Wymagania::sprawdzWymagania( const Ilosc& i, const Poziom& p, const IdType& idPlanety ) const{
	if(wymogi==nullptr)
		return false;
	return czySpelniaWymagania(i,p,idPlanety) && wymogi->sprawdzWarunki(idPlanety);
}

Wymagania::Wymagania( const Wymagania& w )
	: Cennik(w)
{	
	if(w.wymogi!=nullptr)
		wymogi = w.wymogi->Kopia();
	else
		wymogi = nullptr;
}

const Wymagania& Wymagania::operator=( const Wymagania& w ){
	Cennik::operator=(w);
	if(wymogi!=nullptr)
		delete wymogi;
	if(w.wymogi!=nullptr)
		wymogi = w.wymogi->Kopia();
	else
		wymogi = nullptr;
	return *this;
}

Wymagania::~Wymagania(){
	if(wymogi!=nullptr)
		delete wymogi;
}

string Wymagania::toString() const{
	Logger str(LogWymagania::className());
	str.addClass(Cennik::toString());
	if(wymogi!=nullptr)
		str.addField("Warunki",*wymogi);
	return str.toString();
}