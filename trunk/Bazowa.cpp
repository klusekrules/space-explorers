#include "Bazowa.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

Bazowa::Bazowa( const Identyfikator& identyfikator )throw()
	: identyfikator_(identyfikator)
{
}

Bazowa::Bazowa( TiXmlElement* wezel ) throw(WyjatekParseraXML){
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

bool Bazowa::zapisz( TiXmlElement* wezel ) const{
	wezel->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR,identyfikator_.napis());
	return true;
}

bool Bazowa::odczytaj( TiXmlElement* wezel ){
	if(wezel){
		auto atrybut = wezel->Attribute(ATRYBUT_XML_IDENTYFIKATOR);
		if(!atrybut)
			return false;
		string napisAtrybutu = atrybut;
		Utils::trim(napisAtrybutu);
		if(napisAtrybutu.empty())
			return false;
		identyfikator_(stoul(napisAtrybutu,nullptr,0));
		return true;
	}
	return false;
}

string Bazowa::napis() const{
	Logger str(NAZWAKLASY(Bazowa));
	str.dodajPole("Identyfikator",identyfikator_);
	return str.napis();
}
