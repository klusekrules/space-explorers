#include "JednostkaLatajacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"

JednostkaLatajacaInfo::JednostkaLatajacaInfo( const Info& info,const Klucz& k, const MocSilnika& moc, const ZuzyciePaliwa& z, const Masa& masa ) throw()
	: Info(info), rodzajNapedu(k), mocSilnika(moc), zuzyciePaliwa(z), masaNapedu(masa), przyrostMocySilnika(nullptr), przyrostSprawnosciSilnika(nullptr), przyrostZuzyciaPaliwa(nullptr), przyrostMasyNapedu(nullptr)
{
}

JednostkaLatajacaInfo::JednostkaLatajacaInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: Info(XmlBO::ZnajdzWezel<THROW>(n,CLASSNAME(Info))), przyrostMocySilnika(nullptr), przyrostSprawnosciSilnika(nullptr), przyrostZuzyciaPaliwa(nullptr), przyrostMasyNapedu(nullptr)
{
	if(n){
		try{
			IdType id(stoi(n->Attribute("rodzajSilnikaId"),nullptr,0));
			Poziom poziom(stoi(n->Attribute("rodzajSilnikaPoziom")));
			rodzajNapedu(Klucz(id,poziom)());
			
			mocSilnika(stold(n->Attribute("mocSilnika")));
			przyrostMocySilnika = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,"Zmiana","for","mocSilnika"));
			
			zuzyciePaliwa(stold(n->Attribute("zuzyciePaliwa")));
			przyrostZuzyciaPaliwa = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,"Zmiana","for","zuzyciePaliwa"));
			
			masaNapedu(stold(n->Attribute("masaSilnika")));
			przyrostMasyNapedu = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,"Zmiana","for","masaSilnika"));
			
			sprawnoscSilnika(stof(n->Attribute("sprawnoscSilnika")));
			przyrostSprawnosciSilnika = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,"Zmiana","for","sprawnoscSilnika"));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

const Klucz& JednostkaLatajacaInfo::getRodzajNapedu() const{
	return rodzajNapedu;
}

MocSilnika JednostkaLatajacaInfo::getMocSilnika() const{
	return mocSilnika;
}

ZuzyciePaliwa JednostkaLatajacaInfo::getZuzyciePaliwa() const{
	return zuzyciePaliwa;
}

Masa JednostkaLatajacaInfo::getMasaNapedu() const{
	return masaNapedu;
}

Fluktuacja JednostkaLatajacaInfo::getSprawnoscSilnika() const{
	return sprawnoscSilnika;
}

MocSilnika JednostkaLatajacaInfo::getMocSilnika(const PodstawoweParametry& p) const{
	if(przyrostMocySilnika)
		return MocSilnika(przyrostMocySilnika->value(mocSilnika(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()()));
	else
		return mocSilnika;
}

ZuzyciePaliwa JednostkaLatajacaInfo::getZuzyciePaliwa(const PodstawoweParametry& p) const{
	if(przyrostZuzyciaPaliwa)
		return ZuzyciePaliwa(przyrostZuzyciaPaliwa->value(zuzyciePaliwa(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()()));
	else
		return zuzyciePaliwa;
}

Masa JednostkaLatajacaInfo::getMasaNapedu( const PodstawoweParametry& p) const{
	if(przyrostMasyNapedu)
		return Masa(przyrostMasyNapedu->value(masaNapedu(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()()));
	else
		return masaNapedu;
}

Fluktuacja JednostkaLatajacaInfo::getSprawnoscSilnika( const PodstawoweParametry& p) const{
	if(przyrostSprawnosciSilnika)
		return Fluktuacja(static_cast<float>(przyrostSprawnosciSilnika->value(sprawnoscSilnika(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()())));
	else
		return sprawnoscSilnika;
		
}

string JednostkaLatajacaInfo::toString() const{
	Logger str(CLASSNAME(JednostkaLatajacaInfo));
	str.addClass(Info::toString());
	str.addField("RodzajNapedu",rodzajNapedu);
	str.addField(CLASSNAME(MocSilnika),mocSilnika);
	if(przyrostMocySilnika!=nullptr){
		str.addField("ZmianaMocySilnika",*przyrostMocySilnika);
	}
	str.addField("SprawnoscSilnika",sprawnoscSilnika);
	if(przyrostSprawnosciSilnika!=nullptr){
		str.addField("ZmianaSprawnosciSilnika",*przyrostSprawnosciSilnika);
	}
	str.addField(CLASSNAME(ZuzyciePaliwa),zuzyciePaliwa);
	if(przyrostZuzyciaPaliwa!=nullptr){
		str.addField("ZmianaZuzyciaPaliwa",*przyrostZuzyciaPaliwa);
	}
	str.addField("MasaNapedu",masaNapedu);
	if(przyrostMasyNapedu!=nullptr){
		str.addField("ZmianaMasyNapedu",*przyrostMasyNapedu);
	}
	
	return str.toString();
}