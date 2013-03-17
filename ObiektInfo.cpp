#include "ObiektInfo.h"
#include "Logger.h"
#include "XmlBO.h"

ObiektInfo::ObiektInfo( const Masa& masa, const Objetosc& obj, const Powierzchnia& pow, const ObiektBaseInfo& info )
	: ObiektBaseInfo(info), masa(masa), objetosc(obj), powierzchnia(pow), zmMasa(nullptr), zmObjetosc(nullptr), zmPowierzchnia(nullptr)
{
}

ObiektInfo::ObiektInfo( ticpp::Node* n )
	: ObiektBaseInfo(XmlBO::InterateChildren(n,ObiektBaseInfo::LogObiektBaseInfo::className())), zmMasa(nullptr), zmObjetosc(nullptr), zmPowierzchnia(nullptr)
{
	if(n!=nullptr){
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
	return zmPowierzchnia->value(powierzchnia);
}

Objetosc ObiektInfo::getObjetosc() const {
	if(zmPowierzchnia == nullptr)
		return objetosc;
	return zmObjetosc->value(objetosc);
}

Masa ObiektInfo::getMasa() const {
	if(zmPowierzchnia == nullptr)
		return masa;
	return zmMasa->value(masa);
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