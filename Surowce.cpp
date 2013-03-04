#include "Surowce.h"
#include "Logger.h"

Surowce::Surowce( )
	: ilosc(  )
{
}

Surowce::Surowce( const Ilosc& isIlosc , const SurowceInfo& s )
	: ilosc( isIlosc ), Obiekt( reinterpret_cast< const ObiektInfo& >(s) )
{
}

Surowce::Surowce( const Ilosc& isIlosc , const Surowce& s )
	: ilosc( isIlosc ), Obiekt( s )
{
}

Surowce::Surowce( const Surowce& sSurowce )
	: ilosc( sSurowce.ilosc ), Obiekt( sSurowce )
{
}

Surowce::~Surowce( ){
}

bool Surowce::Polacz( const Obiekt& obiekt ){
	if( obiekt.ID() == this->ID() && obiekt.getPoziom() == this->getPoziom() ){
		const Surowce& sur = dynamic_cast< const Surowce& >(obiekt);
		ilosc+=sur.ilosc;
		return true;
	}
	return false;
}

Obiekt* Surowce::Kopia() const{
	return new Surowce( *this );
}

Obiekt* Surowce::Podziel( const Ilosc& ilosc ){
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

Surowce& Surowce::operator=( const Surowce& sSurowce ){
	ilosc = sSurowce.ilosc;
	Obiekt::operator=(sSurowce);
	return *this;
}

bool Surowce::operator==( const Surowce& sSurowce ) const{
	if( this->ID() != sSurowce.ID() )
		return false;
	return ilosc == sSurowce.ilosc;
}
	
bool Surowce::operator!=( const Surowce& sSurowce ) const{
	if( this->ID() != sSurowce.ID() )
		return false;
	return ilosc != sSurowce.ilosc;
}
	
bool Surowce::operator>( const Surowce& sSurowce ) const{
	if( this->ID() != sSurowce.ID() )
		return false;
	return ilosc > sSurowce.ilosc;
}
	
bool Surowce::operator<( const Surowce& sSurowce ) const{
	if( this->ID() != sSurowce.ID() )
		return false;
	return ilosc < sSurowce.ilosc;
}
	
bool Surowce::operator>=( const Surowce& sSurowce ) const{
	if( this->ID() != sSurowce.ID() )
		return false;
	return ilosc >= sSurowce.ilosc;
}
	
bool Surowce::operator<=( const Surowce& sSurowce ) const{
	if( this->ID() != sSurowce.ID() )
		return false;
	return ilosc <= sSurowce.ilosc ;
}

Surowce Surowce::operator+( const Surowce& sSurowce ) const throw ( NiezgodnyTypSurowca ){
	if( this->ID() != sSurowce.ID() )
		throw NiezgodnyTypSurowca( EXCEPTION_PLACE, this->ID() , sSurowce.ID() );
	return Surowce( ilosc + sSurowce.ilosc , sSurowce );
}
	
Surowce Surowce::operator+=( const Surowce& sSurowce )  throw ( NiezgodnyTypSurowca ){
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

Surowce Surowce::operator-=( const Surowce& sSurowce ) throw ( NiezgodnyTypSurowca ){
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
	
Ilosc Surowce::getIlosc() const{
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