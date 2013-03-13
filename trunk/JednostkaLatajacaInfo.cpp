#include "JednostkaLatajacaInfo.h"
#include "Logger.h"

JednostkaLatajacaInfo::JednostkaLatajacaInfo( const Info& info,const Klucz& k, const MocSilnika& moc, const ZuzyciePaliwa& z, const Masa& masa )
	: Info(info), rodzajNapedu(k), mocSilnika(moc), zuzyciePaliwa(z), masaNapedu(masa), przyrostZuzyciaPaliwa(nullptr), przyrostSprawnosciSilnika(nullptr),
	przyrostMocySilnika(nullptr), przyrostMasyNapedu(nullptr)
{
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
		return przyrostMocySilnika->value(mocSilnika);
}

ZuzyciePaliwa JednostkaLatajacaInfo::getZuzyciePaliwa() const{
	if(przyrostZuzyciaPaliwa==nullptr)
		return zuzyciePaliwa;
	else
		return przyrostZuzyciaPaliwa->value(zuzyciePaliwa);
}

Masa JednostkaLatajacaInfo::getMasaNapedu() const{
	if(przyrostMasyNapedu==nullptr)
		return masaNapedu;
	else
		return przyrostMasyNapedu->value(masaNapedu);
}

Fluktuacja JednostkaLatajacaInfo::getSprawnoscSilnika() const{
	if(przyrostSprawnosciSilnika==nullptr)
		return sprawnoscSilnika;
	else
		return przyrostSprawnosciSilnika->value(sprawnoscSilnika);
}

string JednostkaLatajacaInfo::toString() const{
	Logger str(LogJednostkaLatajacaInfo::className());
	str.addClass(Info::toString());
	str.addField("RodzajNapedu",rodzajNapedu);
	str.addField("MocSilnika",mocSilnika);
	if(przyrostMocySilnika!=nullptr){
		str.addField("ZmianaMocySilnika",*przyrostMocySilnika);
	}
	str.addField("SprawnoscSilnika",sprawnoscSilnika);
	if(przyrostSprawnosciSilnika!=nullptr){
		str.addField("ZmianaSprawnosciSilnika",*przyrostSprawnosciSilnika);
	}
	str.addField("ZuzyciePaliwa",zuzyciePaliwa);
	if(przyrostZuzyciaPaliwa!=nullptr){
		str.addField("ZmianaZuzyciaPaliwa",*przyrostZuzyciaPaliwa);
	}
	str.addField("MasaNapedu",masaNapedu);
	if(przyrostMasyNapedu!=nullptr){
		str.addField("ZmianaMasyNapedu",*przyrostMasyNapedu);
	}
	
	return str.toString();
}