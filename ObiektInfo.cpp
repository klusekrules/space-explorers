#include "ObiektInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"

ObiektInfo::ObiektInfo( const Masa& masa, const Objetosc& obj, const Powierzchnia& pow, const ObiektBaseInfo& info ) throw()
	: ObiektBaseInfo(info),powierzchnia(pow), zmPowierzchnia(nullptr), objetosc(obj), zmObjetosc(nullptr), masa(masa), zmMasa(nullptr)
{
}

ObiektInfo::ObiektInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: ObiektBaseInfo(XmlBO::IterateChildren<THROW>(n,CLASSNAME(ObiektBaseInfo))), zmPowierzchnia(nullptr), zmObjetosc(nullptr), zmMasa(nullptr)
{
	if(n){
		try{
			masa.setMasa(stold(n->Attribute("masa")));
			zmMasa = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenIf<NOTHROW>(n,"Zmiana","for","masa"));
			objetosc.setObjetosc(stold(n->Attribute("objetosc")));
			zmObjetosc = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenIf<NOTHROW>(n,"Zmiana","for","objetosc"));
			powierzchnia.setPowierzchnia(stold(n->Attribute("powierzchnia")));
			zmPowierzchnia = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenIf<NOTHROW>(n,"Zmiana","for","powierzchnia"));
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
	return Powierzchnia(zmPowierzchnia->value(powierzchnia.value(),static_cast<int>(pz.value()),idPlanety.value()));
}

Objetosc ObiektInfo::getObjetosc(const Poziom& pz, const IdType& idPlanety) const {
	if(zmPowierzchnia == nullptr)
		return objetosc;
	return Objetosc(zmObjetosc->value(objetosc.value(),static_cast<int>(pz.value()), idPlanety.value()));
}

Masa ObiektInfo::getMasa(const Poziom& pz, const IdType& idPlanety) const {
	if(zmPowierzchnia == nullptr)
		return masa;
	return Masa(zmMasa->value(masa.value(),static_cast<int>(pz.value()), idPlanety.value()));
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