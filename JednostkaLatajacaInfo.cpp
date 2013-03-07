#include "JednostkaLatajacaInfo.h"
#include "Logger.h"

JednostkaLatajacaInfo::JednostkaLatajacaInfo()
{
}

JednostkaLatajacaInfo::JednostkaLatajacaInfo( const Klucz& k, const MocSilnika& moc, const ZuzyciePaliwa& z, const Masa& masa )
	: rodzajNapedu(k), mocSilnika(moc), zuzyciePaliwa(z), masaNapedu(masa)
{
}

JednostkaLatajacaInfo::JednostkaLatajacaInfo( const JednostkaLatajacaInfo& a )
	: rodzajNapedu(a.rodzajNapedu), mocSilnika(a.mocSilnika), zuzyciePaliwa(a.zuzyciePaliwa), masaNapedu(a.masaNapedu)
{
}

JednostkaLatajacaInfo::~JednostkaLatajacaInfo()
{
}

const Klucz& JednostkaLatajacaInfo::getRodzajNapedu() const{
	return rodzajNapedu;
}

void JednostkaLatajacaInfo::setRodzajNapedu( const Klucz& k ){
	rodzajNapedu = k;
}

const MocSilnika& JednostkaLatajacaInfo::getMocSilnika() const{
	return mocSilnika;
}

void JednostkaLatajacaInfo::setMocSilnika( const MocSilnika& m ){
	mocSilnika = m;
}

const ZuzyciePaliwa& JednostkaLatajacaInfo::getZuzyciePaliwa() const{
	return zuzyciePaliwa;
}
void JednostkaLatajacaInfo::setZuzyciePaliwa( const ZuzyciePaliwa& z ){
	zuzyciePaliwa = z;
}

const Masa& JednostkaLatajacaInfo::getMasaNapedu() const{
	return masaNapedu;
}

void JednostkaLatajacaInfo::setMasaNapedu( const Masa& m ){
	masaNapedu = m;
}

const Fluktuacja& JednostkaLatajacaInfo::getSprawnoscSilnika() const{
	return sprawnoscSilnika;
}

void JednostkaLatajacaInfo::setSprawnoscSilnika( const Fluktuacja& m ){
	sprawnoscSilnika = m; 
}

string JednostkaLatajacaInfo::toString() const{
	Logger str(LogJednostkaLatajacaInfo::className());
	str.addClass(Info::toString());
	str.addField("RodzajNapedu",rodzajNapedu);
	str.addField("MocSilnika",mocSilnika);
	str.addField("SprawnoscSilnika",sprawnoscSilnika);
	str.addField("ZuzyciePaliwa",zuzyciePaliwa);
	str.addField("MasaNapedu",masaNapedu);
	return str.toString();
}