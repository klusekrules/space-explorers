#include "Info.h"
#include "Logger.h"
#include "XmlBO.h"

Info::Info( const Tekst& tNazwa , const Tekst& tOpis, const IdType& id , const Wymagania& w )
	: Base(id), nazwa( tNazwa ), opis( tOpis ), wymagania(w)
{
}
Info::Info( ticpp::Node* n )
	: Base( n ) , wymagania( XmlBO::IterateChildren(n,Wymagania::className(),false)  )
{
	if(n!=nullptr){
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

bool Info::sprawdzWymagania(const Ilosc& i, const IdType& idPlanety) const{
	return wymagania.sprawdzWymagania(i,idPlanety);
}

const Wymagania& Info::getWymagania() const{
	return wymagania;
}

string Info::toString() const{
	Logger str(LogInfo::className());
	str.addClass(Base::toString());
	str.addField("Nazwa",nazwa);
	str.addField("Opis",opis);
	str.addField(Wymagania::className(),wymagania);
	return str.toString();
}