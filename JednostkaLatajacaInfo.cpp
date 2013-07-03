#include "JednostkaLatajacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"

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
			przyrostMocySilnika = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenElementIf<NOTHROW>(n,"Zmiana","for","mocSilnika"));
			
			zuzyciePaliwa.setZuzyciePaliwa(stold(e->GetAttribute("zuzyciePaliwa")));
			przyrostZuzyciaPaliwa = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenElementIf<NOTHROW>(n,"Zmiana","for","zuzyciePaliwa"));
			
			masaNapedu.setMasa(stold(e->GetAttribute("masaSilnika")));
			przyrostMasyNapedu = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenElementIf<NOTHROW>(n,"Zmiana","for","masaSilnika"));
			
			sprawnoscSilnika.setFluktuacja(stof(e->GetAttribute("sprawnoscSilnika")));
			przyrostSprawnosciSilnika = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenElementIf<NOTHROW>(n,"Zmiana","for","sprawnoscSilnika"));
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
		return MocSilnika(przyrostMocySilnika->value(mocSilnika.value(),static_cast<int>(p.getPoziom().value()),p.getIdPlanety().value()));
	else
		return mocSilnika;
}

ZuzyciePaliwa JednostkaLatajacaInfo::getZuzyciePaliwa(const PodstawoweParametry& p) const{
	if(przyrostZuzyciaPaliwa)
		return ZuzyciePaliwa(przyrostZuzyciaPaliwa->value(zuzyciePaliwa.value(),static_cast<int>(p.getPoziom().value()),p.getIdPlanety().value()));
	else
		return zuzyciePaliwa;
}

Masa JednostkaLatajacaInfo::getMasaNapedu( const PodstawoweParametry& p) const{
	if(przyrostMasyNapedu)
		return Masa(przyrostMasyNapedu->value(masaNapedu.value(),static_cast<int>(p.getPoziom().value()),p.getIdPlanety().value()));
	else
		return masaNapedu;
}

Fluktuacja JednostkaLatajacaInfo::getSprawnoscSilnika( const PodstawoweParametry& p) const{
	if(przyrostSprawnosciSilnika)
		return Fluktuacja(static_cast<float>(przyrostSprawnosciSilnika->value(sprawnoscSilnika.value(),static_cast<int>(p.getPoziom().value()),p.getIdPlanety().value())));
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