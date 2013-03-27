#include "JednostkaLatajacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"

JednostkaLatajacaInfo::JednostkaLatajacaInfo( const Info& info,const Klucz& k, const MocSilnika& moc, const ZuzyciePaliwa& z, const Masa& masa )
	: Info(info), rodzajNapedu(k), mocSilnika(moc), zuzyciePaliwa(z), masaNapedu(masa), przyrostZuzyciaPaliwa(nullptr), przyrostSprawnosciSilnika(nullptr),
	przyrostMocySilnika(nullptr), przyrostMasyNapedu(nullptr)
{
}

JednostkaLatajacaInfo::JednostkaLatajacaInfo( ticpp::Node* n )
	: Info(XmlBO::IterateChildren(n,Info::LogInfo::className())), przyrostZuzyciaPaliwa(nullptr), przyrostSprawnosciSilnika(nullptr),
	przyrostMocySilnika(nullptr), przyrostMasyNapedu(nullptr)
{
	if(n!=nullptr){
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

MocSilnika JednostkaLatajacaInfo::getMocSilnika() const{
	if(przyrostMocySilnika==nullptr)
		return mocSilnika;
	else
		return MocSilnika(przyrostMocySilnika->value(mocSilnika.value()));
}

ZuzyciePaliwa JednostkaLatajacaInfo::getZuzyciePaliwa() const{
	if(przyrostZuzyciaPaliwa==nullptr)
		return zuzyciePaliwa;
	else
		return ZuzyciePaliwa(przyrostZuzyciaPaliwa->value(zuzyciePaliwa.value()));
}

Masa JednostkaLatajacaInfo::getMasaNapedu() const{
	if(przyrostMasyNapedu==nullptr)
		return masaNapedu;
	else
		return Masa(przyrostMasyNapedu->value(masaNapedu.value()));
}

Fluktuacja JednostkaLatajacaInfo::getSprawnoscSilnika() const{
	if(przyrostSprawnosciSilnika==nullptr)
		return sprawnoscSilnika;
	else
		return Fluktuacja(static_cast<float>(przyrostSprawnosciSilnika->value(sprawnoscSilnika.value())));
}

string JednostkaLatajacaInfo::toString() const{
	Logger str(LogJednostkaLatajacaInfo::className());
	str.addClass(Info::toString());
	str.addField("RodzajNapedu",rodzajNapedu);
	str.addField(mocSilnika.className(),mocSilnika);
	if(przyrostMocySilnika!=nullptr){
		str.addField("ZmianaMocySilnika",*przyrostMocySilnika);
	}
	str.addField("SprawnoscSilnika",sprawnoscSilnika);
	if(przyrostSprawnosciSilnika!=nullptr){
		str.addField("ZmianaSprawnosciSilnika",*przyrostSprawnosciSilnika);
	}
	str.addField(zuzyciePaliwa.className(),zuzyciePaliwa);
	if(przyrostZuzyciaPaliwa!=nullptr){
		str.addField("ZmianaZuzyciaPaliwa",*przyrostZuzyciaPaliwa);
	}
	str.addField("MasaNapedu",masaNapedu);
	if(przyrostMasyNapedu!=nullptr){
		str.addField("ZmianaMasyNapedu",*przyrostMasyNapedu);
	}
	
	return str.toString();
}