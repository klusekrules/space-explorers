
#include "Biblioteki.h"
/*

Statek::Statek(){
}

Statek::Statek( const SPG::IloscJednostek& ilIlosc , const Statek& sStatek )
	: ilosc(ilIlosc), JednostkaAtakujaca(sStatek), JednostkaLatajaca(sStatek)
	, Ladownia(sStatek), Obiekt(sStatek)
{
}

Statek::Statek( const Statek& sStatek )
	: ilosc(sStatek.getIlosc()), JednostkaAtakujaca(sStatek), JednostkaLatajaca(sStatek)
	, Ladownia(sStatek), Obiekt(sStatek)
{
}

Statek::Statek( const SPG::IloscJednostek& i , const StatekInfo& s )
	: ilosc( i ), JednostkaAtakujaca(s), JednostkaLatajaca(s)
	, Ladownia(s), Obiekt(s)
{
}

Statek::~Statek(){
}

bool Statek::Polacz( const Obiekt& obiekt ){
	if( obiekt.ID() == this->ID() && obiekt.getPoziom() == this->getPoziom() ){
		const Statek& statek = dynamic_cast< const Statek& >(obiekt);
		ilosc+=statek.ilosc;
		for(auto iter = statek.zbiornik.begin(); iter!=statek.zbiornik.end(); iter++){
			this->DodajObiektDoLadowni(iter->second);
		}
		return true;
	}
	return false;
}

Obiekt* Statek::Kopia() const{
	return new Statek( *this );
}

Obiekt* Statek::Podziel( const SPG::IloscJednostek& ilosc ){
	if( ilosc < 0 || ilosc >= this->ilosc )
		return NULL;
	if(this->pojemnosc <= (this->ilosc - ilosc) * Ladownia::MaksymalnaPojemnosc() ){
		this->ilosc -= ilosc;
		Statek* result = new Statek( ilosc , *this );
		result->setPrzeworzoneObiekty(SPG::ZbiornikObiektow());
		return result;
	}else{		
		this->ilosc -= ilosc;
		SPG::Objetosc min = this->pojemnosc - this->MaksymalnaPojemnosc();
		Statek* result = new Statek( ilosc , *this );
		result->setPrzeworzoneObiekty( this->PodzielLadownie( result->MaksymalnaPojemnosc() , min ) );
		return result;
	}	
}

SPG::Obrazenia Statek::Atak() const{
	return SPG::Obrazenia();
}	

SPG::Obrazenia Statek::Pancerz( const SPG::Obrazenia& ) const{
	return SPG::Obrazenia();
}	

SPG::Obrazenia Statek::Oslona( const SPG::Obrazenia& ) const{
	return SPG::Obrazenia();
}

SPG::ZuzyciePaliwa Statek::ZuzyciePaliwa( const SPG::Dystans& , const SPG::Predkosc& ) const{
	return SPG::ZuzyciePaliwa();
}

SPG::Predkosc Statek::PredkoscMaksymalna() const{
	return SPG::Predkosc();
}

SPG::Objetosc Statek::MaksymalnaPojemnosc() const{
	return Ladownia::MaksymalnaPojemnosc() * ilosc;
}

SPG::Objetosc Statek::Objetosc() const{
	return getObjetosc() * ilosc;
}

SPG::Masa Statek::Masa() const{
	return getMasa() * ilosc;
}

SPG::IloscJednostek Statek::getIlosc() const{
	return ilosc;
}
void Statek::setIlosc( const SPG::IloscJednostek& ilosc ){
	this->ilosc = ilosc;
}

string Statek::toString() const{
	Logger str("Statek");
	str.dodajPole("Ilosc",ilosc);
	str.dodajKlase(Obiekt::toString());
	str.dodajKlase(Ladownia::toString());	
	str.dodajKlase(JednostkaAtakujaca::toString());
	str.dodajKlase(JednostkaLatajaca::toString());
	return str.toString();
}*/