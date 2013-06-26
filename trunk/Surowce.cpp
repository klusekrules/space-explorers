#include "Surowce.h"
#include "SurowceInfo.h"
#include "Logger.h"
#include "Ladownia.h"

Surowce::Surowce( const Ilosc& isIlosc, const Poziom& p, const SurowceInfo& s )
	:  Obiekt( isIlosc, p, s ), surowceInfo(s)
{
}

Surowce::Surowce( const Ilosc& isIlosc , const Surowce& s )
	:  Obiekt( s ), surowceInfo(s.surowceInfo)
{
}

Surowce::~Surowce( ){
}

bool Surowce::Polacz( const Obiekt& obiekt ) throw ( BladLaczeniaObiektow ){
	if( obiekt.ID() == this->ID() ){
		try
        {
			const Surowce& sur = dynamic_cast< const Surowce& >(obiekt);
			ilosc+=sur.ilosc;
			return true;
		}catch(const std::bad_cast&){
			throw BladLaczeniaObiektow(EXCEPTION_PLACE,this->toString(),obiekt.toString() );
		}
	}
	return false;
}

Surowce* Surowce::Kopia() const{
	return new Surowce( *this );
}

Obiekt* Surowce::Podziel( const Ilosc& ilosc ) throw ( NiepoprawnaIloscObiektow ){
	if( ilosc <= Ilosc(0.0l) || ilosc >= this->ilosc )
		throw NiepoprawnaIloscObiektow(EXCEPTION_PLACE,ilosc);
	this->ilosc -= ilosc;
	return new Surowce( ilosc , *this );
}

Objetosc Surowce::Objetosc() const{
	return getObjetosc() * ilosc ;
}

Masa Surowce::Masa() const{
	return getMasa() * ilosc;
}

Surowce& Surowce::operator=( const Surowce& sSurowce )  throw ( NiezgodnyTypSurowca ) {
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	ilosc = sSurowce.ilosc;
	return *this;
}

bool Surowce::operator==( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc == sSurowce.ilosc;
}
	
bool Surowce::operator!=( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc != sSurowce.ilosc;
}
	
bool Surowce::operator>( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc > sSurowce.ilosc;
}
	
bool Surowce::operator<( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc < sSurowce.ilosc;
}
	
bool Surowce::operator>=( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc >= sSurowce.ilosc;
}
	
bool Surowce::operator<=( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return ilosc <= sSurowce.ilosc ;
}

Surowce Surowce::operator+( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return Surowce( ilosc + sSurowce.ilosc , sSurowce );
}
	
Surowce& Surowce::operator+=( const Surowce& sSurowce )  throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	ilosc += sSurowce.ilosc;
	return *this;
}
	
Surowce Surowce::operator-( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return Surowce( ilosc - sSurowce.ilosc, sSurowce  );
}

Surowce& Surowce::operator-=( const Surowce& sSurowce ) throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	ilosc -= sSurowce.ilosc;
	return *this;
}

bool Surowce::Dodaj( const Surowce& sSurowce ){
	if( this->ID() != sSurowce.ID() )
		return false;
	ilosc += sSurowce.ilosc;
	return true;
}
	
bool Surowce::Usun( const Surowce& sSurowce ){
	if( this->ID() != sSurowce.ID() )
		return false;
	ilosc -= sSurowce.ilosc;
	return true;
}
	
const Ilosc& Surowce::getIlosc() const{
	return ilosc;
}
	
void Surowce::setIlosc( const Ilosc& isIlosc ) {
	ilosc = isIlosc;
}

const SurowceInfo& Surowce::getSurowceInfo() const{
	return surowceInfo;
}

bool Surowce::czyTypPrzyrostowy()const{
	return surowceInfo.czyTypPrzyrostowy();
}

bool Surowce::czMoznaDodacDoLadownii( const Ladownia& c ) const{
	return c.czMoznaDodacDoLadownii(*this);
}
	
string Surowce::toString() const{
	Logger str(CLASSNAME(Surowce));
	str.addClass(Obiekt::toString());
	str.addField(CLASSNAME(Ilosc),ilosc);
	str.addField(CLASSNAME(SurowceInfo)+"ID",surowceInfo.getId());
	return str.toString();
}