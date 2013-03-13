#include "ObiektInfo.h"
#include "Logger.h"

ObiektInfo::ObiektInfo( const Masa& masa, const Objetosc& obj, const Powierzchnia& pow, const Poziom& p , const Info& info )
	: Info(info), masa(masa), objetosc(obj), powierzchnia(pow), obObiekt(Ilosc(),p,info), zmMasa(nullptr), zmObjetosc(nullptr), zmPowierzchnia(nullptr)
{
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

const ObiektBase& ObiektInfo::getObiektBase() const{
	return obObiekt;
}

Obiekt* ObiektInfo::TworzEgzemplarz( const Ilosc& iIlosc ) const {
	Obiekt* o = new Obiekt( *this );
	o->setIlosc(iIlosc);
	return o;
}

string ObiektInfo::toString() const{
	Logger str(LogObiektInfo::className());
	str.addField("ObiektBase",static_cast< const ObiektBase::LogObiektBase& >(obObiekt));
	str.addField("Masa",masa);
	str.addField("Objetosc",objetosc);
	str.addField("Powierzchnia",powierzchnia);
	if(zmMasa!=nullptr)
		str.addField("ZmianaMasy",*zmMasa);
	if(zmObjetosc!=nullptr)
		str.addField("ZmianaObjetosci",*zmObjetosc);
	if(zmPowierzchnia!=nullptr)
		str.addField("ZmianaPowierzchni",*zmPowierzchnia);
	return str.toString();
}