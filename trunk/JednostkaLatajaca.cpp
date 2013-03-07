
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

ZuzyciePaliwa JednostkaLatajaca::WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const throw ( NiezainicjalizowanaKlasa ){
	if(info==nullptr)
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,JednostkaLatajacaInfo::LogJednostkaLatajacaInfo::className());
	return ZuzyciePaliwa(info->getZuzyciePaliwa().getZuzyciePaliwa()*przyrostZuzyciaPaliwa.getFluktuacja());
}

Predkosc JednostkaLatajaca::PredkoscMaksymalna() const throw ( NiezainicjalizowanaKlasa ){
	if(info==nullptr)
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,JednostkaLatajacaInfo::LogJednostkaLatajacaInfo::className());
	long double eta_m = info->getSprawnoscSilnika().getFluktuacja() * przyrostSprawnosciSilnika.getFluktuacja();
	long double a = 0.01;
	long double P = info->getMocSilnika().getMocSilnika() * przyrostMocySilnika.getFluktuacja();
	return Predkosc( ( P * eta_m )/(CalkowitaMasaJednostki().getMasa() * a) );
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

const Fluktuacja& JednostkaLatajaca::getPrzyrostSprawnosciSilnika() const{
	return przyrostSprawnosciSilnika;
}

void JednostkaLatajaca::setPrzyrostSprawnosciSilnika( const Fluktuacja& f ){
	przyrostSprawnosciSilnika = f;
}

string JednostkaLatajaca::toString() const{
	Logger str(className());
	str.addField("PrzyrostMocySilnika",przyrostMocySilnika);
	str.addField("PrzyrostSprawnosciSilnika",przyrostSprawnosciSilnika);
	str.addField("PrzyrostZuzyciaPaliwa",przyrostZuzyciaPaliwa);
	return str.toString();
}