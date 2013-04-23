#include "ObiektInfo.h"
#include "Logger.h"
#include "XmlBO.h"

ObiektInfo::ObiektInfo( const Masa& masa, const Objetosc& obj, const Powierzchnia& pow, const ObiektBaseInfo& info ) throw()
	: ObiektBaseInfo(info),powierzchnia(pow), zmPowierzchnia(nullptr), objetosc(obj), zmObjetosc(nullptr), masa(masa), zmMasa(nullptr)
{
}

ObiektInfo::ObiektInfo( ticpp::Node* n ) throw(WyjatekParseraXML)
	: ObiektBaseInfo(XmlBO::IterateChildren(n,ObiektBaseInfo::LogObiektBaseInfo::className())), zmPowierzchnia(nullptr), zmObjetosc(nullptr), zmMasa(nullptr)
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
	return Powierzchnia(zmPowierzchnia->value(powierzchnia.value(),getPoziom()));
}

Objetosc ObiektInfo::getObjetosc() const {
	if(zmPowierzchnia == nullptr)
		return objetosc;
	return Objetosc(zmObjetosc->value(objetosc.value(),getPoziom()));
}

Masa ObiektInfo::getMasa() const {
	if(zmPowierzchnia == nullptr)
		return masa;
	return Masa(zmMasa->value(masa.value(),getPoziom()));
}

Obiekt* ObiektInfo::TworzEgzemplarz( const Ilosc& iIlosc ) const {
	return new Obiekt( iIlosc, *this );
}

string ObiektInfo::toString() const{
	Logger str(LogObiektInfo::className());
	str.addClass(ObiektBaseInfo::toString());
	str.addField(Masa::className(),masa);
	str.addField(Objetosc::className(),objetosc);
	str.addField(Powierzchnia::className(),powierzchnia);
	if(zmMasa!=nullptr)
		str.addField("ZmianaMasy",*zmMasa);
	if(zmObjetosc!=nullptr)
		str.addField("ZmianaObjetosci",*zmObjetosc);
	if(zmPowierzchnia!=nullptr)
		str.addField("ZmianaPowierzchni",*zmPowierzchnia);
	return str.toString();
}