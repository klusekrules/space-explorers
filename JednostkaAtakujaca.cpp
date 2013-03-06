
#include "JednostkaAtakujaca.h"
#include "Logger.h"

JednostkaAtakujaca::JednostkaAtakujaca()
	: info(nullptr)
{
}

JednostkaAtakujaca::JednostkaAtakujaca( JednostkaAtakujacaInfo * jInfo , const Fluktuacja& wzPrzyrostAtaku, const Fluktuacja& wzPrzyrostPancerza, const Fluktuacja& wzPrzyrostOslony )
	: przyrostAtaku( wzPrzyrostAtaku ) , przyrostPancerza( wzPrzyrostPancerza ) , przyrostOslony( wzPrzyrostOslony ) 
	, info(jInfo)
{
}

JednostkaAtakujaca::JednostkaAtakujaca( const JednostkaAtakujaca& a )
	: przyrostAtaku( a.przyrostAtaku ) , przyrostPancerza( a.przyrostPancerza ) 
	, przyrostOslony( a.przyrostOslony ) , info(a.info)
{
}

JednostkaAtakujaca::~JednostkaAtakujaca(){
}


Obrazenia JednostkaAtakujaca::Atak() const throw ( NiezainicjalizowanaKlasa ) {
	if(info==nullptr)
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,JednostkaAtakujacaInfo::LogJednostkaAtakujacaInfo::className());
	return info->getAtak();
}

Obrazenia JednostkaAtakujaca::Pancerz( const Obrazenia& a ) const throw ( NiezainicjalizowanaKlasa ){
	if(info==nullptr)
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,JednostkaAtakujacaInfo::LogJednostkaAtakujacaInfo::className());
	return a > info->getPancerz() ? a - info->getPancerz() : Obrazenia(0) ;
}		

Obrazenia JednostkaAtakujaca::Oslona( const Obrazenia& a ) const throw ( NiezainicjalizowanaKlasa ){
	if(info==nullptr)
		throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE,JednostkaAtakujacaInfo::LogJednostkaAtakujacaInfo::className());
	return a > info->getOslona() ? a - info->getOslona() : Obrazenia(0) ;
}

const Fluktuacja& JednostkaAtakujaca::getPrzyrostAtaku() const{
	return przyrostAtaku;
}

void JednostkaAtakujaca::setPrzyrostAtaku( const Fluktuacja& wzPrzyrostAtaku ){
	przyrostAtaku = wzPrzyrostAtaku;
}

JednostkaAtakujacaInfo* JednostkaAtakujaca::getJednostkaAtakujacaInfo() const{
	return info;
}

void JednostkaAtakujaca::setJednostkaAtakujacaInfo( JednostkaAtakujacaInfo* i){
	info = i;
}

const Fluktuacja& JednostkaAtakujaca::getPrzyrostPancerza() const{
	return przyrostPancerza;
}	

void JednostkaAtakujaca::setPrzyrostPancerza( const Fluktuacja& wzPrzyrostPancerza ){
	przyrostPancerza = wzPrzyrostPancerza;
}
	
const Fluktuacja& JednostkaAtakujaca::getPrzyrostOslony() const{
	return przyrostOslony;
}

void JednostkaAtakujaca::setPrzyrostOslony( const Fluktuacja& wzPrzyrostOslony ){
	przyrostOslony = wzPrzyrostOslony;
}

string JednostkaAtakujaca::toString() const{
	Logger str(LogJednostkaAtakujaca::className());
	str.addField("PrzyrostAtaku",przyrostAtaku);
	str.addField("PrzyrostPancerza",przyrostPancerza);
	str.addField("PrzyrostOslony",przyrostOslony);
	return str.toString();
}