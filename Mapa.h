#pragma once
#include "Main.h"
#include <map>
#include "Base.h"
#include "Logger.h"

template< class Klucz, class Wartosc >
class Mapa:
	public Base,
	virtual public LoggerInterface,
	public map<Klucz,Wartosc* >
{
	static_assert(!is_pointer< Klucz >::value, "Klucz nie moze byc wskaznikiem.");
	static_assert(!is_pointer< Wartosc >::value, "Wartosc nie moze byc wskaznikiem.");
private:
	typedef Mapa<Klucz,Wartosc > TYP;
public:
	typedef map<Klucz,Wartosc* > HashMapa;

	explicit Mapa( const Identyfikator& id )
		: Base(id), map()
	{
	}

	explicit Mapa( const Base& base )
		: Base(base), map()
	{
	}

	explicit Mapa( const map<Klucz,Wartosc* >& mapa )
		: Base(), map(mapa)
	{
	}

	Mapa( const map<Klucz,Wartosc* >& mapa, const Identyfikator& id )
		: Base(id), map(mapa)
	{
	}

	Mapa( const map<Klucz,Wartosc* >& mapa, const Base& base )
		: Base(base), map(mapa)
	{
	}

	virtual ~Mapa(){
	}

	void put( const Klucz& k, Wartosc* w){
		this->operator[](k)=w;
	}

	Wartosc* get( const Klucz& k ) const{
		return this->at(k);
	}

	string napis() const override{
		Logger str(NAZWAKLASY( TYP ));
		str.dodajKlase(Base::napis());
		str.rozpocznijPodKlase("hash_map");
		for(const_iterator iter=begin(); iter!=end(); ++iter){
			str.dodajPole( "", (*iter).first , *( (*iter).second ) );
		}
		str.zakonczPodKlase();
		return str.napis();
	}
};