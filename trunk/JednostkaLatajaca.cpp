
#include "JednostkaLatajaca.h"
#include "Logger.h"

JednostkaLatajaca::JednostkaLatajaca()
	:  przyrostMocySilnika( ), przyrostZuzyciaPaliwa( )
{
}
JednostkaLatajaca::JednostkaLatajaca( JednostkaLatajacaInfo* jInfo , const Fluktuacja& wzMoc, const Fluktuacja& wzZuzycie)
	: info(jInfo), przyrostMocySilnika(wzMoc), przyrostZuzyciaPaliwa(wzZuzycie)
{
}
JednostkaLatajaca::JednostkaLatajaca( const JednostkaLatajaca& a )
	: info(a.info), przyrostMocySilnika(a.przyrostMocySilnika), przyrostZuzyciaPaliwa(a.przyrostZuzyciaPaliwa)
{
}
	
JednostkaLatajaca::~JednostkaLatajaca(){
}

ZuzyciePaliwa JednostkaLatajaca::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const{
	return ZuzyciePaliwa();
}

Predkosc JednostkaLatajaca::PredkoscMaksymalna() const{
	return Predkosc();
}

Masa JednostkaLatajaca::CalkowitaMasaJednostki() const{
	return Masa();
}

const Fluktuacja& JednostkaLatajaca::getPrzyrostMocySilnika() const{
	return przyrostMocySilnika;
}

void JednostkaLatajaca::setPrzyrostMocySilnika( const Fluktuacja& f ){
	przyrostMocySilnika = f;
}

const Fluktuacja& JednostkaLatajaca::getPrzyrostZuzyciaPaliwa() const{
	return przyrostZuzyciaPaliwa;
}

void JednostkaLatajaca::setPrzyrostZuzyciaPaliwa( const Fluktuacja& f ){
	przyrostZuzyciaPaliwa = f;
}

string JednostkaLatajaca::toString() const{
	Logger str(className());
	str.addField("PrzyrostMocySilnika",przyrostMocySilnika);
	str.addField("PrzyrostZuzyciaPaliwa",przyrostZuzyciaPaliwa);
	return str.toString();
}