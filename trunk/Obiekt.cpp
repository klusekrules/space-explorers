#include "Obiekt.h"
#include "ObiektInfo.h"
#include "Logger.h"

Obiekt::Obiekt()
	: Base( ), ObiektBase()
	, zmObjetosc( )
	, zmMasa( )
	, zmPowierzchnia( )
{
}

Obiekt::Obiekt( const ObiektBase& obiekt )
	: Base( obiekt ), ObiektBase( obiekt )
	, zmObjetosc( )
	, zmMasa( )
	, zmPowierzchnia( )
{
}

Obiekt::Obiekt( const Obiekt& obiekt )
	: Base( obiekt ), ObiektBase( obiekt )
	, zmObjetosc( obiekt.zmObjetosc )
	, zmMasa( obiekt.zmMasa )
	, zmPowierzchnia( obiekt.zmPowierzchnia)
{
}

Obiekt::Obiekt( const ObiektInfo& obiekt )
	: Base( obiekt ), ObiektBase( obiekt )
	, zmObjetosc( )
	, zmMasa( )
	, zmPowierzchnia( )
{
}

Obiekt::Obiekt( const Fluktuacja& wzPow , const Fluktuacja& wzObj , const Fluktuacja& wzMasa, const ObiektBase& bBase)
	: Base( bBase ), ObiektBase( bBase )
	, zmObjetosc( wzObj )
	, zmMasa( wzMasa )
	, zmPowierzchnia( wzPow )
{
}

Obiekt::Obiekt( const Fluktuacja& wzPow , const Fluktuacja& wzObj , const Fluktuacja& wzMasa, const ObiektInfo& bBase)
	: Base( bBase ), ObiektBase( bBase )
	, zmObjetosc( wzObj )
	, zmMasa( wzMasa )
	, zmPowierzchnia( wzPow )
{
}

Obiekt::~Obiekt(){
}

Obiekt* Obiekt::Kopia() const{
	return new Obiekt(*this);
}

Obiekt* Obiekt::Podziel( const Ilosc& i ){
	if( Ilosc::operator>(i) ){
		Obiekt* o = new Obiekt( *this );
		Ilosc::operator-=(i);
		o->setIlosc(i.value());
		return o; 
	}
	return nullptr;
}	
Powierzchnia Obiekt::getPowierzchnia() const{
	return info == nullptr ? Powierzchnia() : Powierzchnia(*info) *( Fluktuacja(1.0) + zmPowierzchnia ) * Ilosc(*this) ;
}

Objetosc Obiekt::getObjetosc() const{
	return info == nullptr ? Objetosc() : Objetosc(*info) *( Fluktuacja(1.0) + zmObjetosc ) * Ilosc(*this);
}

Masa Obiekt::getMasa() const{
	return info == nullptr ? Masa() : Masa(*info) *( Fluktuacja(1.0) + zmObjetosc ) * Ilosc(*this);
}
		
const Fluktuacja& Obiekt::getZmianaPowierzchnia() const{
	return zmPowierzchnia;
}
void Obiekt::setZmianaPowierzchnia( const Fluktuacja& pPrzyrostPowierzchnia ){
	zmPowierzchnia = pPrzyrostPowierzchnia;
}

const Fluktuacja& Obiekt::getZmianaObjetosc() const{
	return zmObjetosc;
}
void Obiekt::setZmianaObjetosc( const Fluktuacja& pPrzyrostObjetosc ){
	zmObjetosc = pPrzyrostObjetosc;
}

const Fluktuacja& Obiekt::getZmianaMasa() const{
	return zmMasa;
}
void Obiekt::setZmianaMasa( const Fluktuacja& pPrzyrostMasa ){
	zmMasa = pPrzyrostMasa;
}

string Obiekt::toString() const{
	Logger str(LogObiekt::className());
	str.addClass(ObiektBase::toString());
	str.addField("ZmianaPowierzchni",zmPowierzchnia);
	str.addField("ZmianaObjetosci",zmObjetosc);
	str.addField("ZmianaMasy",zmMasa);
	return str.toString();
}