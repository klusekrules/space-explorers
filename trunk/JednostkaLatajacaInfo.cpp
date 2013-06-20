#include "JednostkaLatajacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"

JednostkaLatajacaInfo::JednostkaLatajacaInfo( const Info& info,const Klucz& k, const MocSilnika& moc, const ZuzyciePaliwa& z, const Masa& masa ) throw()
	: Info(info), rodzajNapedu(k), mocSilnika(moc), zuzyciePaliwa(z), masaNapedu(masa), przyrostMocySilnika(nullptr), przyrostSprawnosciSilnika(nullptr), przyrostZuzyciaPaliwa(nullptr), przyrostMasyNapedu(nullptr)
{
}

JednostkaLatajacaInfo::JednostkaLatajacaInfo( ticpp::Node* n ) throw(WyjatekParseraXML)
	: Info(XmlBO::IterateChildren<THROW>(n,CLASSNAME(Info))), przyrostMocySilnika(nullptr), przyrostSprawnosciSilnika(nullptr), przyrostZuzyciaPaliwa(nullptr), przyrostMasyNapedu(nullptr)
{
	if(n){
		try{
			ticpp::Element* e = n->ToElement();
			IdType id(stoi(e->GetAttribute("rodzajSilnikaId"),nullptr,0));
			Poziom poziom(stoi(e->GetAttribute("rodzajSilnikaPoziom")));
			rodzajNapedu.setKlucz(Klucz(id,poziom).getKlucz());
			mocSilnika.setMocSilnika(stold(e->GetAttribute("mocSilnika")));
			zuzyciePaliwa.setZuzyciePaliwa(stold(e->GetAttribute("zuzyciePaliwa")));
			masaNapedu.setMasa(stold(e->GetAttribute("masaSilnika")));
			sprawnoscSilnika.setFluktuacja(stof(e->GetAttribute("sprawnoscSilnika")));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

JednostkaLatajacaInfo::~JednostkaLatajacaInfo()
{
}

const Klucz& JednostkaLatajacaInfo::getRodzajNapedu() const{
	return rodzajNapedu;
}

MocSilnika JednostkaLatajacaInfo::getMocSilnika(const Poziom& p ) const{
	if(przyrostMocySilnika==nullptr)
		return mocSilnika;
	else
		return MocSilnika(przyrostMocySilnika->value(mocSilnika.value(),static_cast<int>(p.value())));
}

ZuzyciePaliwa JednostkaLatajacaInfo::getZuzyciePaliwa(const Poziom& p ) const{
	if(przyrostZuzyciaPaliwa==nullptr)
		return zuzyciePaliwa;
	else
		return ZuzyciePaliwa(przyrostZuzyciaPaliwa->value(zuzyciePaliwa.value(),static_cast<int>(p.value())));
}

Masa JednostkaLatajacaInfo::getMasaNapedu( const Poziom& p ) const{
	if(przyrostMasyNapedu==nullptr)
		return masaNapedu;
	else
		return Masa(przyrostMasyNapedu->value(masaNapedu.value(),static_cast<int>(p.value())));
}

Fluktuacja JednostkaLatajacaInfo::getSprawnoscSilnika( const Poziom& p ) const{
	if(przyrostSprawnosciSilnika==nullptr)
		return sprawnoscSilnika;
	else
		return Fluktuacja(static_cast<float>(przyrostSprawnosciSilnika->value(sprawnoscSilnika.value(),static_cast<int>(p.value()))));
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