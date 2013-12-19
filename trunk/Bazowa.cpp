#include "Bazowa.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include "XmlBO.h"

Bazowa::Bazowa( const Identyfikator& identyfikator )throw()
	: identyfikator_(identyfikator)
{
}

Bazowa::Bazowa( tinyxml2::XMLElement* wezel ){
	Bazowa::odczytaj(wezel);
}

Bazowa::~Bazowa(){
}

const Identyfikator& Bazowa::pobierzIdentyfikator()const{
	return identyfikator_;
}

void Bazowa::ustawIdentyfikator( const Identyfikator& identyfikator ){
	identyfikator_ = identyfikator;
}

bool Bazowa::zapisz( tinyxml2::XMLElement* wezel ) const{
	wezel->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR,identyfikator_.napis().c_str());
	return true;
}

bool Bazowa::odczytaj( tinyxml2::XMLElement* wezel ){
	if(wezel){
		return XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR,identyfikator_);
	}
	return false;
}

string Bazowa::napis() const{
	Logger str(NAZWAKLASY(Bazowa));
	str.dodajPole("Identyfikator",identyfikator_);
	return str.napis();
}
