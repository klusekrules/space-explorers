#include "ObiektInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

ObiektInfo::ObiektInfo( const Masa& masa, const Objetosc& obj, const Powierzchnia& pow, const ObiektBaseInfo& info ) throw()
	: ObiektBaseInfo(info),powierzchnia(pow), zmPowierzchnia(nullptr), objetosc(obj), zmObjetosc(nullptr), masa(masa), zmMasa(nullptr)
{
}

ObiektInfo::ObiektInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: ObiektBaseInfo(n), zmPowierzchnia(nullptr), zmObjetosc(nullptr), zmMasa(nullptr)
{
	if(n){
		try{
			ZmianaFabryka& fabryka = Aplikacja::getInstance().getGra().getZmianaFabryka();
			masa(stold(n->Attribute(ATRYBUT_XML_MASA)));
			zmMasa = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_MASA));
			objetosc(stold(n->Attribute(ATRYBUT_XML_OBJETOSC)));
			zmObjetosc = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_OBJETOSC));
			powierzchnia(stold(n->Attribute(ATRYBUT_XML_POWIERZCHNIA)));
			zmPowierzchnia = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_POWIERZCHNIA));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

ObiektInfo::~ObiektInfo(){
}

Powierzchnia ObiektInfo::getPowierzchnia(const Poziom& pz, const IdType& idPlanety) const {
	if(zmPowierzchnia == nullptr)
		return powierzchnia;			
	return Powierzchnia(zmPowierzchnia->policzWartosc(powierzchnia(),static_cast<int>(pz()),idPlanety()));
}

Objetosc ObiektInfo::getObjetosc(const Poziom& pz, const IdType& idPlanety) const {
	if(zmPowierzchnia == nullptr)
		return objetosc;
	return Objetosc(zmObjetosc->policzWartosc(objetosc(),static_cast<int>(pz()), idPlanety()));
}

Masa ObiektInfo::getMasa(const Poziom& pz, const IdType& idPlanety) const {
	if(zmPowierzchnia == nullptr)
		return masa;
	return Masa(zmMasa->policzWartosc(masa(),static_cast<int>(pz()), idPlanety()));
}

Obiekt* ObiektInfo::TworzEgzemplarz( const Ilosc& iIlosc, const IdType& idPlanety ) const {
	return new Obiekt( iIlosc, getPoziom(),idPlanety, *this );
}

string ObiektInfo::toString() const{
	Logger str(CLASSNAME(ObiektInfo));
	str.addClass(ObiektBaseInfo::toString());
	str.addField(CLASSNAME(Masa),masa);
	str.addField(CLASSNAME(Objetosc),objetosc);
	str.addField(CLASSNAME(Powierzchnia),powierzchnia);
	if(zmMasa!=nullptr)
		str.addField("ZmianaMasy",*zmMasa);
	if(zmObjetosc!=nullptr)
		str.addField("ZmianaObjetosci",*zmObjetosc);
	if(zmPowierzchnia!=nullptr)
		str.addField("ZmianaPowierzchni",*zmPowierzchnia);
	return str.toString();
}