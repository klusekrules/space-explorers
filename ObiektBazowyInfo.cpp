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
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_POZIOM,poziom_);
			if( poziom_ <= Poziom(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"poziom\" posiada niepoprawn¹ wartoœæ.") );
		}catch(exception& wyjatek){
			throw WyjatekParseraXML(EXCEPTION_PLACE,wyjatek,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

ObiektBazowyInfo::~ObiektBazowyInfo(){
}

ObiektBazowy* ObiektBazowyInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const{
	return tworzEgzemplarz(ilosc,identyfikatorPlanety,pobierzPoziom());
}

ObiektBazowy* ObiektBazowyInfo::tworzEgzemplarz( const Ilosc& ilosc , const Identyfikator& identyfikatorPlanety, const Poziom& poziom ) const{
	return new ObiektBazowy(ilosc,poziom,identyfikatorPlanety,*this);
}

bool ObiektBazowyInfo::tworz( const Gra& gra , Planeta& planeta , const Ilosc& ilosc, const Poziom& poziom ) const{
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
