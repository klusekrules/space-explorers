#include "Info.h"
#include "Logger.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"

Info::Info( const Tekst& nazwa , const Tekst& opis, const Identyfikator& identyfikator , const Wymagania& wymagania ) throw()
	: Bazowa(identyfikator), nazwa_( nazwa ), opis_( opis ), Wymagania(wymagania)
{
}

Info::Info( TiXmlElement* wezel ) throw(WyjatekParseraXML)
	: Bazowa( wezel ) , Wymagania( wezel )
{
	if(wezel){
		try{
			XmlBO::WczytajAtrybut(wezel,ATRYBUT_XML_NAZWA,nazwa_);
			auto tablicaZnakow = wezel->GetText();
			ustawOpis(string( tablicaZnakow ? tablicaZnakow : "" ));
		}catch(exception& wyjatek ){
			throw WyjatekParseraXML(EXCEPTION_PLACE,wyjatek,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}	
}

Info::~Info(){
}

const Tekst& Info::pobierzNazwe() const{
	return nazwa_;
}

void Info::ustawNazwe( const Tekst& nazwa ){
	nazwa_ = nazwa;
}

const Tekst& Info::pobierzOpis() const{
	return opis_;
}

void Info::ustawOpis( const Tekst& opis ){
	opis_ = opis;
}

string Info::napis() const{
	Logger str(NAZWAKLASY(Info));
	str.dodajKlase(Bazowa::napis());
	str.dodajKlase(Wymagania::napis());
	str.dodajPole("Nazwa",nazwa_);
	str.dodajPole("Opis",opis_);
	return str.napis();
}
