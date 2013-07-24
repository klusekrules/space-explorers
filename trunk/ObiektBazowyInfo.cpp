#include "ObiektBazowyInfo.h"
#include "Logger.h"
#include "ObiektBazowy.h"
#include "definicjeWezlowXML.h"
#include "XmlBO.h"

ObiektBazowyInfo::ObiektBazowyInfo( const Info& ilosc , const Poziom& poziom ) throw()
	: Info(ilosc), poziom_(poziom)
{
}

ObiektBazowyInfo::ObiektBazowyInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML)
	: Info(wezel)
{
	if(wezel){
		try{
			if(!XmlBO::WczytajAtrybut(wezel,ATRYBUT_XML_POZIOM,poziom_))
				throw WyjatekParseraXML(EXCEPTION_PLACE,exception(),WyjatekParseraXML::trescBladStrukturyXml);
		}catch(exception& wyjatek){
			throw WyjatekParseraXML(EXCEPTION_PLACE,wyjatek,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

ObiektBazowyInfo::~ObiektBazowyInfo(){
}

ObiektBazowy* ObiektBazowyInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const{
	return new ObiektBazowy(ilosc,pobierzPoziom(),identyfikatorPlanety,*this);
}

bool ObiektBazowyInfo::tworz( const Gra& gra, Planeta& planeta, const Ilosc& ilosc ) const{
	return false;
}

const Poziom& ObiektBazowyInfo::pobierzPoziom()const{
	return poziom_;
}

string ObiektBazowyInfo::napis() const{
	Logger str(NAZWAKLASY(ObiektBazowyInfo));
	str.dodajKlase(Info::napis());	
	str.dodajPole(NAZWAKLASY(Poziom),poziom_);
	return str.napis();
}