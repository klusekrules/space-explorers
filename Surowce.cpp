#include "Surowce.h"
#include "Logger.h"

Surowce::Surowce( const Ilosc& isIlosc , const SurowceInfo& s )
	: Base(reinterpret_cast< const Base& >(s) ), ilosc( isIlosc ), Obiekt( reinterpret_cast< const ObiektInfo& >(s) )
{
}

Surowce::Surowce( const Ilosc& isIlosc , const Surowce& s )
	: Base(s), ilosc( isIlosc ), Obiekt( s )
{
}

Surowce::Surowce( const Surowce& sSurowce )
	: Base(sSurowce), ilosc( sSurowce.ilosc ), Obiekt( sSurowce )
{
}

Surowce::~Surowce( ){
}

bool Surowce::Polacz( const Obiekt& obiekt ) throw ( BladLaczeniaObiektow ){
	if( obiekt.ID() == this->ID() && obiekt.getPoziom() == this->getPoziom() ){
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

const Surowce& Surowce::operator=( const Surowce& sSurowce )  throw ( NiezgodnyTypSurowca ) {
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
	
const Surowce& Surowce::operator+=( const Surowce& sSurowce )  throw ( NiezgodnyTypSurowca ){
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

const Surowce& Surowce::operator-=( const Surowce& sSurowce ) throw ( NiezgodnyTypSurowca ){
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

SurowceInfo* Surowce::getSurowceInfo() const{
	return info;
}
	
void Surowce::setSurowceInfo( SurowceInfo* sInfo ) {
	info = sInfo;
}
	
string Surowce::toString() const{
	Logger str(LogSurowce::className());
	str.addField(ilosc.className(),ilosc);
	str.addClass(Obiekt::toString());
	return str.toString();
}