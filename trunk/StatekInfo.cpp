#include "Biblioteki.h"
/*

StatekInfo::StatekInfo(){
}

StatekInfo::StatekInfo(	const Obiekt& o,
		const Cena& c,
		const Info& i,
		const Ladownia& l,
		const SPG::RodzajNapedu& rodzajNapedu,
		const SPG::MocSilnika& mocSilnika,
		const SPG::ZuzyciePaliwa& zuzyciePaliwa,1
		const SPG::Obrazenia& atak,
		const SPG::Obrazenia& pancerz,
		const SPG::Obrazenia& oslona
		)
		: Obiekt(o), Cena(c), Info(i), Ladownia(l),
		JednostkaLatajaca(rodzajNapedu,mocSilnika,Stale::wskaznikZdolnosciDomyslny,zuzyciePaliwa,Stale::wskaznikZdolnosciDomyslny),
		JednostkaAtakujaca(atak,pancerz,oslona,Stale::wskaznikZdolnosciDomyslny,Stale::wskaznikZdolnosciDomyslny,Stale::wskaznikZdolnosciDomyslny)
{
}

StatekInfo::~StatekInfo(){
}

StatekInfo::StatekInfo( const StatekInfo& a )
	: Info(a), Obiekt(a), Cena(a), Ladownia(a), JednostkaLatajaca(a), JednostkaAtakujaca(a)
{
}

SPG::ZuzyciePaliwa StatekInfo::ZuzyciePaliwa( const SPG::Dystans& , const SPG::Predkosc& ) const{
	return SPG::ZuzyciePaliwa();
}

SPG::Predkosc StatekInfo::PredkoscMaksymalna() const{
	return SPG::Predkosc();
}

SPG::Obrazenia StatekInfo::Atak() const{
	return SPG::Obrazenia();
}

SPG::Obrazenia StatekInfo::Pancerz( const SPG::Obrazenia& ) const{
	return SPG::Obrazenia();
}

SPG::Obrazenia StatekInfo::Oslona( const SPG::Obrazenia& ) const{
	return SPG::Obrazenia();
}	

Statek* StatekInfo::TworzEgzemplarz( const SPG::IloscJednostek& ilosc ) const{
	return new Statek( ilosc , *this );
}

string StatekInfo::toString() const{
	Logger str("StatekInfo");
	str.dodajKlase(Info::toString());
	str.dodajKlase(Obiekt::toString());
	str.dodajKlase(Cena::toString());
	str.dodajKlase(Ladownia::toString());
	str.dodajKlase(JednostkaLatajaca::toString());
	str.dodajKlase(JednostkaAtakujaca::toString());
	return str.toString();
}*/