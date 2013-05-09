#include "Info.h"
#include "Logger/Logger.h"
#include "XmlBO.h"

Info::Info( const Tekst& tNazwa , const Tekst& tOpis, const IdType& id , const Wymagania& w ) throw()
	: Base(id), nazwa( tNazwa ), opis( tOpis ), Wymagania(w)
{
}
Info::Info( ticpp::Node* n ) throw(WyjatekParseraXML)
	: Base( n ) , Wymagania( XmlBO::IterateChildren(n,CLASSNAME(Wymagania),false)  )
{
	if(n){
		try{
			ticpp::Element* e = n->ToElement();
			setNazwa(e->GetAttribute("nazwa"));
			setOpis(e->GetText(false));
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

string Info::toString() const{
	Logger str(CLASSNAME(Info));
	str.addClass(Base::toString());
	str.addClass(Wymagania::toString());
	str.addField("Nazwa",nazwa);
	str.addField("Opis",opis);
	return str.toString();
}