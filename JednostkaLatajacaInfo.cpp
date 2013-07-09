#include "JednostkaLatajacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

JednostkaLatajacaInfo::JednostkaLatajacaInfo( const Info& info,const Klucz& k, const MocSilnika& moc, const ZuzyciePaliwa& z, const Masa& masa ) throw()
	: Info(info), rodzajNapedu(k), mocSilnika(moc), zuzyciePaliwa(z), masaNapedu(masa), przyrostMocySilnika(nullptr), przyrostSprawnosciSilnika(nullptr), przyrostZuzyciaPaliwa(nullptr), przyrostMasyNapedu(nullptr)
{
}

JednostkaLatajacaInfo::JednostkaLatajacaInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: Info(n), przyrostMocySilnika(nullptr), przyrostSprawnosciSilnika(nullptr), przyrostZuzyciaPaliwa(nullptr), przyrostMasyNapedu(nullptr)
{
	if(n){
		try{
			ZmianaFabryka& fabryka = Aplikacja::getInstance().getGra().getZmianaFabryka();
			IdType id(stoi(n->Attribute(ATRYBUT_XML_RODZAJ_SILNIKA_ID),nullptr,0));
			Poziom poziom(stoi(n->Attribute(ATRYBUT_XML_RODZAJ_SILNIKA_POZIOM)));
			rodzajNapedu(Klucz(id,poziom)());
			
			mocSilnika(stold(n->Attribute(ATRYBUT_XML_MOC_SILNIKA)));
			przyrostMocySilnika = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_MOC_SILNIKA));
			
			zuzyciePaliwa(stold(n->Attribute(ATRYBUT_XML_ZUZYCIE_PALIWA)));
			przyrostZuzyciaPaliwa = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_ZUZYCIE_PALIWA));
			
			masaNapedu(stold(n->Attribute(ATRYBUT_XML_MASA_SILNIKA)));
			przyrostMasyNapedu = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_MASA_SILNIKA));
			
			sprawnoscSilnika(stof(n->Attribute(ATRYBUT_XML_SPRAWNOSC_SILNIKA)));
			przyrostSprawnosciSilnika = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_SPRAWNOSC_SILNIKA));
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