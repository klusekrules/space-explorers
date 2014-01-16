#include "JednostkaAtakujaca.h"
#include "Logger.h"
#include "Aplikacja.h"

JednostkaAtakujaca::JednostkaAtakujaca( const Poziom& p , const Identyfikator& idP, const JednostkaAtakujacaInfo& jInfo )
	: PodstawoweParametry(p,idP), jednostkaAtakujacaInfo_(jInfo)
{
}

JednostkaAtakujaca::JednostkaAtakujaca( const PodstawoweParametry& p, const JednostkaAtakujacaInfo& jInfo )
	: PodstawoweParametry(p), jednostkaAtakujacaInfo_(jInfo)
{
}

JednostkaAtakujaca::~JednostkaAtakujaca(){
}

Obrazenia JednostkaAtakujaca::pobierzAtak() const {
	return jednostkaAtakujacaInfo_.pobierzAtak(*this);
}

Obrazenia JednostkaAtakujaca::pobierzPancerz() const{
	return jednostkaAtakujacaInfo_.pobierzPancerz(*this);
}

Obrazenia JednostkaAtakujaca::pobierzOslone() const{
	return jednostkaAtakujacaInfo_.pobierzOslone(*this);
}

string JednostkaAtakujaca::napis() const{
	Logger str(NAZWAKLASY(JednostkaAtakujaca));
	str.dodajPole(NAZWAKLASY(JednostkaAtakujacaInfo)+"ID",jednostkaAtakujacaInfo_.pobierzIdentyfikator());
	return str.napis();
}
