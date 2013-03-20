#include "Wymagania.h"
#include "Logger.h"
#include "XmlBO.h"

Wymagania::Wymagania( ticpp::Node* n  )
	: koszty( XmlBO::IterateChildren(n,Cennik::LogCennik::className(),false) ), wymogi(nullptr)
{
	if(n){
		//TODO wczytywanie wymogów.
	}
}

Wymagania::Wymagania( const Cennik& c, Warunek* w )
	: koszty(c), wymogi(w)
{
}

bool Wymagania::sprawdzWymagania( const Ilosc& i, const IdType& idPlanety ) const{
	if(wymogi==nullptr)
		return false;
	return koszty.czySpelniaWymagania(i,idPlanety) && wymogi->sprawdzWarunki(idPlanety);
}

Wymagania::Wymagania( const Wymagania& w )
	: koszty(w.koszty)
{	
	if(w.wymogi!=nullptr)
		wymogi = w.wymogi->Kopia();
	else
		wymogi = nullptr;
}

const Wymagania& Wymagania::operator=( const Wymagania& w ){
	koszty = w.koszty;	
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
	Logger str(className());
	str.addField("Koszty",koszty);
	if(wymogi!=nullptr)
		str.addField("Warunki",*wymogi);
	return str.toString();
}