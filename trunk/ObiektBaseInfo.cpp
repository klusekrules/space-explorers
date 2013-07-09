#include "ObiektBaseInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "ObiektBase.h"
#include "Gra.h"

ObiektBaseInfo::ObiektBaseInfo(const Info& i , const Poziom& p) throw()
	: Info(i), poziom(p)
{
}

ObiektBaseInfo::ObiektBaseInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: Info(XmlBO::ZnajdzWezel<NOTHROW>(n,CLASSNAME(Info)))
{
	if(n){
		try{
			poziom(stoi(n->Attribute("poziom")));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

ObiektBase* ObiektBaseInfo::TworzEgzemplarz( const Ilosc& i, const IdType& idPlanety ) const{
	return new ObiektBase(i,getPoziom(),idPlanety,*this);
}

bool ObiektBaseInfo::Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const{
	return false;
}

const Poziom& ObiektBaseInfo::getPoziom()const{
	return poziom;
}

string ObiektBaseInfo::toString() const{
	Logger str(CLASSNAME(ObiektBaseInfo));
	str.addClass(Info::toString());	
	str.addField(CLASSNAME(Poziom),poziom);
	return str.toString();
}
