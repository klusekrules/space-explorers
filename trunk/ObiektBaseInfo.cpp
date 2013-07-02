#include "ObiektBaseInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "ObiektBase.h"

ObiektBaseInfo::ObiektBaseInfo(const Info& i , const Poziom& p) throw()
	: Info(i), poziom(p)
{
}

ObiektBaseInfo::ObiektBaseInfo( ticpp::Node* n ) throw(WyjatekParseraXML)
	: Info(XmlBO::IterateChildren<NOTHROW>(n,CLASSNAME(Info)))
{
	if(n){
		try{
			poziom.setPoziom(stoi(n->ToElement()->GetAttribute("poziom")));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

ObiektBaseInfo::~ObiektBaseInfo(){
}


ObiektBase* ObiektBaseInfo::TworzEgzemplarz( const Ilosc& i, const IdType& idPlanety ) const{
	return new ObiektBase(i,getPoziom(),idPlanety,*this);
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
