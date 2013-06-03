#include "ObiektInfo.h"
#include "Logger.h"
#include "XmlBO.h"

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
			objetosc.setObjetosc(stold(e->GetAttribute("objetosc")));
			powierzchnia.setPowierzchnia(stold(e->GetAttribute("powierzchnia")));
			//TODO: dodanie wczytywania zmiany parametrów
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

ObiektInfo::~ObiektInfo(){
}

Powierzchnia ObiektInfo::getPowierzchnia() const {
	if(zmPowierzchnia == nullptr)
		return powierzchnia;			
	return Powierzchnia(zmPowierzchnia->value(powierzchnia.value(),static_cast<int>(getPoziom().value())));
}

Objetosc ObiektInfo::getObjetosc() const {
	if(zmPowierzchnia == nullptr)
		return objetosc;
	return Objetosc(zmObjetosc->value(objetosc.value(),static_cast<int>(getPoziom().value())));
}

Masa ObiektInfo::getMasa() const {
	if(zmPowierzchnia == nullptr)
		return masa;
	return Masa(zmMasa->value(masa.value(),static_cast<int>(getPoziom().value())));
}

Obiekt* ObiektInfo::TworzEgzemplarz( const Ilosc& iIlosc ) const {
	return new Obiekt( iIlosc, *this );
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