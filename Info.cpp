#include "Info.h"
#include "Logger.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"

Info::Info( const Tekst& tNazwa , const Tekst& tOpis, const Identyfikator& id , const Wymagania& w ) throw()
	: Bazowa(id), nazwa( tNazwa ), opis( tOpis ), Wymagania(w)
{
}
Info::Info( TiXmlElement* n ) throw(WyjatekParseraXML)
	: Bazowa( n ) , Wymagania( n )
{
	if(n){
		try{
			const char* c = n->Attribute(ATRYBUT_XML_NAZWA);
			setNazwa(string( c ? c : ""));
			c = n->GetText();
			setOpis(string( c ? c : ""));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}	
}

Info::~Info(){
}

const Tekst& Info::getNazwa() const{
	return nazwa;
}

void Info::setNazwa( const Tekst& tNazwa ){
	nazwa = tNazwa;
}

const Tekst& Info::getOpis() const{
	return opis;
}

void Info::setOpis( const Tekst& tOpis ){
	opis = tOpis;
}

string Info::napis() const{
	Logger str(NAZWAKLASY(Info));
	str.dodajKlase(Bazowa::napis());
	str.dodajKlase(Wymagania::napis());
	str.dodajPole("Nazwa",nazwa);
	str.dodajPole("Opis",opis);
	return str.napis();
}