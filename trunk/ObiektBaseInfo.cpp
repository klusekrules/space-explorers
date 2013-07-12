#include "ObiektBaseInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "ObiektBase.h"
#include "Gra.h"
#include "definicjeWezlowXML.h"

ObiektBaseInfo::ObiektBaseInfo(const Info& i , const Poziom& p) throw()
	: Info(i), poziom(p)
{
}

ObiektBaseInfo::ObiektBaseInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: Info(n)
{
	if(n){
		try{
			poziom(stoi(n->Attribute(ATRYBUT_XML_POZIOM)));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

ObiektBase* ObiektBaseInfo::TworzEgzemplarz( const Ilosc& i, const Identyfikator& idPlanety ) const{
	return new ObiektBase(i,getPoziom(),idPlanety,*this);
}

bool ObiektBaseInfo::Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const{
	return false;
}

const Poziom& ObiektBaseInfo::getPoziom()const{
	return poziom;
}

string ObiektBaseInfo::napis() const{
	Logger str(NAZWAKLASY(ObiektBaseInfo));
	str.dodajKlase(Info::napis());	
	str.dodajPole(NAZWAKLASY(Poziom),poziom);
	return str.napis();
}
