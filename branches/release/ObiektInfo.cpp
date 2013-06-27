#include "ObiektInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"

ObiektInfo::ObiektInfo( const Masa& masa, const Objetosc& obj, const Powierzchnia& pow, const ObiektBaseInfo& info ) throw()
	: ObiektBaseInfo(info),powierzchnia(pow), zmPowierzchnia(nullptr), objetosc(obj), zmObjetosc(nullptr), masa(masa), zmMasa(nullptr)
{
}

ObiektInfo::ObiektInfo( ticpp::Node* n ) throw(WyjatekParseraXML)
	: ObiektBaseInfo(XmlBO::IterateChildren<THROW>(n,CLASSNAME(ObiektBaseInfo))), zmPowierzchnia(nullptr), zmObjetosc(nullptr), zmMasa(nullptr)
{
	if(n){
		try{
			ticpp::Element* e = n->ToElement();
			masa.setMasa(stold(e->GetAttribute("masa")));
			zmMasa = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenElementIf<NOTHROW>(n,"Zmiana","for","masa"));
			objetosc.setObjetosc(stold(e->GetAttribute("objetosc")));
			zmObjetosc = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenElementIf<NOTHROW>(n,"Zmiana","for","objetosc"));
			powierzchnia.setPowierzchnia(stold(e->GetAttribute("powierzchnia")));
			zmPowierzchnia = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenElementIf<NOTHROW>(n,"Zmiana","for","powierzchnia"));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

ObiektInfo::~ObiektInfo(){
}

Powierzchnia ObiektInfo::getPowierzchnia(const Poziom& pz) const {
	if(zmPowierzchnia == nullptr)
		return powierzchnia;			
	return Powierzchnia(zmPowierzchnia->value(powierzchnia.value(),static_cast<int>(pz.value())));
}

Objetosc ObiektInfo::getObjetosc(const Poziom& pz) const {
	if(zmPowierzchnia == nullptr)
		return objetosc;
	return Objetosc(zmObjetosc->value(objetosc.value(),static_cast<int>(pz.value())));
}

Masa ObiektInfo::getMasa(const Poziom& pz) const {
	if(zmPowierzchnia == nullptr)
		return masa;
	return Masa(zmMasa->value(masa.value(),static_cast<int>(pz.value())));
}

Obiekt* ObiektInfo::TworzEgzemplarz( const Ilosc& iIlosc ) const {
	return new Obiekt( iIlosc, getPoziom(), *this );
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